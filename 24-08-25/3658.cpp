class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        int sumOdd=0,sumEven=0;
        int a=1,b=2;
        while(n>0){
            sumOdd+=a;
            sumEven+=b;
            a+=2;
            b+=2;
            n-=1;
        }
        return __gcd(sumOdd, sumEven);
    }
};