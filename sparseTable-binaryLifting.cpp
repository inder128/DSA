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

// codeNation hiring challenge :- xor and graph paths;

const int N = 1e5, B = 17;
// sparse table;
vector <set<int>> SPT[B];
 
void solve(){
	SPT[0] = vector <set<int>>(N);
	for (int i = 0; i < N-1; ++i){
		SPT[0][i].insert(i);
		SPT[0][i].insert(i+1);
	}
	for (int b = 1; b < B; ++b){
		SPT[b] = vector <set<int>>(N - (1<<b));
		for (int i = 0; i < N-(1<<b); ++i){
			for(int pos : SPT[b-1][i]){
				for(int ind : SPT[b-1][pos]){
					if(SPT[b][i].find(ind) != SPT[b][i].end())
						SPT[b][i].erase(ind);
					else 
						SPT[b][i].insert(ind);
				}
			}
		}
	}

	

	int x, n, k; cin>>x>>n>>k; k--;
	vi a(x); for(int &i : a) cin>>i;

	vector <set <int>> ans(x);
	for (int i = 0; i < x; ++i) ans[i].insert(i);

	for (int b = 16; b >= 0; --b){
		if(n < (1<<b)) continue;
		n -= (1<<b);
		x -= (1<<b);
		vector <set<int>> ta(x);
		for (int i = 0; i < x; ++i){
			for(int pos : SPT[b][i]){
				for(int ind : ans[pos]){
					if(ta[i].find(ind) != ta[i].end())
						ta[i].erase(ind);
					else 
						ta[i].insert(ind);
				}
			}
		}
		ans = ta;
	}
	
	int res = 0;
	for (int i : ans[k]){
		res ^= a[i];
	}
	cout<<res<<el;
}
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	#ifndef ONLINE_JUDGE 
		freopen("input.txt", "r", stdin); 
		freopen("output.txt", "w", stdout); 
	#endif
	int T=1, tc = 1;
	// cin>>T; 
	while(T--){
		solve();
	}
	return 0; 
}