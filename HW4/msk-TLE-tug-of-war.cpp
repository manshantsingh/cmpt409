#include <bits/stdc++.h>
using namespace std;

typedef bitset<100> bitmask_t;

vector<int> v;
unordered_map<bitmask_t, int> m;
bitmask_t done;

int func(int n, int val){
	if(n==0) return val;
	auto it=m.find(done);
	if(it!=m.end()){
		return it->second;
	}

	int limit = distance(v.begin(), upper_bound(v.begin(), v.end(), val));
	int mm=-1;

	for(int i=0;i<limit;i++){
		if(done.test(i)) continue;

		done.set(i);
		int x = func(n-1, val - v[i]);
		done.reset(i);

		if(x==-1) continue;
		if(mm==-1 || mm>x) mm=x;
	}
	m[done]=mm;
	return mm;
}

int solve(int val, int n){
	m.clear();
	done.reset();

	int diff = func(n, val);
	if(diff==-1) return -1;
	return val-diff;
}

int main(){
    int t; cin>>t;
    while(t--){
    	int n;cin>>n;
    	v.resize(n);
    	for(auto& x: v) cin>>x;
    	sort(v.begin(), v.end());

    	int sum=0;
    	for(int x: v) sum+=x;
    	int lim = sum/2;

    	int ans;
    	if(n%2==0) ans = solve(lim, n/2);
    	else ans = max(solve(lim, (n+1)/2), solve(lim, (n-1)/2));

    	int other = sum-ans;
    	if(ans<other) cout<<ans<<' '<<other<<endl;
    	else cout<<other<<' '<<ans<<endl;

    	if(t>0) cout<<endl;
    }
}