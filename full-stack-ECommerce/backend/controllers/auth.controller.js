import jwt from "jsonwebtoken";
import mongoose from "mongoose";
import User from "../models/user.model.js";
import { redisClient } from "../lib/redis.js";

const generateTokens = (userId) => {
  const accessToken = jwt.sign({ userId }, process.env.ACCESS_TOKEN_SECRET, {
    expiresIn: "15m",
  });
  const refreshToken = jwt.sign({ userId }, process.env.REFRESH_TOKEN_SECRET, {
    expiresIn: "7d",
  });
  return { accessToken, refreshToken };
};

const setToken = async (userId, refreshToken) => {
  await redisClient.set(
    `refreshToken:${userId}`,
    refreshToken,
    "EX",
    7 * 24 * 60 * 60 // 7 days
  );
};

const setAuthCookies = (res, accessToken, refreshToken) => {
  res.cookie("accessToken", accessToken, {
    httpOnly: true,
    secure: process.env.NODE_ENV === "production", // only in prod
    sameSite: "strict",
    maxAge: 15 * 60 * 1000, // 15 min
  });

  res.cookie("refreshToken", refreshToken, {
    httpOnly: true,
    secure: process.env.NODE_ENV === "production",
    sameSite: "strict",
    maxAge: 7 * 24 * 60 * 60 * 1000, // 7 days
  });
};

export const signup = async (req, res) => {
  try {
    const { name, email, password } = req.body;

    // Check if user exists
    const isExist = await User.findOne({ email });
    if (isExist) {
      return res.status(400).json({ message: "User already exists" });
    }

    // Create new user
    const newUser = await User.create({
      name,
      email,
      password,
    });

    // Generate tokens
    const { accessToken, refreshToken } = generateTokens(newUser._id);

    // Store refresh token in Redis
    setToken(newUser.id_toString(), refreshToken);

    // Set cookies
    setAuthCookies(res, accessToken, refreshToken);

    // Success response
    res.status(201).json({
      name: newUser.name,
      email: newUser.email,
      role: newUser.role,
      message: "User successfully created",
    });
  } catch (error) {
    console.error("Signup Error:", error);
    res.status(500).json({ error: "Internal Server Error" });
  }
};

export const login = async (req, res) => {
  try {
    const { email, password } = req.body;

    // 1. Validate input
    if (!email || !password) {
      return res
        .status(400)
        .json({ message: "Email and password are required" });
    }

    // 2. Find user by email
    const user = await User.findOne({ email });
    if (!user) {
      return res.status(400).json({ message: "Invalid email or password" });
    }

    // 3. Compare password

    // console.log("vipul", user);

    const isValidPassword = await user.comparePassword(password);
    if (!isValidPassword) {
      return res.status(400).json({ message: "Invalid email or password" });
    }

    // 4. Generate tokens
    const { accessToken, refreshToken } = generateTokens(user._id);

    // 5. Store refresh token in Redis
    setToken(user._id.toString(), refreshToken);

    // 6. Set cookies
    setAuthCookies(res, accessToken, refreshToken);

    // 7. Send response
    return res.status(200).json({
      name: user.name,
      email: user.email,
      role: user.role,
      message: "Login successful",
    });
  } catch (error) {
    console.error("Login Error:", error);
    return res.status(500).json({ message: "Internal server error" });
  }
};

export const logout = async (req, res) => {
  try {
    const refreshToken = req.cookies?.refreshToken;

    if (refreshToken) {
      const decoded = jwt.verify(
        refreshToken,
        process.env.REFRESH_TOKEN_SECRET
      );
      // Delete session from Redis
      await redisClient.del(`refreshToken:${decoded.userId}`);
    }

    // Clear cookies
    res.clearCookie("accessToken");
    res.clearCookie("refreshToken");

    // (Optional) Tell frontend to clear local/session storage
    // res.json({ message: "Logout successful, please clear local storage" });

    return res.status(200).json({ message: "Logout successful" });
  } catch (err) {
    return res.status(500).json({ message: "Logout failed", error: err });
  }
};

export const refreshedToken = async (req, res) => {
  try {
    console.log("1111");

    const refreshToken = req.cookies?.refreshToken;
    // console.log(req.cookies);

    if (!refreshToken) {
      // console.log("11112");
      return res.status(401).json({ message: "No token provided" });
    }
    // console.log("1111222");
    let decoded;
    try {
      decoded = jwt.verify(refreshToken, process.env.REFRESH_TOKEN_SECRET);
    } catch (err) {
      return res
        .status(403)
        .json({ message: "Invalid or expired refresh token" });
    }

    const storedToken = await redisClient.get(`refreshToken:${decoded.userId}`);
    if (storedToken !== refreshToken) {
      return res.status(401).json({ message: "Invalid refresh token" });
    }

    const accessToken = jwt.sign(
      { userId: decoded.userId },
      process.env.ACCESS_TOKEN_SECRET,
      { expiresIn: "15m" }
    );

    res.cookie("accessToken", accessToken, {
      httpOnly: true,
      secure: process.env.NODE_ENV === "production",
      sameSite: "strict",
      maxAge: 15 * 60 * 1000,
    });

    return res.status(200).json({ message: "Token refreshed successfully" });
  } catch (error) {
    console.error("Error in refreshedToken controller:", error);
    return res.status(500).json({ message: "Server error" });
  }
};
