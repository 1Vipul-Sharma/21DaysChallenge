class Solution {
public:
    int numSubmat(vector<vector<int>>& mat) {
        int m=mat.size();
        int n=mat[0].size();
        vector<vector<pair<int,int>>> temp(m,vector<pair<int,int>>(n,{0,0}));
        int res=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(mat[i][j]!=0){
                    int left= j-1>=0 ? temp[i][j-1].first:0;
                    int up= i-1>=0 ? temp[i-1][j].second:0;
                    temp[i][j].first = left+mat[i][j];
                    temp[i][j].second = up+mat[i][j];
                    res+=temp[i][j].first+temp[i][j].second-1;
                }
                cout<<i<<" "<<j<<" "<<temp[i][j].first<<" "<<temp[i][j].second<<" "<<res<<endl;
            }
        }
        int ans=0;
        for (int r1 = 0; r1 < m; ++r1) {
            vector<int> col(n, 1);
            for (int r2 = r1; r2 < m; ++r2) {
                for (int j = 0; j < n; ++j)
                    col[j] &= (mat[r2][j] == 1);

                int height = r2 - r1 + 1;
                if (height >= 2) {
                    // Count runs of consecutive 1s; in a run of length L,
                    // number of subarrays with width >= 2 is L*(L-1)/2
                    int run = 0;
                    for (int j = 0; j < n; ++j) {
                        if (col[j]) ++run;
                        if (!col[j]) {
                            if (run >= 2) ans += 1LL * run * (run - 1) / 2;
                            run = 0;
                        }
                    }
                    if (run >= 2) ans += 1LL * run * (run - 1) / 2;
                }
            }
        }
        return ans+res;
    }
};