#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> coord_t;

// directional arrays for connected grid points
int dx[]={0,-1,1,0};
int dy[]={-1,0,0,1};
char lower_dir[]={'w','n','s','e'};
char upper_dir[]={'W','N','S','E'};
int rows, cols;

typedef tuple<coord_t, coord_t, string, coord_t> my_tuple;
struct cmp{
    bool operator()(const my_tuple& a, const my_tuple& b){
        coord_t c = get<3>(a), d = get<3>(b);
        if(c.first != d.first) return c.first>d.first;
        return c.second>d.second;
    }
};

uint64_t hashable(const coord_t& a, const coord_t& b){
    return (((uint64_t)((a.first << 10) | a.second)) << 32) | ((uint64_t)((b.first << 10) | b.second));
}

bool outOfRange(coord_t x){
    return x.first<0||x.first>=rows||x.second<0||x.second>=cols;
}

// function that computes the shortest path from current player position to behind the box
// to have it ready for push
string inner_bfs(coord_t bPos, coord_t b, coord_t cPos, vector<vector<bool>>& grid){
    if(cPos==b){
        return "";
    }
    queue<pair<coord_t, string>> q;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    q.push({cPos, ""});
    visited[cPos.first][cPos.second]=true;
    while(q.size()){
        coord_t curr; string currPath;
        tie(curr, currPath) = q.front();
        q.pop();
        for(int i=0;i<4;i++){
            coord_t c = {curr.first + dx[i], curr.second + dy[i]};
            if(outOfRange(c) || grid[c.first][c.second] ||
                visited[c.first][c.second] || c == bPos) continue;
            if(c==b){
                return currPath + lower_dir[i];
            }
            q.push({c, currPath + lower_dir[i]});
            visited[c.first][c.second]=true;
        }
    }
    // not reachable
    return "x";
}

int main(){
    int caseNum=0;
    while(true){
        cin>>rows>>cols>>ws;
        if(rows==0 && cols==0) break;

        cout<<"Maze #"<<++caseNum<<endl;

        coord_t start, end, box;
        vector<vector<bool>> grid(rows, vector<bool>(cols));
        for(int i=0;i<rows;i++){
            string line; getline(cin, line);
            for(int j=0;j<cols;j++){
                if(line[j]=='#'){
                    grid[i][j]=true;
                    continue;
                }
                grid[i][j]=false;
                if(line[j]=='T') end = coord_t(i,j);
                else if(line[j]=='S') start = coord_t(i,j);
                else if(line[j]=='B') box = coord_t(i,j);
            }
        }
        priority_queue<my_tuple, vector<my_tuple>, cmp> q;
        unordered_map<uint64_t, coord_t> m;

        q.push({box, start, "", {0,0}});
        m[hashable(box, start)]={0,0};
        bool done=false;
        my_tuple answer;
        while(!q.empty()){
            coord_t bPos, cPos, steps; string currPath;
            tie(bPos, cPos, currPath, steps) = q.top();
            q.pop();
            if(done){
                coord_t val = get<3>(answer);
                // if the value is greater than the best value found so far,
                //    then it means priority queue has no more better values
                if(steps.first > val.first || 
                    (steps.first==val.first && steps.second>=val.second)) break;
            }

            for(int i=0;i<4;i++){
                coord_t f = {bPos.first + dx[i], bPos.second + dy[i]};
                coord_t b = {bPos.first - dx[i], bPos.second - dy[i]};

                if(outOfRange(f) || outOfRange(b) ||
                    grid[b.first][b.second] || grid[f.first][f.second]) continue;

                uint64_t hb = hashable(f, bPos);
                if(m.find(hb)!=m.end()){
                    coord_t val = m[hb];
                    if(steps.first > val.first || 
                        (steps.first ==val.first && steps.second >= val.second)) continue;
                }

                string c = inner_bfs(bPos, b, cPos, grid);

                // route not found
                if(c=="x") continue;

                coord_t newSteps = {steps.first+1, steps.second + 1 + c.size()};
                if(f == end){
                    if(done){
                        coord_t val = get<3>(answer);
                        // if the value is greater than the best value found so far,
                        //    then ignore this value
                        if(newSteps.first > val.first || 
                            (newSteps.first==val.first && newSteps.second>=val.second)) continue;
                    }
                    done=true;
                    // best answer found so far
                    answer = {f, bPos, currPath + c + upper_dir[i], newSteps};
                    continue;
                }
                if(m.find(hb)!=m.end()){
                    coord_t val = m[hb];
                    if(newSteps.first > val.first || 
                        (newSteps.first==val.first && newSteps.second>=val.second)) continue;
                }
                q.push({f, bPos, currPath + c + upper_dir[i], newSteps});

                m[hb]=newSteps;
            }
        }
        if(!done){
            cout<<"Impossible."<<endl<<endl;
        }
        else{
            cout<<get<2>(answer)<<endl<<endl;
        }
    }
}