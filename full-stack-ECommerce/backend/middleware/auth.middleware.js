import jwt from "jsonwebtoken";
import { redisClient } from "../lib/redis.js";
import User from "../models/user.model.js";
export const protectRoute = async (req, res, next) => {
  try {
    const accessToken = req.cookies?.accessToken;
    if (!accessToken) {
      return res
        .status(401)
        .json({ message: "Unauthorized - No access token provided" });
    }
    let decoded;
    try {
      decoded = jwt.verify(accessToken, process.env.ACCESS_TOKEN_SECRET);
    } catch (err) {
      return res
        .status(403)
        .json({ message: "Invalid or expired access token" });
    }

    const user = await User.findById(decoded.userId).select("-password");
    if (!user)
      return res.status(401).json({
        message: "User not found",
      });
    req.user = user;
    next();
  } catch (error) {
    console.error("Error in Protecroute middleware:", error.message);
    return res.status(500).json({ message: "Server error" });
  }
};

export const adminRoute = async (req, res, next) => {
  try {
    if (req.user && req.user.role === "admin") next();
    else
      return res.status(403).json({
        message: "Access Denied",
      });
  } catch (error) {}
};
