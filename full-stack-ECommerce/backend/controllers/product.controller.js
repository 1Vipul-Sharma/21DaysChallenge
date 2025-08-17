import Product from "../models/product.model.js";
import { redisClient } from "../lib/redis.js";

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
