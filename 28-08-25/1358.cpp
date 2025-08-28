class Solution {
public:
    int numberOfSubstrings(string s) {
        int res=0;
        vector<int> temp(3,-1);
        for(int i=0;i<s.size();i++){
            temp[s[i]-'a']=i;
            res+=1+min(temp[0],min(temp[1],temp[2]));
        }
        return res;
    }
};