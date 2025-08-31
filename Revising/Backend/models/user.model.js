import mongoose from "mongoose";
import brcypt from "bcrypt";
const userSchema = new mongoose.Schema({
  username: {
    type: String,
    required: true,
  },
  password: {
    type: String,
    required: true,
  },
  email: {
    type: String,
    required: true,
  },
});

userSchema.pre("save", async (next) => {
  if (!this.isModified("password")) return next();
  try {
    const salt = await brcypt.genSalt(10);
    this.password = await brcypt.hash(this.password, salt);
    next();
  } catch (error) {
    // console.log();
    next(error);
  }
});

const User = mongoose.model("User", userSchema);
export default User;
