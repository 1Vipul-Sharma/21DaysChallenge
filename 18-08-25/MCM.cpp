class Solution {
  public:
    int solve(vector<int>& arr,int i,int j,vector<vector<int>>& memo){
        if(i==j) return 0;
        if(memo[i][j]!=-1) return memo[i][j];
        int res=INT_MAX;
        for(int k=i;k<j;k++){
            int curr=solve(arr,i,k,memo)+solve(arr,k+1,j,memo) + arr[i-1]*arr[k]*arr[j];
            res=min(res,curr);
        }
        return memo[i][j]=res;
    }
    int matrixMultiplication(vector<int> &arr) {
        // code here
        int n=arr.size();
        vector<vector<int>> dp(n,vector<int>(n,0));
        for(int i=n-1;i>0;i--){
            for(int j=i+1;j<n;j++){
                int res=INT_MAX;
                for(int k=i;k<j;k++){
                    int curr=dp[i][k]+dp[k+1][j] + arr[i-1]*arr[k]*arr[j];
                    res=min(res,curr);
                    dp[i][j]=res;
                }       
            }
        }
        return dp[1][n-1];
    }
};

TC - O(n^3)
SC- O(n^3)