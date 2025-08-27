import express from "express";
import { connectDB } from "./lib/db.js";
import BookRoutes from "./routes/book.route.js";
import dotenv from "dotenv";

dotenv.config();

const app = express();
// Middleware to parse JSON body
app.use(express.json());

app.use("/api/book", BookRoutes);

// Global Error Handling Middleware
app.use((err, req, res, next) => {
  console.error("Error stack:", err.stack); // logs the full error
  console.error("Route that caused error:", req.originalUrl); // logs route path

  res.status(err.status || 500).json({
    success: false,
    message: err.message || "Internal Server Error",
    route: req.originalUrl, // tells which route failed
    method: req.method, // tells which method failed (GET, POST, etc.)
  });
});

const PORT = process.env.PORT || 5000;

app.listen(PORT, () => {
  console.log(`Server is listening at http://localhost:${PORT}`);
  connectDB();
});
