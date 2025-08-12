//Got kind of rough idea for the trie data structure
//basically used for storing same kind of string in order to insert and search in a better complexity
//Har level par 26 character rakh rhe h 

class Trie {
private:
    class TrieNode{
        public:
            TrieNode* children[26];
            bool isEnd;
            TrieNode(){
                isEnd=false;
                for(int i=0;i<26;i++) children[i]=nullptr;
            }
    };
    TrieNode* root;
public:
    Trie() {
        root=new TrieNode();
    }
    
    void insert(string word) {
        TrieNode* curr=root;
        for(auto& ch:word){
            if(curr->children[ch-'a']==nullptr){
                curr->children[ch-'a']=new TrieNode();
            }
            curr=curr->children[ch-'a'];
        }
        curr->isEnd=true;
    }
    
    bool search(string word) {
        TrieNode* curr=root;
        for(auto& ch:word){
            if(curr->children[ch-'a']==nullptr) return false;
            curr=curr->children[ch-'a'];
        }
        return curr->isEnd;
    }
    
    bool startsWith(string prefix) {
        TrieNode* curr=root;
        for(auto& ch:prefix){
            if(curr->children[ch-'a']==nullptr) return false;
            curr=curr->children[ch-'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */