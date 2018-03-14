//CMPT 409 Assignment 4
//Problem: Constrained Circular Permutations
//Team Members: Heather Li, Ekjot Singh Billing, Manshant Singh Kohli

#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <numeric>
#include<bitset>
using namespace std;


int factorial(int n){
    int ret=1;
    for (int i=2;i<=n;i++){
        ret=ret*i;
    }
    return ret;
}

//a clock permutation is suggested with fixed values at v[0:ind] and v[N-1]
//try to insert values at v[ind]
int insertfaces(vector<int> v,string used,int ind, int N,int S){
    int total=0;
    int endmax=S-N-v[N-1];
    int maxsum=max(max(v[(ind+1+N)%N]+v[(ind+2+N)%N],v[(ind-1+N)%N]+v[(ind-2+N)%N]),v[(ind+1+N)%N]+v[(ind-1+N)%N]);
    int maxavail=used.rfind('0');
    int minavail=used.find('0',1);

    //all possible values have been inserted. Check and return whether permutation is valid
    if (ind==N-2){
        v[ind]=maxavail;
        if (v[ind]+v[ind-1]+v[ind-2]<=S && v[ind]+v[N-1]+v[0]<=S){
            return 1;
        }
        return 0;
    }

    //if all possible sums for the wraparound triple are too big, no valid permutatations with a configuration up to this point
    if (minavail>endmax) {
        return 0;
    }

    //if all of the remaining permutations configurations are valid, return the number of these configurations
    if ( (maxavail <=endmax ) && (3*maxavail-3)<=S && (v[(ind-1+N)%N]+2*maxavail-1)<=S && (v[N-1]+2*maxavail-1)<=S && (maxsum+maxavail)<=S){
        return factorial(N-1-ind);
    }

    //try to insert a new value into the next index of our clock vector
    for (int i=minavail;i<=S-maxsum &&i<=N-1;i++){
        if (used[i]=='0'){
            v[ind]=i;
            used[i]='1';
            total+=insertfaces(v,used,ind+1,N,S);
            used[i]='0';
        }
    }
    return total;
}


int main(){

    int N,S,cases;

    cin >> cases;
    int zeroval[14]={0,1,3,6,8,9,10,13,14,15,17,19,20,22}; //easy processing
    for (int ccase=0;ccase<cases;ccase++){
        if (ccase!=0)
            cout << endl;
        cin >> N >> S;
        vector<int> faces(N,1);

        int total=0;

        if (S>=zeroval[N]){
            //fix faces[0] to N and faces[N-1] to k. Try to insert values from faces[2],..., faces[N-2]
            for (int k=N-1;k>=1;k--){
                vector<int> faces(N,1);
                faces[0]=N;
                faces[N-1]=k;
                string used(N+1,'0');
                used[N]='1';
                used[k]='1';
                total+=insertfaces(faces,used,1,N,S);
            }
        }

        cout << "Permutation size:    "  << N <<endl;
        cout << "Maximum triplet sum: "  << S <<endl;
        cout << "Valid permutations:  " << total/2 <<endl;

    }

    return 0;
}
