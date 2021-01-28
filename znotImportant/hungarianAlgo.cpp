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


// hungarian algo;
// https://codeforces.com/problemset/problem/491/C



/*
w[i][j] = amount bidder j is willing to pay for item i (0 if he is not bidding)
run time is O(nm^2) where n = #of items and m = #of bidders
resets negative bids in w to 0
returns a, where a[i] = j means ith item got assigned to bidder j
a[i] = -1 means item i did not get assigned
for minimizing set w[i][j] = max(w) - w[i][j]
for assigning all, w[i][j] = min(w) + w[i][j]
*/
vi hungarianMethod(vvi W){
    int n = SZ(W), m = SZ(W[0]), PHI = -1, NOL = -2, INF = 1e9;

    vector <vector <bool>> x(n, vector<bool>(m));
    vector <bool> ss(n), st(m);

    int f = 0;
    for (int i = 0; i < n; i++){
        maxi(f, *max_element(rng(W[i])));
    }

    // for minimising;
    // for(auto& wv : W){
    //     for(int& i : wv){
    //         i = f - i;
    //     }
    // }

    vi u(n, f), v(m), p(m, INF), ls(n, PHI), lt(m, NOL), a(n, -1);


    while(true){
        f = -1;
        for (int i = 0; i < n and f == -1; i++){
            if(ls[i] != NOL and ss[i] == 0){
                f = i;
            }
        }

        if(f != -1){
            ss[f] = true;
            for (int j = 0; j < m; j++){
                if (x[f][j] == 0 and u[f] + v[j] - W[f][j] < p[j]) {
                    lt[j] = f;
                    p[j] = u[f] + v[j] - W[f][j];
                }
            }
        } 
        else{
            for(int i = 0; i < m and f == -1; i++){
                if (lt[i] != NOL and st[i] == 0 and p[i] == 0){
                    f = i;
                }
            }

            if(f == -1){
                int d1 = INF, d2 = INF, d;
                for (int i : u){
                    mini(d1, i);
                }
                for (int i : p){
                    if (i > 0){
                        mini(d2, i);
                    }
                }
                d = min(d1, d2);

                for (int i = 0; i < n; i++){
                    if (ls[i] != NOL){
                        u[i] -= d;
                    }
                }

                for (int i = 0; i < m; i++){
                    if (p[i] == 0){
                        v[i] += d;
                    }
                    if (p[i] > 0 and lt[i] != NOL){
                        p[i] -= d;
                    }
                }

                if(d2 >= d1){
                    break;
                }
            } 
            else{
                st[f] = true;
                int s = -1;

                for (int i = 0; i < n and s == -1; i++){
                    if(x[i][f]){
                        s = i;
                    }
                }

                if(s == -1){
                    for (int l, r; ; f = r){
                        r = f;
                        l = lt[r];

                        if(r >= 0 and l >= 0){
                            x[l][r] = !x[l][r];
                        }
                        else{
                            break;
                        }

                        r = ls[l];
                        if (r >= 0 and l >= 0){
                            x[l][r] = !x[l][r];
                        }
                        else{
                            break;
                        }
                    }

                    fill(rng(p), INF);
                    fill(rng(lt), NOL);
                    fill(rng(ls), NOL);
                    fill(rng(ss), false);
                    fill(rng(st), false);

                    for (int i = 0; i < n; i++){
                        bool ex = true;
                        for (int j = 0; j < m and ex; j++){
                            ex = !x[i][j];
                        }
                        if(ex){
                            ls[i] = PHI;
                        }
                    }
                } 
                else{
                    ls[s] = f;
                }
            }
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if(x[i][j]){
                a[j] = i;
            }
        }
    }
    
    return a;
}


void solve(){
    map <char, int> ind;
    map <int, char> revInd;
    for(char ch = 'a'; ch <= 'z'; ++ch){
        ind[ch] = ch - 'a';
        revInd[ind[ch]] = ch;
    }
    for(char ch = 'A'; ch <= 'Z'; ++ch){
        ind[ch] = (ch - 'A') + 26;
        revInd[ind[ch]] = ch;
    }

    int n, k; cin>>n>>k;
    string a, b; cin>>a>>b;

    // filling with 1 to avoid (matching[i] == -1);
    vvi W(k, vi(k, 1));

    for(int i = 0; i < n; ++i){
        W[ind[a[i]]][ind[b[i]]]++;
    }

    vi matching = hungarianMethod(W);

    db(matching);

    int ans = 0;
    string res(k, '$');
    for(int i = 0; i < k; ++i){
        db(W[i]);
        ans += W[matching[i]][i] - 1;
        res[matching[i]] = revInd[i];
    }

    cout<<ans<<el<<res<<el;
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