//IBH approach
// intentionaly did it with Recursion 
class Solution {
public:
    string helper(string& prev){
        int n=prev.size();
        string res="";
        for(int i=0;i<n;i++){
            int cnt=1;
            while(i+1<n && prev[i+1]==prev[i]){
                cnt++;
                i++;
            }
            res+=to_string(cnt);
            res+=prev[i];
        }
        return res;
    }
    string countAndSay(int n) {
        if(n==1) return "1";
        string res=countAndSay(n-1);
        return helper(res);
    }
};

TC - O(2^n)
// aat last level string can be of len 2*(n-1) for traversing this 
SC - o(2^n + recusrion stack space -O(n))