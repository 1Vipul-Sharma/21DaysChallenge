class Solution {
public:
    bool partitionArray(vector<int>& nums, int k) {
        int n=nums.size();
        if(n%k!=0) return false;  
        int part=n/k;
        unordered_map<int,int> temp;
        for(int i=0;i<nums.size();i++){
            temp[nums[i]]++;
            if(temp[nums[i]]>part) return false;
        }
        return true;
    }
};