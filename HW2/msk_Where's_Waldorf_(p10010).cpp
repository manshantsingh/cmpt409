#include <bits/stdc++.h>
using namespace std;
using namespace std::placeholders;

int n, gap;

bool cmp(int i, int j, const vector<int>& pos){
    if(pos[i]==pos[j]){
        i+=gap; j+=gap;
        if(i>=n || j>=n) return i>j;
    }
    return pos[i]<pos[j];
}

void buildSA(const string& s, vector<int>& sa, vector<int>& pos){
    n=s.size();
    vector<int> tmp(n);
    for(int i=0;i<n;i++) sa[i]=i, pos[i]=s[i];
    for(gap=1;;gap*=2){
        sort(sa.begin(), sa.end(), bind(cmp,_1,_2, pos));
        tmp[0]=0;
        for(int i=1;i<n;i++) tmp[i]=tmp[i-1]+cmp(sa[i-1], sa[i],pos);
        for(int i=0;i<n;i++) pos[sa[i]]=tmp[i];
        if(tmp[n-1]==n-1) break;
    }
}

int main(){
    int t; cin>>t;
    bool first=true;
    while(t--){
        if(first) first=false;
        else cout<<endl;

        int r,c; cin>>r>>c>>ws;
        vector<string> grid(r);
        vector<vector<pair<int,int>>> coord;

        // horizontal read automatically
        for(int i=0;i<grid.size();i++){
            cin>>grid[i];
            for(char& c: grid[i]) c=tolower(c);
            coord.emplace_back(grid[i].size());
            auto& v=coord.back();
            for(int j=0;j<v.size();j++) v[j]={i,j};
        }

        // vertical
        for(int i=0;i<c;i++){
            ostringstream oss;
            coord.push_back({});
            for(int j=0;j<r;j++) oss<<grid[j][i], coord.back().push_back({j,i});
            grid.push_back(oss.str());
        }

        // SouthEast diagnals
        for(int i=0;i<r;i++){
            ostringstream oss;
            coord.push_back({});
            for(int j=i,k=0; j<r && k<c; j++,k++) oss<<grid[j][k], coord.back().push_back({j,k});
            grid.push_back(oss.str());
        }
        for(int i=1;i<c;i++){
            ostringstream oss;
            coord.push_back({});
            for(int j=0,k=i; j<r && k<c; j++,k++) oss<<grid[j][k], coord.back().push_back({j,k});
            grid.push_back(oss.str());
        }

        //SouthWest diagnals
        for(int i=0;i<r;i++){
            ostringstream oss;
            coord.push_back({});
            for(int j=i,k=0; j>=0 && k<c; j--,k++) oss<<grid[j][k], coord.back().push_back({j,k});
            grid.push_back(oss.str());
        }
        for(int i=1;i<c;i++){
            ostringstream oss;
            coord.push_back({});
            for(int j=r-1,k=i; j>=0 && k<c; j--,k++) oss<<grid[j][k], coord.back().push_back({j,k});
            grid.push_back(oss.str());
        }

        int size=grid.size();
        vector<vector<int>> sa, pos;
        for(auto& s: grid){
            int x=s.size();
            sa.emplace_back(x);
            pos.emplace_back(x);
            buildSA(s, sa.back(), pos.back());
        }

        int q; cin>>q;
        while(q--){
            string word; cin>>word;
            for(auto& c: word) c=tolower(c);
            string rev = word;
            reverse(rev.begin(), rev.end());
            int len=word.size();
            bool found=false;
            for(int i=0;i<size;i++){
                auto &_s=grid[i];

                // binary search the suffix array
                int a=0, b=sa[i].size()-1;
                while(a<=b){
                    int v;
                    int mid=(a+b)/2;
                    int x=sa[i][mid];
                    if(len<_s.size()-x) v=word.compare(_s.substr(x, len));
                    else v=word.compare(_s.substr(x));
                    if(v==0){
                        found=true;
                        auto p=coord[i][x];
                        cout<<p.first+1<<' '<<p.second+1<<endl;
                        break;
                    }
                    if(a==b) break;
                    if(v>0) a=mid+1;
                    else b=mid-1;
                }
                if(found) break;

                // binary search the suffix array on word reverse
                a=0; b=sa[i].size()-1;
                while(a<=b){
                    int v;
                    int mid=(a+b)/2;
                    int x=sa[i][mid];
                    if(len<_s.size()-x) v=rev.compare(_s.substr(x, len));
                    else v=rev.compare(_s.substr(x));
                    if(v==0){
                        found=true;
                        auto p=coord[i][x+len-1];
                        cout<<p.first+1<<' '<<p.second+1<<endl;
                        break;
                    }
                    if(a==b) break;
                    if(v>0) a=mid+1;
                    else b=mid-1;
                }
                if(found) break;
            }
        }
    }
}