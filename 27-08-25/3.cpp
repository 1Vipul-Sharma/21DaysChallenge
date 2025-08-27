class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int l = 0, maxLen = 0;
        vector<int> arr(256,0);
        for (int r = 0; r < n; r++) {
            arr[s[r]]++;
            while(arr[s[r]]>1){
                arr[s[l]]--;
                l++;
            }
            maxLen=max(maxLen,r-l+1);
        }
        return maxLen;
    }
};