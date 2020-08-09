#include <bits/stdc++.h>
using namespace std;

#define rng(x) x.begin(), x.end() 
#define pb push_back

typedef vector<int> vi;

int ceil_index(vi &vec, int ind, vi &arr){ 
    int l = 0, r = vec.size() - 1;

    // it is assured that vec is non-empty 
    // and arr[ind] <= arr[vec[r]];
    while(l<r){
        int m = (l+r)/2;

        // here answer will be in seg [m+1, r];
        if(arr[vec[m]] < arr[ind])
            l = m+1;
        else
            r = m;
    }

    // r is the lowest index in vec such that
    // arr[vec[r]] >= arr[ind];
    return r;
}

int main(){
    int n; cin>>n;

    // log and prev both contains indexes;
    vi arr(n), prev(n, -1), log;
    for(int &i : arr) cin>>i;

    log.pb(0);
    for (int i = 1; i < n; ++i){
        if(arr[i] > arr[log.back()]){
            prev[i] = log.back();
            log.pb(i);
            continue;
        }
        int itr = ceil_index(log, i, arr);
        prev[i] = prev[log[itr]];
        log[itr] = i;
    }

    vi LIS;
    int curr_i = log.back();
    while(curr_i!=-1){
        LIS.pb(arr[curr_i]);
        curr_i = prev[curr_i];
    }
    reverse(rng(LIS));

    for(int i : LIS)
        cout<<i<<" ";
    cout<<endl;

    return 0;
}