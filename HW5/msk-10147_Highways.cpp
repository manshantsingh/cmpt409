#include <bits/stdc++.h>
using namespace std;

typedef tuple<int,int,int> tuple_t;

// using union-find data-structure for kruskal's algorithm
vector<int> parent;
int find(int a){ return a==parent[a] ? a : parent[a]=find(parent[a]); }
void merge(int a, int b){ parent[find(a)]=find(b); }
bool same(int a, int b){ return find(a)==find(b); }

struct cmp{
   bool operator()(const tuple_t& a, const tuple_t& b){
    return get<2>(a) > get<2>(b); 
   }
};

int main(){
    int t; cin>>t;
    while(t--){
        int n; cin>>n;
        vector<pair<int,int>> v(n);
        for(auto& x: v) cin>>x.first>>x.second;
        parent.resize(n);
        for(int i=0;i<n;i++) parent[i]=i;
        int m; cin>>m;
        int groups = n;
        while(m--){
            int a,b; cin>>a>>b;
            a--;b--;
            if(!same(a,b)){
                merge(a,b);
                groups--;
            }
        }
        if(groups<=1){
            cout<<"No new highways need"<<endl;
        }
        else{
            // creating a priority queue of all highway combinations
            priority_queue<tuple_t, vector<tuple_t>, cmp> pq;
            for(int i=0;i<n;i++){
                for(int j=i+1;j<n;j++){
                    int x = v[i].first - v[j].first;
                    int y = v[i].second - v[j].second;
                    pq.push({i,j, x*x + y*y});
                }
            }
            // join the least highway distance between sets that have not been joined yet
            while(groups>1){
                int a,b,c;
                tie(a,b,c) = pq.top();
                pq.pop();
                if(!same(a,b)){
                    merge(a,b);
                    groups--;
                    cout<<a+1<<' '<<b+1<<endl;
                }
            }
        }
        if(t>0) cout<<endl;
    }
}