#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>

using namespace std;

//splits a string into a set of strings based on some delimiter
vector <string> split(string inp,string delim){
	vector <string> out;
	int start;
	while ((start = inp.find(delim)) != string::npos) {
	    out.push_back( inp.substr(0, start));
	    inp.erase(0, start+delim.length()+1);
	}
	out.push_back(inp);
	return out;
}


int main() {
	int scenarios,P,N;
	string temp;
	map <string,int> ndict;
	int A;
	cin >> scenarios;

	for (int scenario=1;scenario<=scenarios;scenario++){
		cin>>P>>N; 	getline(cin,temp);
		ndict.clear();

		ndict["Erdos, P"]=0;
		vector< vector<string> > papers;

		for (int i=0;i<P;i++){
	  	getline(cin,temp);
			vector <string> authors=split( temp.substr(0,temp.find(".:")),".,");
			papers.push_back(authors);
			for (int j=0;j<authors.size();j++){
				ndict.insert(pair<string,int> (authors[j],ndict.size()));
			}
		}

		A=ndict.size();
		bool adj[A][A];
		for (int i=0;i<A;i++){
			for (int j=0;j<A;j++){adj[i][j]=false;}
		}
		for (int i=0;i<P;i++){
			for (int j=0;j<papers[i].size();j++){
				for (int k=0;k<j;k++){
					adj[ndict[papers[i][j]]][ndict[papers[i][k]]]=true;
					adj[ndict[papers[i][k]]][ndict[papers[i][j]]]=true;
				}
			}
		}
		
	queue<int> Q;
		Q.push(0);
		int dist[A];
		for (int i=0;i<A;i++){
			dist[i]=A+3;
		}
		dist[0]=0;
		bool visited[A]={false};
		visited[0]=true;


		while (!Q.empty()){
			int curr=Q.front();
			//cout <<curr << " ";
			visited[curr]=true;
			Q.pop();
			for (int j=0;j<A;j++){
				if (adj[curr][j] && (!visited[j])){
					visited[j]=true;
					Q.push(j);
					dist[j]=dist[curr]+1;
				}
			}
		}

		cout << "Scenario " << scenario <<endl;
		for (int i=0;i<N;i++){
			getline(cin,temp);
			string name=temp.substr(0,temp.size()-1);
			cout << temp  << " ";
			if (dist[ndict[name]]>=A+1 || dist[ndict[name]]<=0){
				cout <<"infinity";
			}
			else cout << dist[ndict[name]];
			cout << endl;
		}
	}
	return 0;
}
