#include<bits/stdc++.h>
int kDistinctChars(int k, string &str)
{
    // Write your code here
    unordered_map<char,int> hash;
    int l=0,maxLen=0;
    for(int r=0;r<str.size();r++){
        hash[str[r]]++;
        if(hash.size()>k){
            hash[str[l]]--;
            if(hash[str[l]]==0) hash.erase(str[l]);
            l++;
        }
        maxLen=max(maxLen,r-l+1);
    }
    return maxLen;
}


