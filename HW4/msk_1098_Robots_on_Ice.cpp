#include <bits/stdc++.h>
using namespace std;

int rows, cols;
vector<vector<bool>> grid;
int points[6];
int checksteps[3];
int totalSteps;
int numSolutions;

int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};

bool inRange(int r, int c){
    return r>=0 && r<rows && c>=0 && c<cols;
}

void func(int r, int c, int steps){
    if(r==0&&c==1){
        if(steps == totalSteps) numSolutions++;
        return;
    }

    // reached checkpoint on wrong number of steps
    for(int i=0;i<3;i++){
        if(r==points[2*i] && c==points[2*i+1] && steps != checksteps[i]){
            return;
        }
    }

    // reached checkpoint late
    for(int i=0;i<3;i++){
        if(steps==checksteps[i] && (r!=points[2*i] || c!=points[2*i+1])){
            return;
        }
    }

    // not enough steps to reach the checkpoint in time
    for(int i=0;i<3;i++){
        if(steps < checksteps[i] && abs(r-points[2*i])+abs(c-points[2*i + 1]) > checksteps[i] - steps){
            return;
        }
    }

    // cout<<"got so far"<<endl;
    // check if the graph got disconnected
    vector<vector<bool>> another(rows, vector<bool>(cols, false));
    queue<pair<int,int>> q;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(!grid[i][j]){
                q.push({i,j});
                another[i][j]=true;
                break;
            }
        }
        if(q.size()) break;
    }
    while(!q.empty()){
        auto f = q.front();
        q.pop();
        for(int i=0;i<4;i++){
            int x = f.first + dx[i];
            int y = f.second + dy[i];

            if(inRange(x,y) && !another[x][y] && !grid[x][y]){
                q.push({x,y});
                another[x][y]=true;
            }
        }
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(!grid[i][j] && !another[i][j]){
                return;
            }
        }
    }

    // check for singles neighbours
    int numSingles = 0, index = -1;
    for(int i=0;i<3;i++){
        int x = r+dx[i];
        int y = c+dy[i];
        if(inRange(x, y) && !grid[x][y] && !(x==0 && y==1)){
            int n=0;
            for(int j=0;j<4;j++){
                int xx=x+dx[j];
                int yy=y+dy[j];
                if(inRange(xx, yy) && !grid[xx][yy]){
                    n++;
                }
            }
            if(n==0) return;
            if(n==1){
                numSingles++;
                index = i;
            }
        }
    }

    if(numSingles>1) return;
    else if(numSingles==1){
        int x = r+dx[index];
        int y = c+dy[index];
        grid[x][y]=true;  
        func(x, y, steps+1);
        grid[x][y]=false;
        return;
    }

    // the regular non single case
    for(int i=0;i<4;i++){
        int x=r+dx[i];
        int y=c+dy[i];

        if(inRange(x, y) && !grid[x][y]){
            grid[x][y]=true;    
            func(x, y, steps+1);
            grid[x][y]=false;
        }
    }
}

int main(){
    int caseNum=0;
    while(true){
        cin>>rows>>cols;
        if(rows==0 && cols==0) break;
        for(auto& x: points) cin>>x;

        grid = vector<vector<bool>>(rows, vector<bool>(cols, false));
        totalSteps = rows*cols;
        checksteps[0] = totalSteps/4;
        checksteps[1] = totalSteps/2;
        checksteps[2] = (3*totalSteps)/4;

        numSolutions = 0;
        grid[0][0]=true;
        func(0,0,1);
        cout<<"Case "<< ++caseNum << ": "<<numSolutions<<endl;

    }
}