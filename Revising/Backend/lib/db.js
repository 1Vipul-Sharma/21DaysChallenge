import mongoose from "mongoose";

export const connectDB = async () => {
  const conn = await mongoose.connect(process.env.MONGO_URI);
  if (conn) {
    console.log(`Connected to MongoDB`);
  } else console.log("MongoDB connection error");
};
