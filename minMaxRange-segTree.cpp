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

// cpodeforces question link
// https://codeforces.com/contest/1385/problem/F
 
const int N = 2e5;
vi adj[N];
int n, k;
 
vi ST(3*N), arr(N), deg(N);
 
int comp(int x, int y){
	return arr[x] >= arr[y] ? x : y;
}
 
void updateUtil(int si, int ss, int se, int i, int diff) { 
	if (i < ss || se < i)  return;
 
	if(ss == se){
		arr[ss] += diff;
		return; 
	}
	int mid = (ss + se)/2; 
	if(i <= mid) updateUtil(2*si+1, ss, mid, i, diff); 
	else updateUtil(2*si+2, mid+1, se, i, diff); 
	ST[si] = comp(ST[2*si+1], ST[2*si+2]);
} 
 
void update(int i, int diff) { 
	updateUtil(0, 0, n-1, i, diff); 
}
 
int getMaxUtil(int si, int ss, int se, int qs, int qe) { 
	if (se < qs || ss > qe) return 0; 
	
	if (qs <= ss && qe >= se) return ST[si]; 
 
	int mid = (ss + se)/2;
	return comp(getMaxUtil(2*si+1, ss, mid, qs, qe),
		getMaxUtil(2*si+2, mid+1, se, qs, qe)); 
}
 
int getMax(int qs = 0, int qe = n-1) { 
	return getMaxUtil(0, 0, n-1, qs, qe); 
}
 
int constructSTUtil(int si, int ss, int se) {
	if (ss == se) { 
		ST[si] = ss; 
		return ST[si]; 
	} 
	int mid = (ss + se)/2; 
	ST[si] = comp(constructSTUtil(si*2+1, ss, mid), 
				constructSTUtil(si*2+2, mid+1, se)); 
	return ST[si]; 
}
 
void constructST() { 
	constructSTUtil(0, 0, n-1); 
}
 
void solve(){
 
	cin>>n>>k;
	for (int i = 0; i < n; ++i){
		adj[i].clear();
	}
 
	for (int i = 0; i < n-1; ++i){
		int u, v; cin>>u>>v;
		u--; v--;
		adj[u].pb(v);
		adj[v].pb(u);
	}
 
	for (int node = 0; node < n; ++node){
		int lfCh = 0;
		for(int child : adj[node])
			lfCh += adj[child].size()==1;
 
		arr[node] = lfCh;
		deg[node] = adj[node].size();
	}
	constructST();
 
	int ans = 0;
	while(true){
		int mx = getMax();
		int del = arr[mx]/k;
		if(del == 0) break;
		update(mx, -del*k);
		deg[mx] -= del*k;
		int tk = del*k;
		for(int child : adj[mx]){
			if(deg[child] != 1) continue;
			deg[child] = 0;
			update(child, -1);
			tk--;
			if(tk==0) break;
		}
		if(deg[mx] == 1){
			for(int child : adj[mx]){
				if(deg[child] == 0) continue;
				update(child, 1);
			}
		}
		ans += del;
	}
	cout<<ans<<el;
}
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	#ifndef ONLINE_JUDGE 
		freopen("input.txt", "r", stdin); 
		freopen("output.txt", "w", stdout); 
	#endif
	int T=1, tc = 1;
	cin>>T; 
	while(T--){
		solve();
	}
	return 0; 
}