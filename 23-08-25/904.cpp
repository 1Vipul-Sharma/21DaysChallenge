class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int l=0;
        int maxLen =0;
        int n=fruits.size();
        int cnt1=0,cnt2=0,ele1=-1,ele2=-1;
        for(int k=0;k<n;k++){
            //include current element into logic 
            if(ele1==-1 || ele1==fruits[k]){
                ele1=fruits[k];
                cnt1++;
            }
            else if(ele2==-1 || ele2==fruits[k]){
                ele2=fruits[k];
                cnt2++;
            }

            while(fruits[k]!=ele1 && fruits[k]!=ele2){
                if(fruits[l]==ele1){
                    cnt1--;
                }
                else if(fruits[l]==ele2){
                    cnt2--;
                }
                if(cnt1==0){
                    ele1=fruits[k];
                    cnt1+=1;
                }
                else if(cnt2==0){
                    ele2=fruits[k];
                    cnt2+=1;
                }
                l++;
            }
            maxLen=max(maxLen,k-l+1);
        }
        return maxLen;
    }
};