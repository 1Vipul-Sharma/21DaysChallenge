class Solution {
public:
    bool isPallindrome(string& s,int i,int j){
        while(i<j){
            if(s[i++]!=s[j--]) return false;
        }
        return true;
    }
    void solve(string& s,int idx,vector<string>& temp,vector<vector<string>>& res){
        if(idx==s.size()){
            res.push_back(temp);
            return ;
        }
        string curr="";
        for(int i=idx;i<s.size();i++){
            curr+=s[i];
            if(isPallindrome(s,idx,i)){
                temp.push_back(curr);
                solve(s,i+1,temp,res);
                temp.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> temp;
        solve(s,0,temp,res);
        return res;
    }
};

time complexity: (Number of States) x (Work per State).
time - O(n*2^n)
space - O(2^n)