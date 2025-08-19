class Solution {
public:
    int solve(vector<int>& cuts,int i,int j,vector<vector<int>>& memo){
        if(i>j) return 0;
        if(memo[i][j]!=-1) return memo[i][j];
        int res=INT_MAX;
        for(int k=i;k<=j;k++){
            int curr=cuts[j+1]-cuts[i-1] + solve(cuts,i,k-1,memo)+solve(cuts,k+1,j,memo);
            res=min(res,curr);
        }
        return memo[i][j]=res;
    }
    int minCost(int n, vector<int>& cuts) {
        cuts.insert(cuts.begin(), 0);
        cuts.push_back(n);
        sort(cuts.begin(),cuts.end());
        int idx=cuts.size()-2;
        vector<vector<int>> dp(idx+2,vector<int>(idx+2,0));
        for(int i=idx;i>=1;i--){
            for(int j=1;j<=idx;j++){
                if(i>j) continue;
                else{
                    dp[i][j]=INT_MAX;
                    for(int k=i;k<=j;k++){
                        int curr=cuts[j+1]-cuts[i-1]+dp[i][k-1]+dp[k+1][j];
                        dp[i][j]=min(dp[i][j],curr);
                    }
                }
            }
        }
        return dp[1][idx];
    }
};


tC -O(n^3)
sc- O(n^3)