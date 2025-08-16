# signup login logout routes add kar

    - routes and controllers nam ke naye folder bnaye
    - controllers me basically koi particular route hit hone par what we are going to do wo sab rehta h

# DB se connect karo

    - for that we are using mongoose package will help us in interacting with database easily

# Create a model for user

    - Read about mongoose and model usage
    - Model me pre password encryption functionality add kari h
    - password compare karne ke lie add kia h

# Signup Route controller

    - simply if user exist then no signup
    - other add new user to the database

# add redis functionality in Signup controller

    - generate access n refresh token
    - store refresh token in redis
    - set res.cookies for the refresh n access tokens
