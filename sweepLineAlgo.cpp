#include <bits/stdc++.h>
using namespace std;
 
#define deb(x) cout<<#x<<"="<<x<<endl
#define deb2(x,y) cout<<#x<<"="<<x<<", "<<#y<<"="<<y<<endl
#define deb3(x,y,z) cout<<#x<<"="<<x<<", "<<#y<<"="<<y<<", "<<#z<<"="<<z<<endl
#define in(x,y) memset(x,y,sizeof(x))
#define rng(x) x.begin(),x.end()
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define el endl
 
typedef long long ll;
typedef pair<int,int> pi;
typedef vector<int> vi;
typedef vector<bool> vb;

// codeforces question link :- 
// https://codeforces.com/contest/1278/problem/D

struct pnt{
	int x;
	int i;
	bool isEnd;
};

bool comp(pnt p1, pnt p2){
	// p1.x will be different from p2.x;
	return p1.x < p2.x;
}

void dfs(int node, vi adj[], vector<bool> &isReachable){
	isReachable[node] = true;
	for(int child : adj[node]){
		if(isReachable[child]) continue;
		dfs(child, adj, isReachable);
	}
}
 
bool solve(){	
	int n; cin>>n;
	vi adj[n]; // adjency list of graph formed;
	vector <pnt> pointArr;
	vector <pi> segs(n); // contains segments;
	for (int i = 0; i < n; ++i){
		cin>>segs[i].F>>segs[i].S;
		pointArr.pb({segs[i].F, i, false});
		pointArr.pb({segs[i].S, i, true});
	}
	// all pointArr[i].x are distinct (give in question);
	sort(rng(pointArr), comp);

	// SWEEP LINE ALGORITHM;
	// maintains open log segments at a given coordinate;
	// sorted acc to their ending value;
	set <pi> openSeg; 

	int edgeCnt = 0;

	// all operations in it will run atmost 2*n (n+n) times; 
	for(auto pt : pointArr){
		// if some segment ends, then removing it from openSeg;
		if(pt.isEnd){ 
			openSeg.erase(mp(pt.x, pt.i));
			continue;
		}
		// pt.x is starting point of segment at pt.i
		// segment which are present in openSeg have (ending point > pt.x) and (starting point < pt.x);
		int u = pt.i;
		int r = segs[u].S; // r is ending point of segment at u;

		// all operations in it will run atmost n times, because edgeCnt is incrementing;
		for (auto oSeg : openSeg){
			// oSeg.F is ending point of segment at oSeg.S;
			// points in openSeg are sorted acc to their ending value;
			// if below condition becomes true then present seg will lie inside all other segs in set, so there will be no edge between them, that the reason for break statement;
			if(oSeg.F > r) break;

			// there will be a edje between oseg and present segment;
			// ending point of oSeg is less than ending point of present seg; 
			// starting point of oSeg is less than starting point of present seg;

			int v = oSeg.S;

			// incrementing edje count;
			edgeCnt++;
			// undirected graph;
			adj[u].pb(v);
			adj[v].pb(u);

			if(edgeCnt >= n) break;
		}
		// inserting ending point and index of present seg;
		openSeg.insert(mp(r, u));
	}

	// for a graph to be a tree, edges must be n-1 and all node must be reachable from any node (i.e there exist a path from every pair of nodes);
	if(edgeCnt != n-1)
		return false;

	// So we will now check if all nodes are reachable from node 0;
	vector <bool> isReachable(n, false);
	dfs(0, adj, isReachable);

	if(count(rng(isReachable), false))
		return false;
	return true;
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
		if(solve())
			cout<<"YES\n";
		else
			cout<<"NO\n";
	return 0; 
}