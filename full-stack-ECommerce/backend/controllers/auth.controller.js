import mongoose from "mongoose";
import User from "../models/user.model.js";

export const signup = async (req, res) => {
  try {
    console.log("111");

    const { name, email, password } = req.body;
    // console.log(name, email, password);
    const isExist = await User.findOne({ email });
    if (isExist) return res.status(400).json({ message: "User Already exist" });
    else {
      const newUser = await User.create({ name, email, password });
      res.status(201).json({ newUser, message: "User Successfully Created" });
    }
  } catch (error) {
    res.status(500).json({ Error: error });
  }
};
export const login = async (req, res) => {
  res.send(`login route called`);
};
export const logout = async (req, res) => {
  res.send(`logout route called`);
};
