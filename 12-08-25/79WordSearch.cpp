class Solution {
public:
    vector<vector<int>> delta={{1,0},{-1,0},{0,1},{0,-1}};
    bool solve(vector<vector<char>>& board,string word,vector<vector<int>>& visited,int i,int j,int idx){
        if(idx==word.size()) return true;
        if(i<0 || j<0 || i>=board.size() || j>=board[0].size() || visited[i][j]!=-1 || board[i][j]!=word[idx]) return false;
        visited[i][j]=1;
        for(auto& ele:delta){
            if(solve(board,word,visited,i+ele[0],j+ele[1],idx+1)) return true;
        }
        visited[i][j]=-1;
        return false;
    }
    bool exist(vector<vector<char>>& board, string word) {
        int m=board.size();
        int n=board[0].size();
        vector<vector<int>> visited(m,vector<int>(n,-1));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(board[i][j]==word[0]){
                    if(solve(board,word,visited,i,j,0)==true)
                        return true;
                }
            }
        }
        return false;   
    }
};

Basically no of nodes ginte h total kitni h recursion me 
mainly kya hota h last wali level ke comparision me baki sari level me nodes kam rehti h to ham genrally last level ki total no of nodes gin lete h
jese ki ek que me last level me 4^L nodes h
Time complexity - 0( m*n* 4^L) where L is the length of word
Space - (m*n)