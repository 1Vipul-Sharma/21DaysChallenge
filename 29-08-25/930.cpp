class Solution {
public:
    int find(vector<int>& nums,int goal){
        if(goal<0) return 0;
        int res=0;
        int l=0;
        int curr=0;
        for(int r=0;r<nums.size();r++){
            curr+=nums[r];
            while(curr>goal){
                curr-=nums[l];
                l++;
            }
            res+=r-l+1;
        }
        return res;
    }
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return find(nums,goal)-find(nums,goal-1);
    }
};