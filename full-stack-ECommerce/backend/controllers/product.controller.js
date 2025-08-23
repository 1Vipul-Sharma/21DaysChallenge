import Product from "../models/product.model.js";
import { redisClient } from "../lib/redis.js";
import cloudinary from "../lib/cloudinary.js";

export const getAllProducts = async (req, res) => {
  try {
    const products = await Product.find({});
    res.json({ products });
  } catch (error) {
    console.log(`Error in getAllproducts cont.`, error.message);
    res.status(500).json({ message: "Server Error" });
  }
};

export const getFeaturedProducts = async (req, res) => {
  try {
    const cacheKey = "featuredProducts";

    // 1. Check Redis cache
    const cachedData = await redisClient.get(cacheKey);
    if (cachedData) {
      console.log("Serving from Redis cache ✅");
      return res.status(200).json(JSON.parse(cachedData));
    }

    // 2. If not cached, fetch from MongoDB
    const featuredProducts = await Product.find({ isFeatured: true });

    if (!featuredProducts || featuredProducts.length === 0) {
      return res.status(404).json({ message: "No featured products found" });
    }

    // 3. Store in Redis (set with TTL of 1 hour for example)
    await redisClient.set(cacheKey, JSON.stringify(featuredProducts), {
      EX: 3600, // 1 hour
    });

    console.log("Serving from MongoDB & storing in Redis ✅");
    res.status(200).json(featuredProducts);
  } catch (error) {
    console.error("Error fetching featured products:", error);
    res.status(500).json({ message: "Server error" });
  }
};

export const createProduct = async (req, res) => {
  try {
    const { name, description, price, image, category } = req.body;
    let cloudinaryResponse = null;
    if (image) {
      cloudinaryResponse = await cloudinary.uploader.upload(image, {
        folder: "products",
      });
    }
    const product = await Product.create({
      name,
      description,
      price,
      image: cloudinaryResponse?.secure_url
        ? cloudinaryResponse.secure_url
        : "",
      category,
    });
    res.status(201).json(product);
  } catch (error) {
    console.log(`Error in createProduct Controller`, error.message);
    res.status(500).json({ message: "Server Error" });
  }
};

export const deleteProduct = async (req, res) => {
  try {
    const product = await Product.findById(req.params.id);
    if (!product) {
      return res.status(404).json({ message: `Product not found` });
    }
    if (product.image) {
      const publicId = product.image.split("/").pop().splits(".")[0];
      try {
        await cloudinary.uploader.destroy(`products/${publicId}`);
        console.log(`Deleted image from cloudinary`);
      } catch (error) {
        console.log(`error deleting image from cloudinary`, error);
        res.status(500).json({ message: `Server Error` });
      }
    }
    await Product.findByIdAndDelete(req.params.id);
    res.status(200).json({ message: `Product Deleted Successfully` });
  } catch (error) {}
};

export const getRecommendedProducts = async (req, res) => {
  try {
    const products = await Product.aggregate([
      {
        $sample: { size: 3 },
      },
      {
        $project: {
          _id: 1,
          name: 1,
          description: 1,
          image: 1,
          price: 1,
        },
      },
    ]);

    res.status(200).json(products);
  } catch (error) {
    console.log(`Error in getRecommendedProducts`, error.message);
    res.json(500).json({ message: `Server Error` });
  }
};

export const getProductsByCategory = async (req, res) => {
  try {
    const { category } = req.params;
    const products = await Product.find({ category });
    res.status(200).json(products);
  } catch (error) {
    console.log(`Error in getProductsByCategory controller ${error.message}`);
    res.status(500).json({ message: `Server Error` });
  }
};

export const toggleFeaturedProduct = async (req, res) => {
  try {
    const product = await Product.findById(req.params.id);
    if (product) {
      product.isFeatured = !product.isFeatured;
      const updatedProduct = await product.save();
      await updateFeaturedProductsCache();
      res.json(updatedProduct);
    } else {
      res.status(404).json({ message: "Product not found" });
    }
  } catch (error) {
    console.log(`Error in toggleFeaturedProduct : ${error.message}`);
    res.status(500).json({ message: `Server Error` });
  }
};

const updateFeaturedProductsCache = async () => {
  try {
    const featuredProducts = await Product.find({ isfeatured: true });
    await redisClient.set("featuredProducts", JSON.stringify(featuredProducts));
  } catch (error) {
    console.log(`Error in updateFeaturedProductsCache : ${error}`);
    res.status(500).json({ message: `Server Error` });
  }
};
