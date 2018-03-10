#include <bits/stdc++.h>
using namespace std;

typedef bitset<100> bitmask_t;

int maxVal(const vector<bitmask_t>& row, int pos){
	if(pos>=0) for(int i=row.size()-1; i>0;i--){
		if(row[i].test(pos)){
			return i;
		}
	}
	return 0;
}

int main(){
    int t; cin>>t;
    while(t--){
    	int n;cin>>n;

    	vector<int> v(n);
    	for(auto& x: v) cin>>x;

    	int sum=0;
    	for(int x: v) sum+=x;
    	int lim = sum/2;

    	vector<vector<bitmask_t>> dp(n+1, vector<bitmask_t>(lim+1));

    	for(int i=1;i<=n;i++){
    		int val = v[i-1];
    		for(int j=1;j<=lim;j++){
    			if(val <= j){
    				dp[i][j] = dp[i-1][j] | (dp[i-1][j-val] << 1 );
    			}
    			else dp[i][j] = dp[i-1][j];
    		}
    		if(val<=lim){
    			dp[i][val].set(0);
    		}
    	}

    	int val;
    	if(n%2==0) val = maxVal(dp[n], n/2 - 1);
    	else val = max(maxVal(dp[n], (n-1)/2 - 1), maxVal(dp[n], (n+1)/2 - 1));
    	cout<<val<<' '<<sum-val<<endl;

    	if(t>0) cout<<endl;
    }
}