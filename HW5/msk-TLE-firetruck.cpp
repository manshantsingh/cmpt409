#include <bits/stdc++.h>
using namespace std;

int n, total;
unordered_map<int, vector<int>> m;
unordered_map<int,int> parent;

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
        else if(parent.find(x)==parent.end()){
            parent[x]=a;
            func(x);
            parent.erase(x);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    int caseNum=0;
    while(cin>>n){
        m.clear();
        parent.clear();
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
            for(auto& x: m) sort(x.second.begin(), x.second.end());
            parent[1]=1;
            func(1);
        }
        cout<<"There are "<<total<<" routes from the firestation to streetcorner "<<n<<"."<<endl;
    }
}