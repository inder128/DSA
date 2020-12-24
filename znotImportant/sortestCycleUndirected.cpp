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

// codeforces Question link :-
// https://codeforces.com/contest/1206/problem/D

int solve(){
	ll n; cin>>n;
	vector <ll> a;
	for (int i = 0; i < n; ++i){
		ll x; cin>>x; if(x) a.pb(x);
	}
	n = a.size();
	if(n > 120) return 3;

	vi adj[n];
	// for floyd warshall
	vector <vi> SP(n, vi(n, INT_MAX/2));
	vector <vb> EG(n, vb(n));
	for (int i = 0; i < n; ++i){
		for (int j = i+1; j < n; ++j){
			if(!(a[i]&a[j])) continue;
			adj[i].pb(j); adj[j].pb(i);
			SP[i][j] = SP[j][i] = 1;
			EG[i][j] = EG[j][i] = true;
		}
	} 
	
	int ans = INT_MAX;
	for (int i = 0; i < n; ++i){
		vi dist(n, INT_MAX), par(n, -1);
		queue <int> q; q.push(i);
		dist[i] = 0;
		while(!q.empty()){
			int node = q.front(); q.pop();
			for(int child : adj[node]){
				if(child==par[node]) continue;
				if(dist[child]==INT_MAX){
					par[child] = node;
					dist[child] = dist[node] + 1;
					q.push(child);
				}
				else ans = min(ans, dist[child]+dist[node]+1);
			}
		}
	}

	// floyd warshall method :-
	int ans2 = 1000;
	for (int m = 0; m < n; ++m){
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				if(i==m or m==j or j==i) continue;
				if(EG[i][m] and EG[m][j]) 
					ans2 = min(ans2, SP[i][j]+2);
				if(SP[i][m] + SP[m][j] < SP[i][j])
					SP[i][j] = SP[i][m] + SP[m][j];
			}
		}
	}
	return (ans2==1000 ? -1 : ans2);
	
	return (ans==INT_MAX ? -1 : ans);
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
	while(T--){
		cout<<solve()<<el;
	}
	return 0; 
}