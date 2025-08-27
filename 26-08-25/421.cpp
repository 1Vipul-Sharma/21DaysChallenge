#include <bits/stdc++.h>
using namespace std;

class TrieNode {
public:
    TrieNode* children[2];
    TrieNode() {
        children[0] = NULL;
        children[1] = NULL;
    }
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }

    int insertAndFindXOR(int num) {
        TrieNode* node = root;
        TrieNode* xorNode = root;
        int currXor = 0;

        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;

            // insert
            if (node->children[bit] == NULL) {
                node->children[bit] = new TrieNode();
            }
            node = node->children[bit];

            // check XOR path
            if (xorNode->children[1 - bit] != NULL) {
                currXor |= (1 << i); // opposite bit exists, maximize XOR
                xorNode = xorNode->children[1 - bit];
            } else {
                xorNode = xorNode->children[bit];
            }
        }
        return currXor;
    }
};

class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        Trie* trie = new Trie();
        int res = 0;

        // Insert first number separately (to have something to XOR with)
        trie->insertAndFindXOR(nums[0]);

        for (int i = 1; i < nums.size(); i++) {
            res = max(res, trie->insertAndFindXOR(nums[i]));
        }
        return res;
    }
};