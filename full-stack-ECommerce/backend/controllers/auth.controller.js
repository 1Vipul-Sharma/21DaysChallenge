import mongoose from "mongoose";
import User from "../models/user.model.js";

export const signup = async (req, res) => {
  console.log("inside");
  const { name, email, password } = req.body;
  // console.log(name, email, password);
  const isExist = User.findOne({ email });
  if (isExist) return res.status(404).send("User Already exist");
  res.status(200).send(`signup route called`);
};
export const login = async (req, res) => {
  res.send(`login route called`);
};
export const logout = async (req, res) => {
  res.send(`logout route called`);
};
