#include <bits/stdc++.h>
using namespace std;
 
// CodeForces question link :-
// https://codeforces.com/contest/1243/problem/D

set <int> V;
set <pair<int, int> > E;

// void dfs(int node){
// 	V.erase(node);
// 	int child=0;
// 	// returns imidiate next greater element to child;
// 	while(V.upper_bound(child)!=V.end()){
// 		child = *V.upper_bound(child);
// 		if(!E.count({node, child}))
// 			dfs(child);
// 	}
// }

// Another way :- 
void dfs(int node){
	V.erase(node);
	// Simply iteration will not work bbecause set it dynamically changing inside for loop;
	for(auto it = V.begin(); it != V.end(); it = V.upper_bound(*it))
		if(!E.count({node, *it})) dfs(*it);
}

int main(){
	int n, m; cin>>n>>m;

	// initialisation of set should be in front othewise error will come;
	// see it :- https://codeforces.com/contest/1243/my
	for (int i = 1; i <= n; ++i)
		V.insert(i);
	
	for (int i = 0; i < m; ++i){
		int u, v; cin>>u>>v;
		E.insert({u, v});
		E.insert({v, u});
	}

	int cmp = 0;
	for (int i = 1; i <= n; ++i)
		if(V.count(i)) dfs(i), cmp++;	

	cout<<cmp-1<<endl;
	return 0;
}
