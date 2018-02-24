//CMPT 409 Assignment 3
//Problem: Chopsticks
//Team Members: Heather Li, Ekjot Singh Billing, Manshant Singh Kohli

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


//dp[k][n] stores the minimum badness that must be created with k sets and the last n chopsticks
int dpfunc(int k, int n,int badness[],vector <vector<int> > &dp) {
	if (dp[k][n]==-1){
		if (n < 3*k) //no space left
			dp[k][n] = 1024000001;

		else if (k == 0) //none needed
			dp[k][n] = 0;

		else
			dp[k][n] = fmin(dpfunc(k, n-1,badness,dp), dpfunc(k-1, n-2,badness,dp)+badness[badness[0]-(n-2)]);
	}

	return dp[k][n];
}

int main(){
	int T,K,N;
	cin >> T;

	for (int cases=0;cases<T;cases++){
		cin >> K >> N;
		K+=8;
		vector<vector<int> > dp(K+1,vector<int>(N+1,-1));

		int A[N+1]; //lengths
		int badness[N+1]; //badness of consecutive leements
		A[0]=0;
		badness[0]=N; //store N length for array

		for (int i=1;i<=N;i++){
			cin >> A[i];
			badness[i]=(A[i]-A[i-1])*(A[i]-A[i-1]);
		}

		cout << dpfunc(K,N,badness,dp) <<endl;

	}
	return 0;

}
