#include <bits/stdc++.h>
using namespace std;
 
#define rng(x) x.begin(), x.end()
#define maxi(x, y) x = max(x, (y))
#define mini(x, y) x = min(x, (y))
#define pb push_back
#define F first
#define S second
#define el '\n'
#define ll long long
#define SZ(x) ((int)(x).size()) 
template<typename T>
istream&operator>>(istream&is,vector<T>&v){for(auto&it:v)is>>it;return is;}
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {
    return os << "(" << P.F << "," << P.S << ")"; }
template<class T> ostream& operator<<(ostream &os, vector<T> V) {
    os << "[ "; for(auto v : V) os << v << " "; return os << "]"; }
template<class T> ostream& operator<<(ostream &os, set<T> S){
    os << "{ "; for(auto s:S) os<<s<<" "; return os<<"}"; }
#define db(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) { cout<<name<<" : "<<arg1<<'\n';}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
    const char* comma = strchr(names + 1, ',');
    cout.write(names,comma-names)<<" : "<<arg1<<" |";__f(comma+1, args...);}
typedef pair<int,int> pi; typedef vector<int> vi; typedef vector<vi> vvi;
 
/*-----------------------------Code begins----------------------------------*/


int LISonlySize(vi &arr){
    int n = SZ(arr);

    // lb[i] is the smallest and last element of a lis of length i + 1 till now;
    vi lb(n, 1e9);

    for (int i = 0; i < n; ++i){
        // constraints if necessry;;
        // if(arr[i] < 0) continue;

        // longest strictly increasing subsequence;
        int ui = lower_bound(rng(lb), arr[i]) - lb.begin();

        // longest non-decreasing subsequence'
        // int ui = upper_bound(rng(lb), arr[i]) - lb.begin();

        lb[ui] = arr[i];
    }

    int lisSize = -1;
    for (int i = 0; i < n; ++i){
        if(lb[i] < 1e9){
            lisSize = i;
        }
    }

    return lisSize + 1;
}

vi LIS(vi &arr){
    int n = SZ(arr);

    // lb[i] is the smallest and last element of a lis of length i + 1 till now;
    // lbi[i] is the index of lb[i] in the array;
    // lasti[i] is the index of element of arr which comes before lb[i] in the lis;
    vi lb(n, 1e9), lbi(n, -1), lasti(n, -1); 

    for (int i = 0; i < n; ++i){
        // constraints if necessry;;
        // if(arr[i] < 0) continue;

        // longest strictly increasing subsequence;
        int ui = lower_bound(rng(lb), arr[i]) - lb.begin();

        // longest non-decreasing subsequence'
        // int ui = upper_bound(rng(lb), arr[i]) - lb.begin();

        lb[ui] = arr[i], lbi[ui] = i;
        if(ui){
            lasti[i] = lbi[ui - 1];   
        }
    }

    int lisSize = 0;
    for (int i = 0; i < n; ++i){
        if(lb[i] < 1e9){
            lisSize = i;
        }
    }

    vi lis;
    int curr_i = lbi[lisSize];
    while(curr_i != -1){
        lis.pb(curr_i);
        curr_i = lasti[curr_i];
    }
    reverse(rng(lis));


    return lis;
}


void solve(){
    int n; cin>>n;
    vi arr(n); cin>>arr;

    vi lis = LIS(arr);
    db(lis);

    int lisSize = LISonlySize(arr);
    db(lisSize);
}
 
int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T = 1;
    // cin>>T;
    while(T--){
        solve();
    }
    return 0;
}