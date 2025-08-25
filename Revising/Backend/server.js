import express from "express";
import { connectDB } from "./lib/db.js";
import BookRoutes from "./routes/book.route.js";
import dotenv from "dotenv";

dotenv.config();

const app = express();
// Middleware to parse JSON body
app.use(express.json());

app.use("/api/book", BookRoutes);

const PORT = process.env.PORT || 5000;

app.listen(PORT, () => {
  console.log(`Server is listening at http://localhost:${PORT}`);
  connectDB();
});
