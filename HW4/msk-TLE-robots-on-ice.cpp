#include <bits/stdc++.h>
using namespace std;

typedef bitset<128> bitmask_t;
typedef pair<int,int> coord_t;

int rows, cols;
coord_t points[5];
int marks[4];
unordered_map<bitmask_t, int> done;
const bitmask_t ACTUAL_MASK( numeric_limits<uint64_t>::max() );


coord_t directions[]={ {1,0}, {-1,0}, {0,1}, {0,-1} };

bool outOfRange(int r, int c){
    return r<0||r>=rows||c<0||c>=cols;
}

coord_t fromBitmask(const bitmask_t& b){
    int val = (b>>64).to_ulong();
    return {val/cols, val%cols};
}

bitmask_t toBitmask(int r, int c, const bitmask_t& b){
    return (bitmask_t(r*cols+c)<<64)|b;
}

vector<bitmask_t> func(coord_t start, coord_t end, int numSteps, bitmask_t startMask, const set<coord_t>& important){
    vector<bitmask_t> ans;

    startMask = toBitmask(start.first, start.second, startMask);

    queue<pair<bitmask_t, int>> q;
    q.push({toBitmask(start.first, start.second, startMask), numSteps});
    while(q.size()){
        bitmask_t bm; int steps;
        tie(bm, steps) = q.front();
        q.pop();
        coord_t pos = fromBitmask(bm);
        bm &= ACTUAL_MASK;

        steps--;
        for(auto& x: directions){
            int r = pos.first + x.first,
                c = pos.second + x.second;
            if(outOfRange(r,c) || bm.test(r*cols+c)) continue;
            if(abs(r-end.first)+abs(c-end.second)>steps) continue;
            if(end == coord_t(r,c) && steps!=0) continue;
            if(important.find({r,c})!=important.end()) continue;

            bitmask_t mask = bm;
            mask.set(r*cols+c);
            mask |= bitmask_t(r*cols+c)<<64;
            int val = done[mask]++;
            if(val==0){
                if(steps==0) ans.push_back(mask);
                else q.push({mask, steps});
            }
        }
    }
    return ans;
}

vector<pair<bitmask_t, int>> section(coord_t start, coord_t end, int numSteps, bitmask_t startMask, const set<coord_t>& important){

    done.clear();
    vector<bitmask_t> ret = func(start, end, numSteps, startMask, important);
    vector<pair<bitmask_t,int>> ans(ret.size());

    for(int i=0;i<ans.size();i++){
        ans[i] = {ret[i] & ACTUAL_MASK, done[ret[i]]};
    }

    return ans;
}

int main(){
    int caseNum=0;
    while(true){
        cin>>rows>>cols;
        if(rows==0&&cols==0) break;
        for(int i=1;i<=3;i++) cin>>points[i].first>>points[i].second;
        points[0]={0,0};
        points[4]={0,1};

        int total = rows*cols;
        marks[0] = total/4;
        marks[1] = total/2 - marks[0];
        marks[2] = (3*total)/4 - marks[1] - marks[0];
        marks[3] = total - marks[2] - marks[1] - marks[0];

        set<coord_t> important{points[0],points[2], points[3], points[4]};

        // starting steps is marks[0] - 1 since it is already on the first step 
        auto first = section(points[0], points[1], marks[0]-1, bitmask_t(1), important);
        important.erase(points[2]);
        important.insert(points[1]);
        auto second = section(points[1], points[2], marks[1], bitmask_t(), important);
        important.erase(points[3]);
        important.insert(points[2]);
        auto third = section(points[2], points[3], marks[2], bitmask_t(), important);
        important.erase(points[4]);
        important.insert(points[3]);
        auto fourth = section(points[3], points[4], marks[3], bitmask_t(), important);

        vector<pair<bitmask_t, int>> ab, cd;
        for(int i=0;i<first.size();i++){
            for(int j=0;j<second.size();j++){
                bitmask_t x = first[i].first, y = second[j].first;
                bitmask_t xy = x|y;
                if(xy.count() == x.count()+y.count())
                    ab.push_back({xy, first[i].second * second[j].second});
            }
        }
        for(int i=0;i<third.size();i++){
            for(int j=0;j<fourth.size();j++){
                bitmask_t x = third[i].first, y = fourth[j].first;
                bitmask_t xy = x|y;
                if(xy.count() == x.count()+y.count())
                    cd.push_back({xy, third[i].second * fourth[j].second});
            }
        }

        int finalAns=0;
        for(int i=0;i<ab.size();i++){
            for(int j=0;j<cd.size();j++){
                bitmask_t x = ab[i].first, y = cd[j].first;
                bitmask_t xy = x|y;
                if(xy.count() == x.count()+y.count()) finalAns += ab[i].second * cd[j].second;
            }
        }
        cout<<"Case "<<++caseNum<<": "<<finalAns<<endl;
    }
}