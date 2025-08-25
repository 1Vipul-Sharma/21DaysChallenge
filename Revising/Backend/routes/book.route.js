import express from "express";
import Book from "../models/book.model.js";
const router = express.Router();

// GET all books
router.get("/", async (req, res) => {
  const books = await Book.find({});
  res.status(200).json(books);
});

// POST a new book
router.post("/", async (req, res) => {
  try {
    const { name, category, quantity } = req.body;

    // Option 1: using Book.create()
    const newBook = await Book.create({ name, category, quantity });

    res.status(201).json(newBook);
  } catch (err) {
    res
      .status(400)
      .json({ message: "Failed to create book", error: err.message });
  }
});

router.delete("/:mongoId", async (req, res) => {
  try {
    const { mongoId } = req.params;

    // Delete the book
    const deletedBook = await Book.findByIdAndDelete(mongoId);

    if (!deletedBook) {
      return res.status(404).json({ message: "Book not found" });
    }

    res.status(200).json({ message: "Book deleted successfully", deletedBook });
  } catch (err) {
    res
      .status(500)
      .json({ message: "Error deleting book", error: err.message });
  }
});

router.patch("/:mongoId", async (req, res) => {
  try {
    const { mongoId } = req.params;
    const updates = req.body; // fields to update

    // Find the book and update only provided fields
    const updatedBook = await Book.findByIdAndUpdate(
      mongoId,
      { $set: updates },
      { new: true, runValidators: true } // return updated doc & validate schema
    );

    if (!updatedBook) {
      return res.status(404).json({ message: "Book not found" });
    }

    res.status(200).json(updatedBook);
  } catch (err) {
    console.log(err.message);

    res
      .status(400)
      .json({ message: "Failed to update book", error: err.message });
  }
});

// router.patch();

export default router;
