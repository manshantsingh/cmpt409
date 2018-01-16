#include <iostream>
#include <list>
#include <vector>

using namespace std;

void DFS(int a,int target,list<int> * adjlist, bool visited[],int * path,bool * flag ,int l){
	if (*flag)	
		return;

	visited[a]=true;
	path[l++]=a;
		
	for (list<int>::iterator it=adjlist[a].begin();it!=adjlist[a].end() ; ++it){
		if (*it==target){
			*flag=true;
			path[l++]=*it;
			if (l%2==1){
				cout << "The fleas meet at " << path[l/2] << "." << endl;
			}
			else {
				cout << "The fleas jump forever between ";
				if (path[l/2] < path[l/2-1])
					cout << path[l/2] << " and " << path[l/2-1];
				else
					cout << path[l/2-1] << " and " << path[l/2];
				cout << "." <<endl;
			}
			return;
		}
		else if (!visited[*it])
			DFS(*it,target,adjlist,visited,path,flag,l);
	}
}

int main(){
	int n,l;
	cin >> n;
	int a,b;
	while (n!=0){
		list<int> adjlist[n+1];
		for (int i=1;i<n+1;i++){
			adjlist[i].clear();
		}
		for (int i=1;i<n;i++){
			cin >> a >>b;
			adjlist[a].push_back(b);
			adjlist[b].push_back(a);
		}
		cin >> l;
		bool visited[n+1];
		int path[n+1];
		for (int query=0;query<l;query++){
			cin >> a >>b;
			if (a==b)
				cout << "The fleas meet at " << a << "." << endl;
			else {
				for (int i=1;i<n+1;i++){
					visited[i]=false;
				}
				bool flag=false;
				DFS(a,b,adjlist,visited,path,&flag,0);
			}
		}
		cin >>n;
	}
	return 0;
}