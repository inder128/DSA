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
typedef pair<ll,ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<bool> vb;
 
const int N = 4e5;
vi par(N), tin(N), tout(N);
vi adj[N], tower(N), same(N);
vvi up(N, vi(20));
vi grp(N);
int t = 0, n, m;
 
void dfs(int node, int dad){
	tin[node] = t++;
 
	par[node] = up[node][0] = dad;
	for (int i = 1; i < 20; ++i)
		up[node][i] = up[up[node][i-1]][i-1];
 
	for(int child : adj[node])
		dfs(child, node);
 
	tout[node] = t++;
}
 
bool isAncestor(int rt, int ch){
	return (tin[rt] <= tin[ch] and tout[rt] >= tout[ch]);
}
 
int lca(int u, int v){
	if(isAncestor(u, v)) return u;
 
	for (int i = 19; i >= 0; --i){
		if(!isAncestor(up[u][i], v))
			u = up[u][i];
	}
	return par[u];
}
 
void solve(){
	cin>>n>>m;
	for (int i = 0; i < n; ++i){
		cin>>tower[i];
		tower[i]--;
	}
 
	for (int i = 0; i < m; ++i){
		grp[i] = i;
	}
	for (int i = 0; i < m-1; ++i){
		int u, v; cin>>u>>v; 
		u--; v--;
		adj[m+i].pb(grp[u]);
		adj[m+i].pb(grp[v]);
		grp[u] = m+i;
	}
 
	dfs(2*m - 2, 2*m - 2);
 
	for (int i = 1; i < n; ++i){
		int node = lca(tower[i], tower[i-1]);
		if(node < m)
			same[0]++;
		else
			same[node - m + 1]++;
	}
 
	for (int i = 1; i < m; ++i)
		same[i] += same[i-1];
 
	for (int i = 0; i < m; ++i)
		cout<<(n - 1 - same[i])<<el;
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