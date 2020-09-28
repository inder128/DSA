#include <bits/stdc++.h>
using namespace std;
 
#define rng(x) x.begin(), x.end()
#define pb push_back
#define F first
#define S second
#define el '\n'
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {
    return os << "(" << P.F << "," << P.S << ")"; }
template<class T> ostream& operator<<(ostream &os, vector<T> V) {
    os << "[ "; for(auto v : V) os << v << " "; return os << "]"; }
template<class T> ostream& operator<<(ostream &os, set<T> S){
    os << "{ "; for(auto s:S) os<<s<<" "; return os<<"}"; }
template<class L, class R> ostream& operator<<(ostream &os, map<L,R> M) {
    os << "{ "; for(auto m:M) os<<"("<<m.F<<":"<<m.S<<") "; return os<<"}";}
#define db(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) { cout<<name<<" : "<<arg1<<'\n';}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
    const char* comma = strchr(names + 1, ',');
    cout.write(names,comma-names)<<" : "<<arg1<<" |";__f(comma+1, args...);}
typedef long long ll; typedef pair<int,int> pi; 
typedef vector<int> vi; typedef vector<ll> vl; typedef vector<vi> vvi;
 
/*-----------------------------Code begins----------------------------------*/

// codeforces question link :-
// https://codeforces.com/contest/1303/problem/E

void solve(){
    string a, b, c; cin>>a>>b;
    int n = a.length(), m = b.length();

    vvi next(n, vi(26, -1));
    next[n-1][a[n-1]-'a'] = n-1;
    for (int i = n-2; i >= 0; --i){
        next[i] = next[i+1];
        next[i][a[i]-'a'] = i;
    }

    for (int l = 0; l <= m-1; ++l){
        // O(n^2) way to find if b and c are non-intersecting subsequences if a;
        // DP[i][j] = minimal length prefix of a needed so that b[0--j-1] and c[0--k-1] are non-i s of that prefix;
        // If there is no such prefix exist then DP[i][j] = infinity;
        vvi DP(l + 1, vi(m-l + 1, INT_MAX));
        // Base Case :-
        DP[0][0] = 0;
        for (int i = 0; i <= l; ++i){
            for (int j = 0; j <= m-l; ++j){
                // next element can't be found;
                if(DP[i][j] >= n) continue;

                // transition states :-
                if(i < l and next[DP[i][j]][c[i]-'a'] != -1)
                    DP[i+1][j] = min(DP[i+1][j], next[DP[i][j]][c[i]-'a'] + 1);
                if(j < m-l and next[DP[i][j]][b[j]-'a'] != -1)
                    DP[i][j+1] = min(DP[i][j+1], next[DP[i][j]][b[j]-'a'] + 1);
            }
        }
        // Final ans :-
        if(DP[l][m-l] <= n){
            cout<<"YES\n";
            return;
        }
        c.pb(b[0]); b.erase(b.begin());
    }

    cout<<"NO\n";


    // O(n^3) way to find if b and c are non-intersecting subsequences if a;
    // DP[i][j][k] = true if b[0--j-1] and c[0--k-1] are non-i s of a[0--i-1];
    // bool DP[n + 1][m1 + 1][m2 + 1];
    // memset(DP, false, sizeof(DP));
    // Base Case :-
    // DP[0][0][0] = true;
    // for (int i = 1; i <= n; ++i){
    //     for (int j = 0; j <= m1; ++j){
    //         for (int k = 0; k <= m2; ++k){
    //             Transitions :-
    //             DP[i][j][k] |= DP[i-1][j][k];
    //             if(j and b[j-1]==a[i-1])
    //                 DP[i][j][k] |= DP[i-1][j-1][k];
    //             if(k and c[k-1]==a[i-1])
    //                 DP[i][j][k] |= DP[i-1][j][k-1];
    //         }
    //     }
    // }
    // Final ans :-
    // cout<<(DP[n][m1][m2] ? "YES" : "NO")<<el;
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