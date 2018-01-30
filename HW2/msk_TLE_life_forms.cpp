#include <bits/stdc++.h>
using namespace std;

int n, gap;
vector<int> pos;

const char TERMINATOR = (char)CHAR_MAX;

bool cmp(int i, int j){
    if(pos[i]==pos[j]){
        i+=gap; j+=gap;
        if(i>=n || j>=n) return i>j;
    }
    return pos[i]<pos[j];
}

int main(){
    bool first=true;
    while(true){
        int num;cin>>num;
        if(num==0) break;

        if(first) first=false;
        else cout<<endl;

        if(num==1){
            string s; cin>>s;
            cout<<s<<endl;
            continue;
        }

        vector<string> words(num);
        for(auto& x: words) cin>>x;
        vector<int> lengths(num);
        for(int i=0,a=-1;i<words.size();i++) lengths[i] = a = 1+a+words[i].size();

        ostringstream oss;
        // adding a special character helps an edge case
        for(auto& x: words) oss<<x<<TERMINATOR;
        string s=oss.str();
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

        // create the LCP sorted array in additional O(n*logn)
        for(int i=0,k=0;i<n;i++) if(pos[i]!=n-1){
            for(int j=sa[pos[i]+1]; s[i+k]!=TERMINATOR && s[i+k]==s[j+k]; k++);
            lcp[pos[i]]=k;
            if(k) k--;
        }
        map<int, vector<int>, greater<int>> m;
        for(int i=0;i<n-1;i++){
            if(lcp[i]==0) continue;
            auto start=upper_bound(lengths.begin(), lengths.end(), sa[i]);
            auto end=upper_bound(lengths.begin(), lengths.end(), sa[i]+lcp[i]-1);
            auto start2=upper_bound(lengths.begin(), lengths.end(), sa[i+1]);
            auto end2=upper_bound(lengths.begin(), lengths.end(), sa[i+1]+lcp[i]-1);

            // shortening the prefixes that end in a different original word
            if(start==end && start2==end2) m[lcp[i]].push_back(i);
            else m[min(*start-sa[i],*start2-sa[i+1])].push_back(i);
        }

        // find the largest common one in O(n*logn)
        unordered_set<string> outer_done;
        bool found=false;
        for(auto& pp: m){
            for(int ind: pp.second){
                // binary search the first value that matches the substring
                string word=s.substr(sa[ind], pp.first);
                if(!outer_done.insert(word).second) continue;
                int a=0, b=n-1, mid;
                while(a<=b){
                    mid=(a+b)/2;
                    int v=word.compare(s.substr(sa[mid]));
                    if(v==0) break;
                    if(v>0) a=mid+(a==mid?1:0);
                    else b=mid-(b==mid?1:0);
                }

                // binary search the last/last+1 value that matches the substring
                word.back()=word.back()+1;
                a=0, b=n-1;
                int old_mid=mid;
                while(a<=b){
                    mid=(a+b)/2;
                    int v=word.compare(s.substr(sa[mid]));
                    if(v==0) break;
                    if(v>0) a=mid+(a==mid?1:0);
                    else b=mid-(b==mid?1:0);
                }
                word.back()=word.back()-1;
                if(word.size()<=n-sa[mid] && word==s.substr(sa[mid], word.size())) mid++;

                // check the substring range belongs to more than half of the original strings
                unordered_set<int> done;
                for(int i=old_mid;i<mid;i++){
                    auto start=upper_bound(lengths.begin(), lengths.end(), sa[i]);
                    auto end=upper_bound(lengths.begin(), lengths.end(), sa[i]+pp.first-1);
                    
                    if(start==end) done.insert(*start);
                }
                if(done.size()>num/2){
                    found=true;
                    cout<<word<<endl;
                }
            }
            if(found){
                break;
            }
        }
        if(outer_done.empty()){
            cout<<'?'<<endl;
        }
    }
}