class Solution {
public:
    int find(vector<int>& nums,int k){
        if(k<0) return 0;
        unordered_map<int,int> m;
        int l=0;
        int res=0;
        for(int r=0;r<nums.size();r++){
            m[nums[r]]++;
            while(m.size()>k){
                m[nums[l]]--;
                if(m[nums[l]]==0) m.erase(nums[l]);
                l++;
            }
            res+=r-l+1;
        }
        return res;
    }
    int subarraysWithKDistinct(vector<int>& nums, int k) {
      return find(nums,k) - find(nums,k-1);  
    }
};