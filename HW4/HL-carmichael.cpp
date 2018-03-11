#include <iostream>
#include <vector>
#include <bitset>
using namespace std;


int main(){

  //pre-process: sieve of Eratosthenes for primes in n range
  int maxn=65000;
  vector<bool> sieve(maxn+1,true);
  for (int i=2; i*i<maxn; i++){
      if (sieve[i]) {
          for (int j=2*i; j<=maxn; j += i)
              sieve[j] = false;
      }
  }

  int n;
  while(cin>>n){
    if (n==0) break;
    //check if n is prime -- will be normal
    if (sieve[n])
      cout << n << " is normal." <<endl;

    //otherwise, check whether composite n is Carmichael
    else {
      //find length for square-multiply algorithm
      int len=16;
      for (int k=16;k>=0;k--){
        if ((1<<k)<=n){
          len=k+1;
          break;
        }
      }


      bool carm=true;
      //square-multiply test
      for (int a=2;a<n && carm;a++){
        long z=1;
        for (int i=0;i<len;i++){
          z=(z*z)%n;
          if (((n>>(len-i-1))&1)==1)
            z=(z*a)%n;
        }

        if (z!=a){
          carm=false;
          cout << n << " is normal."<<endl;
        }

      }
      if (carm)
        cout << "The number " << n << " is a Carmichael number." <<endl;

    }
  }

  /*561
1105
1729
2465
2821
6601
8911
10585
15841
29341
41041
46657
52633
62745
63973
0
*/







}
