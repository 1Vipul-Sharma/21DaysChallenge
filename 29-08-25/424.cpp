class Solution {
public:
    int find(unordered_map<char,int>& map){
        int res=0;
        for(auto &ele:map){
            res=max(res,ele.second);
        }
        return res;
    }
    int characterReplacement(string s, int k) {
    //    count of all char
    //    max count also
    int res=0,maxC=0;
    int l=0;
    unordered_map<char,int> map;
    for(int r=0;r<s.size();r++){
        map[s[r]]++;
        maxC=max(maxC,map[s[r]]);
        while(r-l+1-maxC>k){
            map[s[l]]--;
            maxC=find(map);
            l++;
        }
        res=max(res,r-l+1);
    } 
        return res;
    }
};