#include <bits/stdc++.h>
using namespace std;

int hx[]={-1,0,1,0},
    hy[]={0,-1,0,1},
    dx[]={-1,-1,1,1},
    dy[]={-1,1,-1,1},
    kx[]={-2,-1,2,1,-2,-1,2,1},
    ky[]={1,2,-1,-2,-1,-2,1,2};

bool inrange(int i, int j){
    return i>=0 && i<8 && j>=0 && j<8;
}

int func(string arr[]){

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            char c=arr[i][j];
            char target = islower(c)?'K':'k';
            int ret = islower(c)?-1:1;
            c=tolower(c);
            if(c=='n'){
                for(int k=0;k<8;k++){
                    int x=i+kx[k],
                        y=j+ky[k];
                    if(inrange(x,y) && arr[x][y]==target) return ret;
                }
                continue;
            }
            if(c=='q'||c=='r'){
                for(int k=0;k<4;k++){
                    int x=i, y=j;
                    while(true){
                        x+=hx[k];
                        y+=hy[k];
                        if(!inrange(x,y)) break;
                        if(arr[x][y]==target) return ret;
                        if(arr[x][y]!='.') break;
                    }
                }
            }
            if(c=='q'||c=='b'){
                for(int k=0;k<4;k++){
                    int x=i, y=j;
                    while(true){
                        x+=dx[k];
                        y+=dy[k];
                        if(!inrange(x,y)) break;
                        if(arr[x][y]==target) return ret;
                        if(arr[x][y]!='.') break;
                    }
                }
            }
            if(c=='p'){
                int k=i-ret;
                if((inrange(k,j-1) && arr[k][j-1]==target)
                    || (inrange(k,j+1) && arr[k][j+1]==target)) return ret;
            }
        }
    }
    return 0;
}

int main(){
    string arr[8];
    int counter=0;
    while(true){
        counter++;
        for(auto& x: arr) cin>>x;
        bool empty=true;
        for(auto& x: arr){
            if(x!="........"){
                empty=false;
                break;
            }
        }
        if(empty) break;
        int val=func(arr);
        cout<<"Game #"<<counter<<": "
            <<(val==0?"no" : val==1?"black":"white")
            <<" king is in check."<<endl;
    }
}