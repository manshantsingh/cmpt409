#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <set>
#include <list>
#include <bitset>

using namespace std;


multiset<int>  adj[60];

//DFS to determine whether our graph is connected
void DFS(int curr, bitset<51> &visited){
    for (auto it:adj[curr]) {
        int index=it;
        if (visited.test(index)){
            visited.reset(index);
            DFS(index,visited);
        }
    }
}

//create a cycle , returns cycle[1:-1]
list<int> makecycle(int curr){
    int first=curr;
    list<int> cycle;
    int temp;
    do{
        temp=curr;
        curr = *adj[curr].begin();
        adj[curr].erase(adj[curr].find(temp)); 
        adj[temp].erase(adj[temp].find(curr)); 
        cycle.push_back(curr);
    }  while (first!=curr);
    return cycle;
}


int main() {
    int T,N,a,b;
    bool invalid;
    cin >> T;

    for (int cases=1;cases<=T;cases++){
        invalid=false;

        for (int i=0;i<60;i++){
            adj[i].clear();
        }
        list<int> L; 

        if (cases!=1)
            cout <<endl;
        cin >> N;
        cout << "Case #" <<cases<<endl;


        int mincolour=51;

        bitset<51> degcheck;
        bitset<51> visited;
        for (int line=0;line<N;line++){
            cin >> a >> b;
            mincolour=max(b,min(mincolour,a));
            adj[a].insert(b);
            adj[b].insert(a);
            degcheck.flip(a);
            degcheck.flip(b);
            visited.set(a);
            visited.set(b);
        }

        //eulerian paths exists iff every vertex has even degree and the graph is connected
        if (degcheck.any()){ //is every vertex of even degree
            invalid=true;
        }
        else { //is graph connected?
            DFS(mincolour, visited);
            if (visited.any())
                invalid=true;
        }

        if (!invalid){
             list<int> test;
            test.push_back(mincolour); //insert a value 
            test.push_back(-1); //dummy

            //keep inserting cycles
            while (test.size()<=N+1){
                auto it=test.begin();
                for (auto i=test.begin();i!=test.end();i++){
                    if(adj[*i].size()>0){
                        it=i;
                        break;
                    }
                }
                list<int> temp=makecycle(*it); //grab a cycle from remaining edges. guaranteed to exist
                test.insert(++it,temp.begin(),temp.end());
                --it;

            }


            //print our eulerian path, given in list of visited nodes
            cout << *test.begin() << " ";
            for (list<int>::iterator it=++test.begin(); it != --(--test.end()); ++it){
                cout << *it << endl << *it <<' ';
            }
            cout << mincolour <<endl;

                 
        }
        if (invalid)
            cout << "some beads may be lost" <<endl;

    }

    return 0;
}

