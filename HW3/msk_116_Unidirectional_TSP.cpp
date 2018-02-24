//CMPT 409 Assignment 3
//Problem: Unidirectional TSP
//Team Members: Heather Li, Ekjot Singh Billing, Manshant Singh Kohli

#include <bits/stdc++.h>
using namespace std;

int main(){
    int m,n;
    while(cin>>m>>n){
        vector<vector<int>> grid(m, vector<int>(n)), dp(m, vector<int>(n));
        for(auto& x: grid) for(auto& y: x) cin>>y;

        for(int i=n-2;i>=0;i--){ //column
            for(int j=0;j<m;j++){ //row
                set<int> s{j, (j+1)%m, (j+m-1)%m};
                auto it=s.begin();
                int val=grid[*it][i+1];
                int index=*it;
                //find best path and record index
                while(++it != s.end()){
                    int newVal = grid[*it][i+1];
                    if(newVal < val){
                        val=newVal;
                        index=*it;
                    }
                }
                dp[j][i]=index;
                grid[j][i]+=val;
            }
        }

        int mm=0;
        for(int i=1;i<m;i++){ //row
            if(grid[i][0]<grid[mm][0]) mm=i;
        }
        cout<<mm+1;
        for(int i=0, x=mm;i<n-1;i++){ //row
            x=dp[x][i];
            cout<<' '<<x+1;
        }
        cout<<endl<<grid[mm][0]<<endl;
    }
}
