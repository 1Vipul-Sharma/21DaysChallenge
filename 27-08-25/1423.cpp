https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/description/

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n=cardPoints.size();
        int Wsize=n-k;
        int l=0;
        int TotSum=accumulate(cardPoints.begin(),cardPoints.end(),0);
        if(Wsize==0) return TotSum;
        int sum=0,minSum=INT_MAX;
        for(int r=0;r<n;r++){
            sum+=cardPoints[r];
            if( r>=Wsize-1){
                minSum=min(minSum,sum);
                sum-=cardPoints[l++];
            }
        }
        return TotSum-minSum;
    }
};

T - O(n)
S - O(1)