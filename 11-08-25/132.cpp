// for this i have to revise MCM
//19-08-25 

#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    bool isPallindrome(std::string& s, int i, int j) {
        while (i < j) {
            if (s[i++] != s[j--]) return false;
        }
        return true;
    }

    int solve(std::string& s, int idx, std::vector<int>& memo) {
        if (idx == s.size()) {
            return 0;
        }
        if (memo[idx] != -1) {
            return memo[idx];
        }

        int minPartitions = INT_MAX;
        for (int i = idx; i < s.size(); i++) {
            if (isPallindrome(s, idx, i)) {
                int remainingPartitions = solve(s, i + 1, memo);
                // if (remainingPartitions != INT_MAX) {
                    minPartitions = std::min(minPartitions, 1 + remainingPartitions);
                // }
            }
        }

        return memo[idx] = minPartitions;
    }

    int minCut(std::string s) {
        std::vector<int> memo(s.size(), -1);
        int totalPartitions = solve(s, 0, memo);
        return totalPartitions - 1;
    }
};
