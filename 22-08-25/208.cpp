class Trie {
public:
    class TrieNode{
    public:
        TrieNode* arr[26];
        bool flag;
        TrieNode(){
            flag=false;
            for(int i=0;i<26;i++) arr[i]=NULL;
        }
    };

    TrieNode* root;
    Trie() {
        root=new TrieNode();
    }
    
    void insert(string word) {
       TrieNode *node = root;
       for(auto& ch:word){
            if(node->arr[ch-'a']==NULL){
                node->arr[ch-'a']=new TrieNode();
            }
            node=node->arr[ch-'a'];
       } 
       node->flag = true;
    }
    
    bool search(string word) {
        TrieNode *node=root;
        for(auto &ch:word){
            if(node->arr[ch-'a']==NULL) return false;
            node=node->arr[ch-'a'];
        }
        return node->flag;
    }
    
    bool startsWith(string prefix) {
        TrieNode *node=root;
        for(auto &ch:prefix){
            if(node->arr[ch-'a']==NULL) return false;
            node=node->arr[ch-'a'];
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