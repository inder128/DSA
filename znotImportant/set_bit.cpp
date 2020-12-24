#include <bits/stdc++.h>
using namespace std;

// insert, delete and access by index in constant time;
// can't know size of set in constant time;
// set[size_of_set + 1] == M+1; always;
// so to find size we have to binary search;
struct Set {
    vector<int> bit;
    int n;
    Set(int M){
        n=(int)M+2;
        bit.resize(n);
    }
    void insert(int val){
        for (++val; val<n; val+=val&-val) {
            bit[val]+=1;
        }
    }
    void erase(int val){
        for (++val; val<n; val+=val&-val) {
            bit[val]-=1;
        }
    }
    int index(int j){
        int ans=-1;
        for (++j; j; j-=j&-j){
            ans+=bit[j];
        }
        return ans;
    }
    int lower_find(int val) { /// last value < or <= to val
        int idx = 0;
        for(int i = 31-__builtin_clz(n); i >= 0; --i) {
            int nidx = idx | (1 << i);
            if(nidx < n && bit[nidx] < val) { /// change <= to <
                val -= bit[nidx];
                idx = nidx;
            }
        }
        return idx;
    }
    int operator [](int id){
        id++;
        return lower_find(id);
    }
};
 
int main(){
    Set set(1000); // M=1000;

    set.insert(1);
    set.insert(14);
    set.insert(11);
    set.insert(100);

    cout<<set[4]<<el;
    cout<<set[5]<<el; // return 10001;
    return 0; 
}