#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;



bool descsort (int i,int j) {
  return (i>j);
}

bool ascsort (int i,int j) {
  return (i<j);
}

//rearrange so you skip all the permutations where the 0-'index' indices of the vector occur
void skipperms(vector <int> &v,int index,int biggest){
    if (index==0 || index==v.size()-1)   {
        return;
    }
    auto swapit=find(v.begin()+index,v.end(),biggest);
    int replacer=*swapit;
    for (auto it=v.begin()+index+1;it!=v.end();it++){
        if (*it>v[index]){
            replacer=min(replacer,*it);
            if (replacer==*it)  swapit=it;
        }
    }
    if (replacer==v[index]){
        sort(v.begin()+index,v.end(),descsort);
    }
    else{
        iter_swap(v.begin()+index,swapit);
        sort(v.begin()+index+1,v.end(),ascsort);
    }
}



int main(){

  int N,S,cases;

  cin >> cases;
  int zeroval[14]={0,1,3,6,8,9,10,13,14,15,17,19,20,22};
  for (int ccase=0;ccase<cases;ccase++){
    if (ccase!=0)
      cout << endl;
    cin >> N >> S;
    vector<int> faces(N);
    iota(faces.begin()+1,faces.end(),1);
    faces[0]=N;

  int total=0;
    if (S>zeroval[N]){
        while( next_permutation(faces.begin()+1,faces.end()) ){
            bool notvalid=false;
            bool changed=false;
            vector<int> maxarray(N,1);
            maxarray[N-1]=faces[N-1];
            for (int i=N-2;i>=0;i--){
                maxarray[i]=max(maxarray[i+1],faces[i]);
            }

            for (int i=0;i<N && !notvalid &&!changed;i++){
            /*    if (i>2){
                    int X=maxarray[i];//*max_element(faces.begin()+i,faces.end() );
                    if  ( (3*X-3<=S) && (faces[i-1]+faces[i-2]+X) <=S && (N+2*X-1 <=S) && (N+faces[1]+X)<=S){
                        changed=true;
                        break;
                    }
                } */
                if (faces[i]+faces[(i+1)%N]+faces[(i+2)%N]>S){
                    notvalid=true;
                    int biggestindex=min(max(i,max((i+1)%N,(i+2)%N)),N-1);
                    skipperms(faces,biggestindex,maxarray[biggestindex]);
                    break;
                }
            }
            if (!notvalid){
                total++;
            }
        }
    }

    cout << "Permutation size:    "  << N <<endl;
    cout << "Maximum triplet sum: "  << S <<endl;
    cout << "Valid permutations:  " << total/2 <<endl;





  }



}
