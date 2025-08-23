middleware - Middleware functions are functions that have access to req, res, and next.

Types: 1. Built-in middleware

       - express.json() → parse JSON body
       - express.urlencoded({ extended: true }) → parse form data

    2. Third-party middleware

        -Install and use packages.
        -Example: morgan (logging)

    3. Custom middleware

        -Define your own logic:

//Params

    app.get("/books/:id", (req, res) => {
    const { id } = req.params;
    res.send(`Book ID is ${id}`);
    });

//query

    app.get("/search", (req, res) => {
    const { author, year } = req.query;
    res.send(`Searching for books by ${author} in ${year}`);
    });
