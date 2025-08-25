// Trie 
class Trie{
public:
    class TrieNode{
    public:
        unordered_map<char,TrieNode*> children;
        bool flag;
        TrieNode(){
            flag=false;
        }    
    };
    TrieNode *node;
    Trie(){
        node=new TrieNode();
    }
    void fill(string &word){
        TrieNode* root=node;
        for(auto &ch:word){
            if(root->children.find(ch)==root->children.end()){
                root->children[ch]=new TrieNode();
            }
            root=root->children[ch];
        }
        root->flag=true;
    }
    bool check(string &word){
        TrieNode* root=node;
        for(auto &ch:word){
            root=root->children[ch];
            if(root->flag==false) return false;
        }
        return true;
    }
};
class Solution {
  public:
    string longestString(vector<string> &words) {
        // code here
        Trie *TrieObj=new Trie();
        for(auto &word:words){
            TrieObj->fill(word);
        }
        string res="";
        for(auto &word:words){
            if(TrieObj->check(word)){
                if(word.size()>res.size()) res=word;
                else if(word.size()==res.size()) res=min(res,word);
            }
        }
        return res;
    }
};