class Solution {
public:
    string minWindow(string s, string t) {
        int l=0,minL=INT_MAX;
        int idx=-1;
        int cnt=0;
        unordered_map<char,int> m;
        for(auto &ch:t) m[ch]++;
        int size=m.size();
        for(int k=0;k<s.size();k++){
            if(m.find(s[k])!=m.end()) {
                m[s[k]]--;
                if(m[s[k]]==0) cnt++;
            }
            while(cnt==size){
                if(k-l+1<minL){
                    idx=l;
                    minL=k-l+1;
                }
                if(m.find(s[l])!=m.end()){
                    if(m[s[l]]==0) cnt--;    
                    m[s[l]]++;
                } 
                l++;
            }
        }

        return idx==-1?"":s.substr(idx,minL);
    }
};


#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <functional>
#include <utility>

class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        long long MOD = 1e9 + 7;

        std::vector<std::vector<long long>> dp(m, std::vector<long long>(n, 0));

        std::vector<std::vector<std::vector<std::pair<int, int>>>> memo(
            m, std::vector<std::vector<std::pair<int, int>>>(
                   n, std::vector<std::pair<int, int>>(2, {-2, -2})));

        std::function<std::pair<int, int>(int, int, int)> find_landing_spot =
            [&](int r, int c, int dir) -> std::pair<int, int> {
            if (memo[r][c][dir].first != -2) {
                return memo[r][c][dir];
            }

            int res_r = -1, res_c = -1;
            if (dir == 0) { // right
                int next_c = c + 1;
                if (next_c < n) {
                    if (grid[r][next_c] == 0) {
                        res_r = r;
                        res_c = next_c;
                    } else {
                        auto landing_spot = find_landing_spot(r, next_c, 1);
                        res_r = landing_spot.first;
                        res_c = landing_spot.second;
                    }
                }
            } else { // down
                int next_r = r + 1;
                if (next_r < m) {
                    if (grid[next_r][c] == 0) {
                        res_r = next_r;
                        res_c = c;
                    } else {
                        auto landing_spot = find_landing_spot(next_r, c, 0);
                        res_r = landing_spot.first;
                        res_c = landing_spot.second;
                    }
                }
            }
            return memo[r][c][dir] = {res_r, res_c};
        };

        dp[0][0] = 1;

        for (int r = 0; r < m; ++r) {
            for (int c = 0; c < n; ++c) {
                if (dp[r][c] == 0) continue;

                // Move Right from (r,c)
                auto dest_r = find_landing_spot(r, c, 0);
                if (dest_r.first != -1) {
                    dp[dest_r.first][dest_r.second] = (dp[dest_r.first][dest_r.second] + dp[r][c]) % MOD;
                }

                // Move Down from (r,c)
                auto dest_d = find_landing_spot(r, c, 1);
                if (dest_d.first != -1) {
                    dp[dest_d.first][dest_d.second] = (dp[dest_d.first][dest_d.second] + dp[r][c]) % MOD;
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};


