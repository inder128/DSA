#include <bits/stdc++.h>
using namespace std;

#define deb(x) cout<<#x<<"="<<x<<endl
#define deb2(x,y) cout<<#x<<"="<<x<<", "<<#y<<"="<<y<<endl
#define deb3(x,y,z) cout<<#x<<"="<<x<<", "<<#y<<"="<<y<<", "<<#z<<"="<<z<<endl
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

// codeforces question link :-
// https://codeforces.com/contest/1380/problem/E

const int N = 2e5;
int n, m; 
vi par(N), val[N], tower(N);


int getPar(int u){
	return u == par[u] ? u : par[u] = getPar(par[u]);
	// less efficient then above; 
	// return u == par[u] ? par[u] : getPar(par[u]);
}


void solve(){
	cin>>n>>m;
	int ans = n-1;
	for (int i = 0; i < n; ++i){
		int x; cin>>x; x--;
		tower[i] = x;
		val[x].pb(i);
		ans -= (i and tower[i]==tower[i-1]);
	}

	for (int i = 0; i < m; ++i){
		par[i] = i;
	}
	
	cout<<ans<<el;
	for (int i = 0; i < m-1; ++i){
		int u, v; cin>>u>>v;
		u--; v--;
		u = getPar(u); v = getPar(v);

		// more efficient :- making smaller set child of bigger set;
		if(val[u].size() > val[v].size())
			swap(u, v);

		for(int x : val[u]){
			ans -= (x and tower[x-1]==v);
			ans -= (x<n-1 and tower[x+1]==v);
		}

		for(int x : val[u]){
			val[v].pb(x);
			tower[x] = v;
		}

		par[u] = v;

		cout<<ans<<el;
	}
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