#include <iostream>
#include <bitset>

using namespace std;
/*
template <size_t bitsetsize>
void fillin  (bitset<bitsetsize> arr[], char inp,int i,int j) {
    if (inp=='r' || inp=='q'){
        arr[i].set();
        for (int l=0;l<8;l++){
            arr[l].set(j);
        }
        arr[i].set(j,0);
    }
    if (inp=='d' || inp=='q'){
        for (int offset=1;offset<8;offset++){
            bool right= offset+j <8;
            bool top= offset-i >=0;
            bool left= j-offset >=0;
            bool bot= offset+j<8;
            if (top){
                if (right) arr[i-offset].set(j+offset);
                if (left) arr[i-offset].set(j-offset);
            }
            if (bot) {
                if (right) arr[i+offset].set(j+offset);
                if (left) arr[i+offset].set(j-offset);
            }

        }
        arr[i].set(j,0);
    }
    if (inp=='k'){
        bool right= j+1 <8;
        bool top= i-1 >=0;
        bool left= j-1 >=0;
        bool bot= j+1<8;
        if (top){
            arr[i-1].set(j);
            if (left)   arr[i-1].set(j-1);
            if (right)   arr[i-1].set(j+1);
        }
        if (left)   arr[i].set(j-1);
        if (right)   arr[i].set(j+1);
        if (bot){
            arr[i+1].set(j);
            if (left)   arr[i+1].set(j-1);
            if (right)   arr[i+1].set(j+1);
        }
    if (inp=='p'){
        bool right= 1+j <8;
        bool left= j-1 >=0;
        bool bot= i+1<8;
        if (bot) {
            if (right) arr[i+1].set(j+1);
            if (left) arr[i+1].set(j-1);
        }
    }
    if (inp=='P'){
        bool right= 1+j <8;
        bool left= j-1 >=0;
        bool top= i-1>=0;
        if (top) {
            if (right) arr[i-1].set(j+1);
            if (left) arr[i -1].set(j-1);
        }
    }
    if (inp=='n'){
        int orient[2]={-1,1};
        for (int k=1;k<3;k++){
            int l=3-k;
            for (int x=0;x<2;x++){
                for (int y=0;j<2;j++){
                    int icoord=i+(orient[x]*k);
                    int jcoord=j+(orient[y]*l);
                    if (icoord>=0 && icoord <8 && jcoord >=0 && jcoord <8)
                        arr[icoord].set(jcoord);
                }
            }

        }
    }

}*/

//movethrough pieces
int main() {
    const int MAKELOWER = 'a'-'A';
    char board[8][8];
    int num=0;
    while (true){
      num++;
      int wking=-1;
      int bking=-1;
      for (int i=0;i<8;i++){
          for (int j=0;j<8;j++){
              cin >> board[i][j];
              if (board[i][j]=='k')
                  bking=i*8+j;
              if (board[i][j]=='K')
                  wking=i*8+j;
          }
      }

      if (wking==-1 || bking==-1)
        break;

      int i=wking/8;
      int j=wking%8;
      bool incheck[2]={false,false}; //incheck[0]=white, incheck[1]=black
      int charup=0;
      for (int cases=0;cases<2 && !incheck[0]; cases++){
        if (cases==1){
          charup=MAKELOWER;
          i=bking/8;
          j=bking%8;
        }

        //scan down king
        for (int k=i+1;k<8 && !incheck[cases];k++){
          if (board[k][j]==char('r'-charup) ||board[k][j]==char('q'-charup))
            incheck[cases]=true;
          if (board[k][j]!='.') break;//blocked by a piece
        }
        // if (incheck[cases]) cout <<cases << "down" <<endl;
        //scan up king
        for (int k=i-1;k>=0 && !incheck[cases];k--){
          if (board[k][j]==char('r'-charup) ||board[k][j]==char('q'-charup))
            incheck[cases]=true;
          if (board[k][j]!='.') break;//blocked by a piece
        }
          // if (incheck[cases]) cout << "up" <<endl;
        //scan right king
        for (int l=j+1;l<8 && !incheck[cases];l++){
          if (board[i][l]==char('r'-charup) ||board[i][l]==char('q'-charup))
            incheck[cases]=true;
          if (board[i][l]!='.') break;//blocked by a piece
        }
          // if (incheck[cases]) cout << "right" <<endl;
        //scan left king
        // cout << j << " ";
        for (int l=j-1;l>=0 && !incheck[cases];l--){
          // cout << "inleft"<< board[i][l] ;
          if (board[i][l]==char('r'-charup) ||board[i][l]==char('q'-charup))
            incheck[cases]=true;
          if (board[i][l]!='.') break;//blocked by a piece
        }
        //  if (incheck[cases]) cout << cases << "left" <<endl;
        //scan bottom right diagonal
        for (int offset=1;i+offset<8 && j+offset<8 && !incheck[cases];offset++){
          if (board[i+offset][j+offset]==char('b'-charup) ||board[i+offset][j+offset]==char('q'-charup))
            incheck[cases]=true;
          if (board[i+offset][j+offset]!='.') break; //blocked by a piece
        }
        // if (incheck[cases]) cout << "botright" <<endl;
        //scan top right diagonal
        for (int offset=1;i-offset>=0 && j+offset <8 && !incheck[cases];offset++){
          if (board[i-offset][j+offset]==char('b'-charup) ||board[i-offset][j+offset]==char('q'-charup))
            incheck[cases]=true;
          if (board[i-offset][j+offset]!='.') break; //blocked by a piece
        }
            // if (incheck[cases]) cout << "topright" <<endl;
        //scan top left wking
        for (int offset=1;j-offset>=0 && i-offset>=0 && !incheck[cases];offset++){
          if (board[i-offset][j-offset]==char('b'-charup) ||board[i-offset][j-offset]==char('q'-charup))
            incheck[cases]=true;
          if (board[i-offset][j-offset]!='.') break; //blocked by a piece
        }
                  // if (incheck[cases]) cout << "topleft" <<endl;
        //scan bottom left wking
        for (int offset=1;j-offset>=0 && i+offset<8 && !incheck[cases];offset++){
          if (board[i+offset][j-offset]==char('b'-charup) ||board[i+offset][j-offset]==char('q'-charup))
            incheck[cases]=true;
          if (board[i+offset][j-offset]!='.') break; //blocked by a piece
        }
                          // if (incheck[cases]) cout << "bot" <<endl;
        //scan for black pawns
        if (cases==0){
          if (i-1>=0){
            if (j-1>=0){
              if (board[i-1][j-1]=='p')
                incheck[cases]=true;
            }
            if (j+1<8){
              if (board[i-1][j+1]=='p')
                incheck[cases]=true;
            }
          }
        }
          // if (incheck[cases]) cout << "bpawn" <<endl;
        //scan for white pawns
        if (cases==1){
          if (i+1<8){
            if (j-1>=0){
              if (board[i+1][j-1]=='P')
                incheck[cases]=true;
            }
            if (j+1<8){
              if (board[i+1][j+1]=='P')
                incheck[cases]=true;
            }
          }
        }
                  // if (incheck[cases]) cout << "wpawn" <<endl;
        //scan for knights
        int orient[2]={-1,1};
        for (int k=1;k<3 && !incheck[cases];k++){
            int l=3-k;
            for (int x=0;x<2 && !incheck[cases];x++){
                for (int y=0;y<2 && !incheck[cases];y++){
                    int icoord=i+(orient[x]*k);
                    int jcoord=j+(orient[y]*l);
                    if (icoord>=0 && icoord <8 && jcoord >=0 && jcoord <8){
                      if (board[icoord][jcoord]==char('n'-charup)){
                        incheck[cases]=true;
                        break;
                      }
                    }
                }
            }
          }
                    // if (incheck[cases]) cout << "knight" <<endl;
      }
      cout <<"Game #"<< num << ": ";
      if (incheck[0])
          cout <<"white king is in check." << endl;
      else if (incheck[1])
          cout <<"black king is in check." << endl;
      else
              cout <<"no king is in check." << endl;


    }


    return 0;

}
