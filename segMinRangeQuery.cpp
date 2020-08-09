#include <bits/stdc++.h>
using namespace std;

#define deb(x) cout<<#x<<"="<<x<<endl
#define deb2(x,y) cout<<#x<<"="<<x<<", "<<#y<<"="<<y<<endl
#define deb3(x,y,z) cout<<#x<<"="<<x<<", "<<#y<<"="<<y<<", "<<#z<<"="<<z<<endl
#define rng(x) x.begin(), x.end()
#define pb push_back
#define F first
#define S second
#define el endl

typedef long long ll;
typedef pair<int,int> pi;
typedef vector<int> vi;
typedef vector<bool> vb;

// codeforces question link :-
// https://codeforces.com/contest/1217/problem/E 

vector <vi> ST(1<<21, vi(10));
vi arr(1<<21);
int n, m;

void update(vi &node, int val){
    node[0] = INT_MAX;
    int x = val;
    for (int i = 1; i < 10; ++i){
        int rem = x%10; x /= 10;
        if(rem) node[i] = val;
        else node[i] = INT_MAX;
    }
}

// if not passed by reference it will give tle;
vi merge(vi &nodel, vi &noder){
    vi node(10, INT_MAX);
    node[0] = min(nodel[0], noder[0]);
    for (int i = 1; i < 10; ++i){
        node[i] = min(nodel[i], noder[i]);
        if(nodel[i] < INT_MAX and noder[i] < INT_MAX)
            node[0] = min(node[0], nodel[i] + noder[i]);
    }
    return node;
}

void constructST(int ind, int l, int r){
    if(l==r) return update(ST[ind], arr[l]);
    int m = (l+r)/2;
    constructST(2*ind+1, l, m);
    constructST(2*ind+2, m+1, r);
    ST[ind] = merge(ST[2*ind+1], ST[2*ind+2]);
}

vi get(int ind, int l, int r, int ql, int qr){
    // [l, r] and [ql, qr] will never be disjoint;
    if(l==ql and r==qr) return ST[ind];
    int m = (l+r)/2;
    if(qr <= m) return get(2*ind+1, l, m, ql, qr);
    else if(ql > m) return get(2*ind+2, m+1, r, ql, qr);
    vi lmn = get(2*ind+1, l, m, ql, m);
    vi rmn = get(2*ind+2, m+1, r, m+1, qr);
    return merge(lmn, rmn);
}

void update(int ind, int l, int r, int pos, int val){
    if(l==r) return update(ST[ind], val);
    int m = (l+r)/2;
    if(pos <= m) update(2*ind+1, l, m, pos, val);
    else update(2*ind+2, m+1, r, pos, val);
    ST[ind] = merge(ST[2*ind+1], ST[2*ind+2]);
}

void solve(){
    cin>>n>>m;
    for (int i = 0; i < n; ++i) cin>>arr[i];
    
    constructST(0, 0, n-1);

    for (int i = 0; i < m; ++i){
        int t, x, y; cin>>t>>x>>y;
        if(t==1) update(0, 0, n-1, x-1, y);
        else{
            int ans = get(0, 0, n-1, x-1, y-1)[0];
            cout<<(ans==INT_MAX ? -1 : ans)<<el;
        }
    }

}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    #ifndef ONLINE_JUDGE 
        freopen("input.txt", "r", stdin); 
        freopen("output.txt", "w", stdout); 
    #endif
    int T=1;
    // cin>>T; 
    while(T--)
        solve();
    return 0; 
}

// codeforces question link :-
// https://codeforces.com/contest/1208/problem/D

namespace SegmentTree {
    int n;
    ll t[4 * MAXN];
    ll mod[4 * MAXN];

    void pull(int v) {
        t[v] = min(t[2 * v + 1], t[2 * v + 2]);
    }

    void apply(int v, ll val) {
        t[v] += val;
        mod[v] += val;
    }

    void push(int v) {
        if (mod[v] != 0) {
            apply(2 * v + 1, mod[v]);
            apply(2 * v + 2, mod[v]);
            mod[v] = 0;
        }
    }

    void build(int v, int l, int r) {
        if (l + 1 == r) {
            t[v] = a[l];
        } else {
            int m = (r + l) >> 1;
            build(2 * v + 1, l, m);
            build(2 * v + 2, m, r);
            pull(v);
        }
    }

    void add(int v, int l, int r, int ql, int qr, ll val) {
        if (r <= ql || qr <= l) {
            return;
        } else if (ql <= l && r <= qr) {
            apply(v, val);
        } else {
            push(v);
            int m = (r + l) >> 1;
            add(2 * v + 1, l, m, ql, qr, val);
            add(2 * v + 2, m, r, ql, qr, val);
            pull(v);
        }
    }

    int go_down(int v, int l, int r) {
        if (l + 1 == r) {
            return l;
        } else {
            push(v);
            int m = (r + l) >> 1;
            int res = -1;
            if (t[2 * v + 2] == 0) {
                res = go_down(2 * v + 2, m, r);
            } else {
                res = go_down(2 * v + 1, l, m);
            }
            pull(v);
            return res;
        }
    }

    void init(int n_) {
        n = n_;
        build(0, 0, n);
    }

    void add(int l, int r, ll val) {
        add(0, 0, n, l, r, val);
    }

    void add(int pos, ll val) {
        add(0, 0, n, pos, pos + 1, val);
    }

    int last_zero() {
        return go_down(0, 0, n);
    }
}