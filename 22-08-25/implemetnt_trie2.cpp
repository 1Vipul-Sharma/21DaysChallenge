#include <bits/stdc++.h> 
class Trie{

    public:
        class TrieNode{
        public:
            TrieNode* arr[26];
            int Pcnt;
            int Ccnt;
            TrieNode(){
                Ccnt=0;
                Pcnt=1;
                for(int i=0;i<26;i++) 
                    arr[i]=NULL;
            }
        };

    TrieNode *node;

    Trie(){
        // Write your code here.
        node = new TrieNode();
    }

    void insert(string &word){
        // Write your code here.
        TrieNode* root=node;
        for(auto &ch:word){
            if(root->arr[ch-'a']==NULL){
                root->arr[ch-'a']=new TrieNode();
            }
            root=root->arr[ch-'a'];
            root->Pcnt+=1;
        }
        root->Ccnt+=1;
    }

    int countWordsEqualTo(string &word){
        // Write your code here.
        TrieNode* root=node;
        for(auto &ch:word){
            if(root->arr[ch-'a']==NULL) return 0;
            root=root->arr[ch-'a'];
        }
        return root->Ccnt;
    }

    int countWordsStartingWith(string &word){
        // Write your code here.
        TrieNode* root=node;
        for(auto &ch:word){
            if(root->arr[ch-'a']==NULL) return 0;
            root=root->arr[ch-'a'];
        }
        return root->Pcnt;
    }

    void erase(string &word){
        TrieNode* temp=node;

         std::vector<TrieNode*> nodes;

        for(char c:word){

            int index=c-'a';

            if (temp->arr[index]==NULL) {

                return;

            }

            

            nodes.push_back(node);

             temp=temp->arr[index];

             node->Pcnt-=1;

        }

          node->Ccnt -= 1;

    }
};
