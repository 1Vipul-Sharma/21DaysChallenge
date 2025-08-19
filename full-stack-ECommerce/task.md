# signup login logout routes add kar

    - routes and controllers nam ke naye folder bnaye
    - controllers me basically koi particular route hit hone par what we are going to do wo sab rehta h

# DB se connect karo

    - for that we are using mongoose package will help us in interacting with database easily

<!-- USER RELATED -->

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

# login Route controller - simple check if email and password is valid

    -if yes just generate , set n send the tokens

# logout route

    - remove tokens from redis
    - remove tokens from cookies

# regenerate access token

    -check req me jo refreshtoken h n jo redis me save h same h
    - if yes generate access token set in redis n cokkies again

<!-- PRODUCT RELATED -->

# getAllproducts route

    - added middleware for protectedroute(get user)
    - user should be admin

# getFeaturedProduct route

    -get from redis if not from mongo but store it in redis then it is frequent transaction so just save it in redis

# addProduct

<!-- by 21 i have to complete backend part -->
