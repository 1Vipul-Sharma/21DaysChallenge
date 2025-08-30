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