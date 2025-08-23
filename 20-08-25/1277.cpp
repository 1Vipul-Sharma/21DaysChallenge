class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m=matrix.size();
        int n=matrix[0].size();
        int res=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(matrix[i][j]==0) continue;
                else{
                   int upper= i-1>=0?matrix[i-1][j]:0;
                   int left= j-1>=0?matrix[i][j-1]:0;
                   int d=(i-1>=0 &&j-1>=0)?matrix[i-1][j-1]:0;
                   matrix[i][j]+=min(upper,min(left,d));
                   res+=matrix[i][j];
                }
            }
        }
        return res;
    }
};