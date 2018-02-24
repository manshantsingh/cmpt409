//CMPT 409 Assignment 3
//Problem: Bribing FIPA
//Team Members: Heather Li, Ekjot Singh Billing, Manshant Singh Kohli


 #include <iostream>
 #include <utility>
 #include <vector>
 #include <map>
 #include <sstream>
 #include <climits>
 using namespace std;


//function return value returns the nodes under and including root
//also loads the DP array
 int dpload(int root,vector<vector<int> > &dp,vector<vector <int> > &adj, vector <int>  &costs)  {
   int ret = 0;
   dp[root][0] = 0;
   for (auto &child:adj[root]){
     int childans = dpload(child,dp,adj,costs);

     ret += childans;
     for(int i=ret;i>0;i--) {
         for(int j=1;j<=i;j++) {
            dp[root][i] = min(dp[root][i], dp[root][i-j]+dp[child][j]);
        }
     }
   }
   ret++;
   for (int i=1;i<=ret;i++){
    dp[root][i] = min(dp[root][i], costs[root]);
   }
   return ret;
 }

int main(){
    int m,n;
    string country;
    int bribe,currindex;
    string buffer;

    while (true){

        getline(cin,buffer);
        if (buffer=="#")
            break;

        stringstream ss(buffer);

        ss >> n >> m;
        vector<vector<int> > adj(n+1);
        vector<int> costs(n+1,0);
        vector<bool> ischild(n+1,false);
        vector<int> retvals(n+1,0);
        map <string,int> cmap;
        int ccounter=0;
        for (int i=0;i<n;i++){
            getline(cin,buffer);
            stringstream ss(buffer);
            ss >> country >> bribe;
            if (cmap.find(country)==cmap.end()){
                ccounter++;
                cmap.insert(make_pair(country,ccounter));
            }
            currindex=cmap[country];
            costs[currindex]=bribe;

            while (ss>> country){

                if (cmap.find(country)==cmap.end()){
                    ccounter++;
                    cmap.insert(make_pair(country,ccounter));
                }
                adj[currindex].push_back(cmap[country]);
                ischild[cmap[country]]=true;
            }
        }

        costs[0]=INT_MAX;

        for (int i=1;i<=n;i++){
            if (ischild[i]==false){
                adj[0].push_back(i);
            }
        }

        vector<vector<int> > dp(n+1,vector<int>(n+1,100000000)); //INT_MAX gives weird overflows?

        //dp[i][j] shows the minimum amount of diamonds to bribe j of country i and its subjugates
        dpload(0,dp,adj,costs);

        cout << dp[0][m] << endl;
    }

}
