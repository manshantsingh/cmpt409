#include <bits/stdc++.h>
using namespace std;

int main(){
    const string ERDOS="Erdos, P.";
    int t; cin>>t;
    for(int z=1;z<=t;z++){
        int p,n; cin>>p>>n>>ws;

        // Hash Tree:
        // Key = Name of the author
        // Value = Hash Set of authors published papers with
        unordered_map<string, pair<unordered_set<string>,int>> m;

        // Read in all the publishers and parse the node edges
        while(p--){
            string a,b; getline(cin, a, ':');
            istringstream iss(" "+a);
            vector<string> v;
            while(getline(iss, a, ',') && getline(iss, b, ',')){
                v.push_back(a.substr(1)+','+b);
            }
            getline(cin, a);
            for(int i=0;i<v.size();i++){
                auto& x=m[v[i]].first;
                for(int j=0;j<v.size();j++){
                    if(i==j) continue;
                    x.insert(v[j]);
                }
            }
        }

        // Breadth First Search to find the Erdos number for each author
        m[ERDOS].second=-1;
        queue<pair<string,int>> q;
        q.push({ERDOS, 0});
        while(q.size()){
            string name; int next;
            tie(name, next) = q.front();
            q.pop();
            next++;
            for(auto& x: m[name].first){
                if(m[x].second==0){
                    m[x].second=next;
                    q.push({x, next});
                }
            }
        }
        cout<<"Scenario "<<z<<endl;
        while(n--){
            string s; getline(cin, s);
            cout<<s<<' ';
            int val=m[s].second;
            if(val==0) cout<<"infinity";
            else cout<<val;
            cout<<endl;
        }
    }
}