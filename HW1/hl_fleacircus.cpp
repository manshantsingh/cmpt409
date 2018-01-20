//CMPT 409 Assignment 1
//Problem: Flea Circus
//Team Members: Heather Li, Ekjot Singh Billing, Manshant Singh Kohli

#include <iostream>
#include <list>
#include <vector>

using namespace std;

//DFS search which starts from node 'a' in a tree and terminates once it reaches the target notes
//prints middle nodes in this path to stdout
void DFS(int a,int target,list<int> * adjlist, bool visited[],int * path,bool * flag ,int l){
	if (*flag)	//halt extraneous DFS calls
		return;

	//mark node and add it to the path
	visited[a]=true;
	path[l++]=a;

	//iterate through neighbours of current node
	for (list<int>::iterator it=adjlist[a].begin();it!=adjlist[a].end() ; ++it){
		//if neighbour is the target node
		if (*it==target){
			*flag=true;
			path[l++]=*it;

			//determine middle node(s) in path and print out relevant output
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
		//if the neighbour is not the target node, but is unvisited, continue the algorithm
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
		bool visited[n+1]; //array to check if nodes are visited
		int path[n+1]; //'stack' which keeps track of the path from node a to b
		for (int query=0;query<l;query++){
			cin >> a >>b;
			if (a==b) //corner case not covered by our DFS
				cout << "The fleas meet at " << a << "." << endl;
			else {
				for (int i=1;i<n+1;i++){
					visited[i]=false;
				}
				bool flag=false; //flag for if the target node has been found

				//run DFS, which will print necessary output
				DFS(a,b,adjlist,visited,path,&flag,0);
			}
		}
		cin >>n;
	}
	return 0;
}
