//GIVING TLE

class Solution {
public:
    // Compare the computed sum string `final` with a "pattern" built from result:
    // - mapped letters are concrete digits in the pattern
    // - unmapped letters remain as letters in the pattern
    // We also pass `helper` to know which digits are already used by mapped letters,
    // so unknown result letters cannot reuse those digits.
    bool compare(const std::string& final, const std::string& pattern,
                 const std::vector<int>& usedGlobal) {
        if (final.size() != pattern.size()) return false;

        std::vector<int> used = usedGlobal;          // copy of used digits (0..9)
        std::unordered_map<char,char> bindUnknown;   // result-letter -> digit

        for (int i = 0; i < (int)final.size(); ++i) {
            char p = pattern[i];
            char d = final[i]; // digit from computed sum

            if (p >= '0' && p <= '9') {
                // Known (mapped) result letter: must match exactly
                if (d != p) return false;
            } else {
                // Unknown result letter: bind consistently and uniquely
                if (bindUnknown.count(p)) {
                    if (bindUnknown[p] != d) return false;
                } else {
                    // cannot reuse any digit already used by mapped letters
                    if (used[d - '0']) return false;
                    // result's leading letter cannot be 0
                    if (i == 0 && d == '0') return false;
                    bindUnknown[p] = d;
                    used[d - '0'] = 1;
                }
            }
        }
        return true;
    }

    bool solve(std::vector<std::string>& words, std::string& result,
               std::unordered_map<char,int>& mp, std::vector<int>& used) {

        // Pick exactly one next unmapped char from words and try all digits for it
        for (auto& w : words) {
            for (char ch : w) {
                if (mp.find(ch) == mp.end()) {
                    for (int val = 0; val <= 9; ++val) {
                        if (used[val] == 0) {
                            if (ch == w[0] && val == 0) continue; // no leading zero for any word
                            mp[ch] = val; used[val] = 1;
                            if (solve(words, result, mp, used)) return true;
                            used[val] = 0; mp.erase(ch);
                        }
                    }
                    return false; // stop after handling this single char
                }
            }
        }

        // All letters from words are assigned: compute sum
        long long sum = 0;
        for (auto& w : words) {
            long long cur = 0;
            for (char ch : w) cur = cur * 10 + mp[ch];
            sum += cur;
        }
        std::string final = std::to_string(sum);

        // Build pattern from result: mapped letters -> digit char; unmapped -> keep the letter
        std::string pattern; pattern.reserve(result.size());
        for (char ch : result) {
            auto it = mp.find(ch);
            if (it != mp.end()) pattern.push_back(char('0' + it->second));
            else                pattern.push_back(ch); // keep letter (do NOT use '*')
        }

        return compare(final, pattern, used);
    }

    bool isSolvable(std::vector<std::string>& words, std::string result) {
        std::unordered_map<char,int> mp;
        std::vector<int> used(10, 0);
        return solve(words, result, mp, used);
    }
};
