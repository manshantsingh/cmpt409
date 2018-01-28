#include <bits/stdc++.h>
using namespace std;

int n, gap;
vector<int> pos;

bool cmp(int i, int j){
    if(pos[i]==pos[j]){
        i+=gap; j+=gap;
        if(i>=n || j>=n) return true;
    }
    return pos[i]<pos[j];
}

int main(){
    int t; cin>>t;
    while(t--){
        string s;
        cin>>n>>s;
        s+=s+(char)CHAR_MAX;
        n=s.size();
        vector<int> sa(n), tmp(n);
        pos.resize(n);
        for(int i=0;i<n;i++) sa[i]=i, pos[i]=s[i];
        for(gap=1;;gap*=2){
            sort(sa.begin(), sa.end(), cmp);
            tmp[0]=0;
            for(int i=1;i<n;i++) tmp[i]=tmp[i-1]+cmp(sa[i-1], sa[i]);
            for(int i=0;i<n;i++) pos[sa[i]]=tmp[i];
            if(tmp[n-1]==n-1) break;
        }
        cout<<sa[0]<<endl;
    }
}