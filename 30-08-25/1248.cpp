class Solution {
public:
    int find(vector<int>& nums,int k){
        if(k<0)return 0;
        int l=0;
        int res=0,cnt=0;
        for(int r=0;r<nums.size();r++){
            if(nums[r]%2) cnt++;
            while(cnt>k){
                cnt-=nums[l]%2 ?1:0;
                l++;
            }
            res+=r-l+1;
        }
        return res;
    }
    int numberOfSubarrays(vector<int>& nums, int k) {
     return find(nums,k)-find(nums,k-1);   
    }
};