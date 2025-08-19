// KIND OF FRONT PARTITION
class Solution {
public:
    int solve(vector<int>& arr,int idx,int k,vector<int>& dp){
        if(idx==arr.size()) return 0;
        if(dp[idx]!=-1) return dp[idx];
        long long res=0;
        int maxi=0;
        for(int i=idx; i < min((int)arr.size(), idx + k);i++){
            maxi=max(maxi,arr[i]);
            long long curr=maxi*(i-idx+1) +solve(arr,i+1,k,dp);
            res=max(res,curr);
        }
        return dp[idx]=res;
    }
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        vector<int> dp(arr.size(),-1);
        return solve(arr,0,k,dp);
    }
};