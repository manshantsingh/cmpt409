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
	int n;
	string inp,str;
	cin >> n;
	double half;
	bool first=true;
	while (n!=0){
		if (!first)	cout << endl;
		first=false;
		
		int maxlen=0;
		vector <string> answers;

		half=n/2+1;
		str="";
		int lens[n+1];
		for (int i=0;i<n;i++){
			cin >>inp;
			str.append(inp);
			str.append("$");
		}
		if (n==1) {
			answers.push_back(inp);
		}
		if (n!=1) {
			suffix_array sarr(str);
			vector<int> v=sarr.idx;
		//	cout << str.length() <<endl;
			int wordno[str.size()];
//			vector<int> H(str.size());
			vector <int> scanlist;
			wordno[n-1]=count(str.begin()+v[n],str.end(),'$');
			for (int i=n;i<str.size();i++){
//				H[i]=sarr.lcp(v[i-1],v[i]);
				wordno[i]=count(str.begin()+v[i],str.end(),'$');
				if (wordno[i]!=wordno[i-1])	{
					if (scanlist.size()==0 || scanlist.back()!=i-1)
						scanlist.push_back(i-1);	
					scanlist.push_back(i);
					
				}
					
			}
			
	//		for (int i=0;i<scanlist.size();i++) cout << " "<< scanlist[i]; cout << endl; 	for (int i=n;i<H.size();i++) cout <<i<< " "<< wordno[i]  <<str.substr(v[i]) << " " <<endl; cout << endl;cout << str << endl;

			
			int temp, right, scans;
			int rightmostj=0;
			for (int i=0;i<scanlist.size();i++){
				bool used[n+1]={0};
				
				right=0;
				scans=0;
				//cout << i << rightmostj <<endl;
				for (int j=i;j<scanlist.size() && scans<half;j++ ){
					if (used[wordno[scanlist[j]]]==0){
						used[wordno[scanlist[j]]]=1;
						scans++;
						right=scanlist[j];
						rightmostj=j;
					}
				} 
				
				if (scans<half) right=0;
				
				temp=sarr.lcp(v[scanlist[i]],v[right]);
				string pattern=str.substr(v[scanlist[i]],temp);
				if (pattern.find('$')!=string::npos){
					temp=pattern.find('$');
					pattern=pattern.substr(0,temp);
				}
				if (temp>maxlen) {
					maxlen=temp;
					answers.clear();
				}
				if (temp==maxlen && maxlen>0){
					if (answers.size()==0 ||answers.back()!=pattern)
						answers.push_back(pattern);
	//				cout << scanlist[i] << right << " " << temp << str.substr(v[i],temp) <<endl;
				}
			}
		}
		for (int i=0;i<answers.size();i++){
			cout << answers[i]<< endl;
		}
		if (answers.size()==0)	cout<< "?" <<endl;
		
		
		
		cin >> n;
	}
}



