#include <bits/stdc++.h>
using namespace std;

int main(){
    while(true){
        int n; cin>>n;
        if(n==0) break;

        // v[i] returns a vector to all adjacent nodes of i-th node
        vector<vector<int>> v(n, vector<int>());
        while(--n){
            int a, b; cin>>a>>b;
            a--;b--;
            v[a].push_back(b);
            v[b].push_back(a);
        }
        int l; cin>>l;
        while(l--){
            int a, b; cin>>a>>b;
            if(a==b){
                cout<<"The fleas meet at "<<a<<"."<<endl;
                continue;
            }

            // perform a Breadth First Search for each query to get the path from A to B
            a--;b--;
            queue<pair<int,int>> q;
            q.push({a,0});
            int d;
            vector<int> p(v.size(),-1);
            while(true){
                int c; tie(c,d) = q.front();
                d++;
                q.pop();
                bool flag=false;
                for(int x: v[c]){
                    if(p[x]!=-1) continue;
                    p[x]=c;
                    if(x==b){
                        flag=true;
                        break;
                    }
                    q.push({x,d});
                }
                if(flag) break;
            }

            // Find the midpoint(s) of the path and print the result.
            bool odd=d%2;
            d/=2;
            int x=b;
            while(d--) x=p[x];
            if(odd){
                set<int> s{x+1, p[x]+1};
                cout<<"The fleas jump forever between "<<*s.begin()<<" and "<<*s.rbegin()<<"."<<endl;
            }
            else cout<<"The fleas meet at "<<x+1<<"."<<endl;
        }
    }
}