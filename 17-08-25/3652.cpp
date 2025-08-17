//Question from contest
class Solution {
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n=prices.size();
        long long baseProfit=0;
        for(int i=0;i<n;i++){
            baseProfit+=1LL*strategy[i]*prices[i];
        }
        vector<long long>pS(n+1,0),pP(n+1,0);
        for(int i=0;i<n;i++){
            pS[i+1]=pS[i]+ 1LL*strategy[i]*prices[i];
            pP[i+1]=pP[i]+prices[i];
        }
        long long res=0;
        for(int i=0;i+k<=n;i++){
            int mid=i+k/2;
            long long oC=pS[i+k]-pS[i];
            long long nC=pP[i+k] -pP[mid];
            long long gain=nC-oC;
            res=max(res,gain);
        }
        return baseProfit+res;
    }
};