#include <bits/stdc++.h>
using namespace std;
 
#define rng(x) x.begin(), x.end()
#define pb push_back
#define F first
#define S second
#define el '\n'
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
 
typedef long long ll;
typedef pair<int,int> pi;
typedef pair<ll,ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<bool> vb;
 
/*-----------------------------Code begins----------------------------------*/

// HackerRank question link : -
// Determining DNA Health

const int N = 2e6;
int nxt = 1;
vvi inds(N);
vvi trie(N, vi(26, -1));
vi cost(N);
vi failSafe(N);
vector <string> pat(N);
int n;

void build(int i){
	int v = 0;
	for(char c : pat[i]){
		if(trie[v][c - 'a'] == -1)
			trie[v][c - 'a'] = nxt++;
		v = trie[v][c - 'a'];
	}
	inds[v].pb(i);
}

void dfs(int node = 0, int par = -1, char c = '$'){
	db(node, par, c);
	if(node != 0 and par != 0){
		int v = failSafe[par];
		while(trie[v][c-'a'] == -1){
			if(v == 0) break;
			v = failSafe[v];
		}
		if(trie[v][c-'a'] != -1) 
			failSafe[node] = trie[v][c-'a'];
	}
	for (int i = 0; i < 26; ++i){
		if(trie[node][i] != -1)
			dfs(trie[node][i], node, (char)('a' + i));
	}
}

void solve(){
    cin>>n;
    for (int i = 0; i < n; ++i){
    	cin>>pat[i];
    	build(i);
    }
    dfs();
    for (int i = 0; i < n; ++i){
    	cin>>cost[i];
    }
    for (int i = 0; i < 7; ++i){
    	db(trie[i]);
    	db(inds[i]);
    	db(failSafe[i]);
    }
    ll mx = 0, mn = LLONG_MAX; 
    int q; cin>>q;
    while(q--){
    	int l, r; cin>>l>>r;
    	l--; r--;
    	string str; cin>>str;
    	ll v = 0, i = 0, sm = 0;
    	while(i < str.length()){
    		char c = str[i];
    		db(c, v);
    		if(trie[v][c - 'a'] == -1){
    			if(v == 0) i++;
    			v = failSafe[v];
    		}else{
    			v = trie[v][c - 'a'];
    			i++;
    		}
    		for(int id : inds[v]){
    			if(id >= l and id <= r)
    				sm += cost[id];
    		}
    		db(sm);
    	}
    	mx = max(mx, sm);
    	mn = min(mn, sm);
    }
    cout<<mn<<" "<<mx<<el;
}
 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T=1, tc = 1;
    // cin>>T; 
    while(T--){
        solve();
    }
    return 0; 
}