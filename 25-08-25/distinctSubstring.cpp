/*You are required to complete this method */
// int countDistinctSubstring(string s) {
//     // Your code here
    
// }

struct TrieNode {
    unordered_map<char, TrieNode*> next;
    ~TrieNode() {
        for (auto& kv : next) delete kv.second;
    }
};

int countDistinctSubstring(string s) {
    auto* root = new TrieNode();
    int res = 0;

    for (int i = 0; i < (int)s.size(); ++i) {
        TrieNode* node = root;
        for (int j = i; j < (int)s.size(); ++j) {
            char c = s[j];
            if (node->next.find(c) == node->next.end()) {
                node->next[c] = new TrieNode();
                ++res;
            }
            node = node->next[c];
        }
    }
    delete root;
    return res + 1;
}
