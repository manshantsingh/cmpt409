#include <bits/stdc++.h>
using namespace std; 


struct entry { pair <int,int> nr; int p; };
bool operator <(const entry &a,const entry &b){
	return a.nr < b.nr;
}

struct suffix_array {
	string s;
	int n;
	vector<entry> L;
	vector<int> idx;
	vector <vector <int > > P;
	suffix_array(string _s) : s(_s), n(s.size()) {
		L= vector<entry>(n), P.push_back(vector<int>(n)),idx=vector<int>(n);
		for (int i=0;i<n;i++){
			P[0][i]=s[i];
		}
		for (int stp=1,cnt=1;cnt>>1 <n;stp++,cnt<<=1){
			P.push_back(vector<int>(n));
			for (int i=0;i<n;i++){
				L[L[i].p =i].nr =pair<int,int>(P[stp-1][i],i+cnt<n?P[stp-1][i+cnt]:-1);
			}
			sort(L.begin(),L.end());
			for (int i=0;i<n;i++){
				P[stp][L[i].p]=i>0 && L[i].nr == L[i-1].nr ? P[stp][L[i-1].p] :i;
			}
		}
		for (int i=0;i<n;i++){
			idx[P[P.size() - 1][i]] = i;
		}
	}
	int lcp(int x,int y){
		int res=0;
		if (x==y) return n-x;
		for (int k=P.size() -1;k>=0 && x<n && y<n; k--){
			if (P[k][x]==P[k][y])
				x+=1 <<k,y+=1<<k,res+=1<<k;
		}
		return res;
	}
	
};



int main() {
	int T,L;
	string str;
	cin >> T;
	for (int tcase=0;tcase<T;tcase++){
		cin >> L >> str;
		suffix_array sarr(str.append(str.substr(0,L-1)));
		vector<int> v=(sarr.P).back();
		 int dist=distance(v.begin(),min_element(v.begin(),v.begin()+L));
		 string shortest=str.substr(dist,L);
		for (int i=0;i<L;i++){
			if (shortest==str.substr(i,L)){
				cout << i <<endl;
				break;
			}
				
		}
	}
}



