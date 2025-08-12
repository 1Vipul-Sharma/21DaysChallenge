import mongoose from "mongoose";

export async function connectDB() {
  try {
    const conn = await mongoose.connect(process.env.MONGO_URI);
    console.log(`Successfully connected to MONGODB ${conn.connection.host}`);
  } catch (error) {
    console.log(`Error while connecting MONGODB ${error}`);
    process.exit(1);
  }
}
