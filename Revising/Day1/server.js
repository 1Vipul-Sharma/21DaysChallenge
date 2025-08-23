import express from "express";

const app = express();

app.use((req, res, next) => {
  // wrap res.json to always add a timestamp
  const originalJson = res.json;
  res.json = (data) => {
    data.timestamp = new Date();
    return originalJson.call(res, data);
  };
  next();
});

app.get("/books", (req, res) => {
  res.json({ id: 1, name: "Vipul" });
});

app.get("/", (req, res) => {
  res.send(`Helloooo !!`);
});
app.get("/user/:id", (req, res) => {
  const { id } = req.params;
  res.send(`Id is ${pasta}`);
});

app.get("/search", (req, res) => {
  console.log(req.query);
  res.send(req.query);
});

app.listen(8000, () => {
  console.log(`Server is listening at http://localhost:8000`);
});
