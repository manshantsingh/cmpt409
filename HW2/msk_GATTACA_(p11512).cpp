#include <bits/stdc++.h>
using namespace std;

int n, gap;
vector<int> pos;

bool cmp(int i, int j){
    if(pos[i]==pos[j]){
        i+=gap; j+=gap;
        if(i>=n || j>=n) return i>j;
    }
    return pos[i]<pos[j];
}

int main(){
    int t; cin>>t;
    while(t--){
        string s;
        cin>>s;
        n=s.size();

        // create the suffix array O(n*log2n)
        vector<int> sa(n), tmp(n), lcp(n);
        pos.resize(n);
        for(int i=0;i<n;i++) sa[i]=i, pos[i]=s[i];
        for(gap=1;;gap*=2){
            sort(sa.begin(), sa.end(), cmp);
            tmp[0]=0;
            for(int i=1;i<n;i++) tmp[i]=tmp[i-1]+cmp(sa[i-1], sa[i]);
            for(int i=0;i<n;i++) pos[sa[i]]=tmp[i];
            if(tmp[n-1]==n-1) break;
        }

        // create the LCP array in additional O(n)
        for(int i=0,k=0;i<n;i++) if(pos[i]!=n-1){
            for(int j=sa[pos[i]+1]; s[i+k]==s[j+k]; k++);
            lcp[pos[i]]=k;
            if(k) k--;
        }

        // find the maximum length lcp
        int ind=0, mm=lcp[0];
        for(int i=1;i<n;i++) if(lcp[i]>mm) mm=lcp[i], ind=i;
        if(mm){
            // binary search the first value that matches the substring
            string word=s.substr(sa[ind], lcp[ind]);
            int a=0, b=sa.size()-1, mid;
            while(a<=b){
                mid=(a+b)/2;
                int v=word.compare(s.substr(sa[mid]));
                if(v==0) break;
                if(v>0) a=mid+(a==mid?1:0);
                else b=mid-(b==mid?1:0);
            }

            // binary search the last/last+1 value that matches the substring
            word.back()=word.back()+1;
            a=0, b=sa.size()-1;
            int old_mid=mid;
            while(a<=b){
                mid=(a+b)/2;
                int v=word.compare(s.substr(sa[mid]));
                if(v==0) break;
                if(v>0) a=mid+(a==mid?1:0);
                else b=mid-(b==mid?1:0);
            }
            if(word.compare(s.substr(sa[mid]))>=0) mid++;
            word.back()=word.back()-1;
            cout<<word<<' '<<(mid-old_mid)<<endl;
        }
        else cout<<"No repetitions found!"<<endl;
    }
}