#include <bits/stdc++.h>
using namespace std;

//masks to represent different poker hand combinations
const uint64_t ONE = 1ull<<52,
            TWO = 1ull<<53,
            THREE = 1ull<<54,
            STRAIGHT = 1ull<<55,
            FLUSH = 1ull<<56,
            HOUSE = 1ull<<57,
            FOUR = 1ull<<58,
            SF = 1ull<<59;

uint64_t getVal(istringstream& iss){
    vector<int> v(13, 0);
    unordered_map<char, int> m;
    int num_cards=5;
    while(num_cards--){
        string s; iss>>s;
        switch(s[0]){
            case 'A':
                v[12]++;
                break;
            case 'K':
                v[11]++;
                break;
            case 'Q':
                v[10]++;
                break;
            case 'J':
                v[9]++;
                break;
            case 'T':
                v[8]++;
                break;
            default:
                v[s[0]-'2']++;
        }
        m[s[1]]++;
    }
    uint64_t val=0;
    bool flag=false;
    // If all cards belong to same suite, set the FLUSH bit to true
    for(auto& x: m) if(x.second==5) val|=FLUSH;
    for(int i=0;i<13;i++){
        if(!flag && i<9){
            // If all 5 cards are consecutive, set the STRAIGHT bit to true
            flag=true;
            for(int j=0;j<5;j++){
                if(v[i+j]!=1){
                    flag=false;
                    break;
                }
            }
            if(flag) val|=STRAIGHT;
        }
        // if hand has many cards with same value, set the corresponding bit(s) to true
        if(v[i]==2){
            if((val&ONE)!=0) val|=TWO;
            else val|=ONE;
        }
        else if(v[i]==3) val|=THREE;
        else if(v[i]==4) val|=FOUR;
    }
    // Check if it's a full house
    if((val&THREE)!=0 && (val&ONE)!=0) val|=HOUSE;

    // If it's a Straight Flush, set the bit and set a mask for the biggest consecutive value 
    if((val&STRAIGHT)!=0 && (val&FLUSH)!=0){
        val|=SF;
        for(int i=12;i>=0;i--) if(v[i]==1) {
            val|=1ull<<i;
            break;
        }
    }

    // If There is Four of a kind, then mask the cards giving presidence
    // to the card value with all 4 suites.
    else if((val&FOUR)!=0){
        for(int i=12;i>=0;i--){
            if(v[i]==1) val|=1ull<<i;
            else if(v[i]==4) val|=1ull<<i+20;
        }
    }
    // If it's a Full house, then mask the cards giving presidence
    // to the card value with 3 suites
    else if((val&HOUSE)!=0){
        for(int i=12;i>=0;i--){
            if(v[i]==2) val|=1ull<<i;
            else if(v[i]==3) val|=1ull<<i+20;
        }
    }
    // If it's a Flush, then mask all the cards
    else if((val&FLUSH)!=0){
        for(int i=12;i>=0;i--) if(v[i]==1) val|=1ull<<i;
    }
    // If it's a Straight, then set a mask for the biggest consecutive value
    else if((val&STRAIGHT)!=0){
        for(int i=12;i>=0;i--) if(v[i]==1) {
            val|=1ull<<i;
            break;
        }
    }
    else if((val&THREE)!=0){
        for(int i=12;i>=0;i--){
            if(v[i]==1) val|=1ull<<i;
            else if(v[i]==3) val|=1ull<<i+20;
        }
    }
    else if((val&TWO)!=0){
        for(int i=12;i>=0;i--){
            if(v[i]==1) val|=1ull<<i;
            else if(v[i]==2) val|=1ull<<i+20;
        }
    }
    else if((val&ONE)!=0){
        for(int i=12;i>=0;i--){
            if(v[i]==1) val|=1ull<<i;
            else if(v[i]==2) val|=1ull<<i+20;
        }
    }
    else{
        for(int i=12;i>=0;i--){
            int pos=i*4+3;
            while(v[i]--){
                val|=1ull<<pos;
                pos--;
            }
        }
    }
    return val;
}

int main(){
    string s;
    while(getline(cin, s)){
        if(s.empty()) continue;
        istringstream iss(s);
        uint64_t black=getVal(iss);
        uint64_t white=getVal(iss);
        if(black>white) cout<<"Black wins."<<endl;
        else if(black<white) cout<<"White wins."<<endl;
        else cout<<"Tie."<<endl;
    }
}