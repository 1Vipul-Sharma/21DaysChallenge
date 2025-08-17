#include <bits/stdc++.h> 
void generate(long long num,int l,int r,vector<int>& res){
    if(num>r) return ;
    if(num>=l && num<=r) res.push_back((int)num);
    int lastdigit=num%10;
    if(lastdigit>0)
        generate(num*10+(lastdigit-1),l,r,res);
    if(lastdigit<9)
        generate(num*10+(lastdigit+1),l,r,res);
}
vector<int> findSteppingNumbers(int l, int r) {
	// Write your code here.
    vector<int> res;
    for(int i=1;i<=9;i++){
        generate(i,l,r,res);
    }
    sort(res.begin(),res.end());
    return res;
}




tC-O(9*(2^0+2^1+...+2^k-1)) => O(9*2^k);
sC-O(k);

k = height of the tree formed