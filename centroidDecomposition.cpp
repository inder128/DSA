#include <bits/stdc++.h>
using namespace std;
typedef vector <int> vi; 

const int N = 1e5, logN = 40;
unordered_set <int> adj[N];
vi subtreeSize(N);

// centroid tree data structure;
vi papa(N), level(N);
vvi dist(N, vi(logN));
// dist[i][l] -> distance of node(i) from its ancestor at l'th level in centroid tree;
// every node will have a unique ancestor at some specific level;

// problem specific data structure;
// xyz;

void decompose(int root = 0, int par = -1){
    // genric code;
    function <int(int, int)> getSize = [&](int node, int par){
        subtreeSize[node] = 1;
        for(auto child : adj[node]){
            if(child == par) continue;
            subtreeSize[node] += getSize(child, node);
        }
        return subtreeSize[node];
    };
    int totalSize = getSize(root, -1);
    function <int(int, int)> findCentroid = [&](int node, int par){
        for(auto child : adj[node]){
            if(child == par) continue;
            if(subtreeSize[child] > totalSize / 2){
                return findCentroid(child, node);
            }
        }
        return node;
    };
    int centroid = findCentroid(root, -1);

    // problem specific code;
    // xyz;

    // genric code;
    for(auto newRoot : adj[centroid]){
        adj[newRoot].erase(centroid);
        decompose(newRoot, centroid);
    }
    adj[centroid].clear();
}

int main(){
    int n; cin>>n;
    for(int i = 0; i < n - 1; ++i){
        int u, v; cin>>u>>v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    decompose();

    // problem specific code;
    // xyz;
    return 0;
}