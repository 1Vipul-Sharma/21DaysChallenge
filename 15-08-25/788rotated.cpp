//learn Digits DP
//Dgits Dp se bhi karna h


class Solution {
public:
    int solve(int n){
        bool flag=false;
        while(n){
            int rem=n%10;
            if(rem==3 || rem==4 || rem==7) return 0;
            if(rem==2 || rem==5 || rem==6 || rem==9) flag=true;
            n=n/10;
        }
        return flag==true ? 1:0;
    }
    int rotatedDigits(int n) {
        if(n==1) return 0;
        int res=rotatedDigits(n-1);
        return res+solve(n);
    }
};

tc-O(n)
sc-O(n) recursive stack space
