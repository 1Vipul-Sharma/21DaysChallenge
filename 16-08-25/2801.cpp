// Giving TLE 
//learn DIgit DP then try it again
class Solution {
public:
const int MOD=1e9+7;
bool liesInRange(const string& num, const string& low, const string& high) {
    if(num.size() < low.size() || num.size() > high.size()) return false;
    if(num.size() == low.size() && num < low) return false;
    if(num.size() == high.size() && num > high) return false;
    return true;
}

void dfs(string curr, const string& low, const string& high, int& res) {
    // Prune if larger than high
    if(curr.size() > high.size() || (curr.size() == high.size() && curr > high)) 
        return;

    // Count if in range
    if(liesInRange(curr, low, high)) {
        res = (res + 1) % MOD;
    }

    int last = curr.back() - '0';
    if(last > 0) dfs(curr + char(last - 1 + '0'), low, high, res);
    if(last < 9) dfs(curr + char(last + 1 + '0'), low, high, res);
}

int countSteppingNumbers(string low, string high) {
    int res = 0;
    for(char ch = '1'; ch <= '9'; ch++) {
        dfs(string(1, ch), low, high, res);
    }
    if(low == "0") res = (res + 1) % MOD; // include 0 explicitly
    return res;
}

};