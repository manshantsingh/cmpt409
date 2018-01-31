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
        vector<string> outer_done;
        bool found=false;
        for(auto& pp: m){

            for(int ind: pp.second){
              int a=0, b=n-1, mid;
              string word=s.substr(sa[ind], pp.first);


                mid=ind;
                for (int i=ind;i>=0 ;i--){
                  if (lcp[i]<pp.first){
                    mid=i+1;
                    break;
                  }
                  if (i==0) mid=0;
                }

                int hi=ind;
          			for (int i=ind;i<n ;i++){
          				if (lcp[i]<pp.first){
          					hi=i;
                    break;
          				}

          			}


                // check the substring range belongs to more than half of the original strings
                unordered_set<int> done;
                for(int i=mid;i<=hi;i++){
                    done.insert(distance(lengths.begin(),upper_bound(lengths.begin(), lengths.end(), sa[i])));
                }
                if(done.size()>num/2){
                  if (outer_done.empty() || outer_done.back()!=word)
                   outer_done.push_back(word);
                    found=true;
                }
            }
            if(found){
                break;
            }
        }
        for (auto &i: outer_done)
          cout << i << endl;
        if(outer_done.empty()){
            cout<<'?'<<endl;
        }
    }
}
