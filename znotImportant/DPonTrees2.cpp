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

const int N = 1e4;
const int mxK = 100;
vector <vl> DP(N, vl(mxK));
// tree is rooted at 0;
// sub-tree :- set of conected nodes;
// DP[i, j] :- no of sub-trees rooted at i having j nodes;
vl rooted(N), total(N);
// rooted[i] :- no of sub-trees rooted at i;
// total[i] :- total no of sub-trees in the subtree rooted at i;
vi adj[N];
int n, K;

void dfs(int node = 0, int par = -1){
	rooted[node] = 1;
	total[node] = 0;
	DP[node][0] = 1;

	for(int child : adj[node]){
		if(child == par) continue;
		dfs(child, node);
		rooted[node] *= (1+rooted[child]);
		total[node] += total[child];

		vl CDP(mxK); CDP[0] = 1;
		for (int ok = 0; ok < K; ++ok){
			for (int ck = 0; ok + ck < K; ++ck){
				CDP[ok + ck + 1] += DP[node][ok] * DP[child][ck]; 
			}
		}
		DP[node] = CDP;
	}

	total[node] += rooted[node];
}

void solve(){
	cin>>n>>K;
	for (int i = 0; i < n-1; ++i){
		int u, v; cin>>u>>v;
		u--; v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}

	dfs();
	// author's method;
	// rec();

	ll sum = 0;
	for (int i = 0; i < n; ++i)
		for (int k = 1; k <= K; ++k)
			sum += DP[i][k];

	cout<<sum<<el;
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

