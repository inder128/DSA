#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define int long long
#define SZ(x) ((int)(x).size()) 
typedef vector<int> vi;
typedef pair<int, int> pi;

const int N = 2e5;
vector <pi> adj[N];

int32_t main(){
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; ++i){
        int u, v, w; cin >> u >> v >> w;
        u--, v--;
        adj[u].pb({v, w});
        adj[v].pb({u, w});
    }
    
    vi cost(n, 1e18);
    priority_queue <pi, vector <pi>, greater <>> PQ;
    PQ.push({cost[0] = 0, 0});

    while(SZ(PQ)){
        auto [wt, node] = PQ.top(); PQ.pop();
        if(wt > cost[node]){
            continue;
        }
        for(auto [child, w] : adj[node]){
            if(cost[child] > cost[node] + w){
                cost[child] = cost[node] + w;
                PQ.push({cost[child], child});
            }
        }
    }

    for(int i = 0; i < n; ++i){
        cout << cost[i] << " ";
    }
    cout << endl;
    return 0;
}