#include <bits/stdc++.h>
using namespace std;

const int LIMIT = 21;

int n, total;
int parent[LIMIT];
vector<int> m[LIMIT];
int reachable;

void func(int a){
    for(int x: m[a]){
        if(x==n){
            total++;
            stack<int> s;
            int y = a;
            while(y!=1){
                s.push(y);
                y=parent[y];
            }
            cout<<1;
            while(s.size()){
                cout<<' '<<s.top();
                s.pop();
            }
            cout<<' '<<n<<endl;
        }
        // prune if a path doesn't exist or if the node is already visited
        else if((reachable & (1<<x))!=0 && parent[x]==-1){
            parent[x]=a;
            func(x);
            parent[x]=-1;
        }
    }
}

// runs BFS from the endpoint to see if there see if a path exists from point x to n
void computeReachable(int n){
    vector<int> mm[LIMIT];
    for(auto& x: mm) x.clear();
    for(int i=1;i<LIMIT;i++){
        for(int x: m[i]) mm[x].push_back(i);
    }
    reachable=(1<<n);
    queue<int> q;
    q.push(n);
    while(q.size()){
        int a = q.front();
        q.pop();
        for(int x: mm[a]){
            if((reachable & (1<<x))==0){
                reachable |= 1<<x;
                q.push(x);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    int caseNum=0;
    while(cin>>n){
        for(auto& x: m) x.clear();
        while(true){
            int a,b;
            cin>>a>>b;
            if(a==0 && b==0) break;
            m[a].push_back(b);
            m[b].push_back(a);
        }
        total=0;
        cout<<"CASE "<<++caseNum<<":"<<endl;
        if(n==1){
            cout<<1<<endl;
            total++;
        }
        else {
            for(auto& x: m) sort(x.begin(), x.end());
            for(int i=2;i<LIMIT;i++) parent[i]=-1;
            parent[1]=1;
            computeReachable(n);
            func(1);
        }
        cout<<"There are "<<total<<" routes from the firestation to streetcorner "<<n<<"."<<endl;
    }
}