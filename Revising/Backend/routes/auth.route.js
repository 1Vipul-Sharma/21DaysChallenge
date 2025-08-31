import express from "express";

const router = express.Router();

router.post("/register", async (req, res) => {
  try {
    const { email, password } = req.body;
    if (email.length == 0 || password.length == 0)
      return res.status(404).json({ message: `Email and password required` });
  } catch (error) {}
});
router.post("/login", async (req, res) => {});

export default router;
