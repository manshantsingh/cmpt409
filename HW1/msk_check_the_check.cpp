#include <bits/stdc++.h>
using namespace std;

    // Arrays representing horizontal & vertical directions
int hx[]={-1,0,1,0},
    hy[]={0,-1,0,1},
    // Arrays representing diagnal directions
    dx[]={-1,-1,1,1},
    dy[]={-1,1,-1,1},
    // Arrays representing knight directions
    kx[]={-2,-1,2,1,-2,-1,2,1},
    ky[]={1,2,-1,-2,-1,-2,1,2};

bool inrange(int i, int j){
    return i>=0 && i<8 && j>=0 && j<8;
}

int func(string arr[]){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            // Check each position of the chess board
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
            // Check the horizontal & vertical directions if its a queen or rook
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
            // Check the diagonal directions if its a queen or bishop
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
            // If its a pawn, check if it is threatening a king
            if(c=='p'){
                int k=i-ret;
                if((inrange(k,j-1) && arr[k][j-1]==target)
                    || (inrange(k,j+1) && arr[k][j+1]==target)) return ret;
            }
        }
    }
    // Return Tie if no king in threat
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