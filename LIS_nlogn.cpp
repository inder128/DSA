#include <bits/stdc++.h>
using namespace std;
 
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {
    return os << "(" << P.first << "," << P.second << ")"; }
template<class T> ostream& operator<<(ostream &os, vector<T> V) {
    os << "[ "; for(auto v : V) os << v << " "; return os << "]"; }
template<class T> ostream& operator<<(ostream &os, set<T> S){
    os << "{ "; for(auto s:S) os<<s<<" "; return os<<"}"; }
template<class T> ostream& operator<<(ostream &os, multiset<T> S){
    os << "{ "; for(auto s:S) os<<s<<" "; return os<<"}"; }
template<class L, class R> ostream& operator<<(ostream &os, map<L,R> M) {
    os << "{ "; for(auto m:M) os<<"("<<m.F<<":"<<m.S<<") "; return os<<"}"; }
    #define db(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << '\n'; }
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
    const char* comma = strchr(names + 1, ',');
    cout.write(names, comma - names) << " : " << arg1 << " |"; __f(comma + 1, args...); }
#define rng(x) x.begin(), x.end()
#define pb push_back
#define F first
#define S second
#define el '\n'
 
typedef long long ll;
typedef pair<int,int> pi;
typedef pair<ll,ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<bool> vb;
 
/*-----------------------------Code begins----------------------------------*/

void solve(){
    int n; cin>>n;
    vi arr(n); for(int &i : arr) cin>>i;
    // lb[i] = x -> x is the smallest and last element of a lis of length i + 1 till now;
    vi lb, lbi, last(n, -1); 
    lb.pb(arr[0]); lbi.pb(0);
    for (int i = 1; i < n; ++i){
        if(arr[i] > lb.back()){
            last[i] = lbi.back();
            lb.pb(arr[i]); lbi.pb(i); 
        }
        else{
            int ui = lower_bound(rng(lb), arr[i]) - lb.begin(); 
            lb[ui] = arr[i], lbi[ui] = i;
            if(ui) last[i] = lbi[ui - 1];
        }
    }
    vi lis;
    int curr_i = lbi.back();
    while(curr_i != -1){
        lis.pb(curr_i);
        curr_i = last[curr_i];
    }
    reverse(rng(lis));
    cout<<lis.size()<<el;
    // for(int i : lis) cout<<arr[i]<<" ";
}

void solveShort(){
    int n; cin>>n;
    vi arr(n); for(int &i : arr) cin>>i;
    // lb[i] = x -> x is the smallest and last element of a lis of length i + 1 till now;
    vi lb(n, 1e9), lbi(n, -1), last(n, -1); 
    for (int i = 0; i < n; ++i){
        // longest strictly increasing subsequence;
        int ui = lower_bound(rng(lb), arr[i]) - lb.begin();

        // longest non-decreasing subsequence'
        // int ui = upper_bound(rng(lb), arr[i]) - lb.begin();

        lb[ui] = arr[i], lbi[ui] = i;
        if(ui) last[i] = lbi[ui - 1];   
    }
    int lk;
    for (int i = 0; i < n; ++i)
        if(lb[i] < 1e9) lk = i; else break;
    vi lis;
    int curr_i = lbi[lk];
    while(curr_i != -1){
        lis.pb(curr_i);
        curr_i = last[curr_i];
    }
    reverse(rng(lis));
    cout<<lis.size()<<el; 
    // for(int i : lis) cout<<arr[i]<<" "; cout<<el;
}
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T=1, tc = 1;
    cin>>T; 
    while(T--){
        solve();
    }
    return 0; 
}