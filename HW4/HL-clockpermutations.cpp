#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <bitset>
using namespace std;


bitset<16> bitmask(int a,int b,int c){
  bitset<16> badtriple;
  badtriple.set(a);
  badtriple.set(b);
  badtriple.set(c);
  return badtriple;
}
/*
int bitmask(int a,int b,int c){
  int badtriple=(1<<a)||(1<<b)||(1<<c);
  return badtriple;
}*/

bool descsort (int i,int j) {
  return (i>j);
}

bool ascsort (int i,int j) {
  return (i<j);
}



int main(){

  int N,S,cases;

  cin >> cases;

  for (int ccase=0;ccase<cases;ccase++){
    if (ccase!=0)
      cout << endl;
    cin >> N >> S;
    vector<int> faces(N);
    for (int i=1;i<N;i++){
      faces[i]=i;
    }
    faces[0]=N;

    /*
    //triples
    unordered_set < bitset<16> > bads;

    for (int a=N;a>2;a--){
      for (int b=a-1;b>1;b--){
        for (int c=b-1;c>0;c--){
          if (a+b+c>S){
            bads.insert(bitmask(a,b,c));
          }
          else break;
        }
      }
    }
*/
    int total=0;
    while( next_permutation(faces.begin()+1,faces.end()) ){
      bool notvalid=false;
      for (int i=0;i<N;i++){
//        if (bads.count(bitmask(faces[i],faces[(i+1)%N],faces[(i+2)%N])) >0) {
          if (faces[i]+faces[(i+1)%N]+faces[(i+2)%N]>S){
          vector<int> copyfaces(faces);
      //    for (auto i:copyfaces)    cout << i << " "; cout << endl;
          notvalid=true;
          int biggestindex=max(i,max((i+1)%N,(i+2)%N));
          if (biggestindex+1<N){
            int badnum=copyfaces[biggestindex];
            auto maxnum=max_element(copyfaces.begin()+biggestindex+1,copyfaces.end());
            int nextvalid=*maxnum;
            for (int j=biggestindex+1;j<N;j++){
                if (copyfaces[j]>badnum){
                  nextvalid=min(nextvalid,copyfaces[j]);
                }

            }
          //  cout <<biggestindex<<badnum <<  nextvalid <<endl;;
            auto nextbiggest=find(copyfaces.begin()+ biggestindex,copyfaces.end(),nextvalid );
            iter_swap(nextbiggest,copyfaces.begin()+biggestindex);
            sort (copyfaces.begin()+biggestindex+1,copyfaces.end(),descsort);
        //    for (auto i:copyfaces)    cout << i << " "; cout << endl;
            prev_permutation(copyfaces.begin()+1,copyfaces.end());
            if (lexicographical_compare(faces.begin(),faces.end(),copyfaces.begin(),copyfaces.end(),ascsort))
              faces=copyfaces;

          //  cout << endl;
          }

          break;
        }
      }
      if (!notvalid){
        //for (auto i:faces)    cout << i << " "; cout << endl;
        total++;
      }

    }

    cout << "Permutation size:    "  << N <<endl;
    cout << "Maximum triplet sum: "  << S <<endl;
    cout << "Valid permutations:  " << total/2 <<endl;





  }



}
