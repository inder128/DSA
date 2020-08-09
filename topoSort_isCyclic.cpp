#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<bool> vb;

// GFG QUESTION LINK :-
// https://practice.geeksforgeeks.org/problems/topological-sort/1

// Directed Unconnected Graph;
// checked[child]==true -> we have explored all childs of i;
// so there is no path from child to t we don't need to check it again;

bool isCyc(int t, vi adj[], vb &vis, vb &checked, stack <int> &stk){
    stk.push(t); vis[t] = true;
    for (int child : adj[t]){
        if(checked[child]==true) 
            continue;
        if(vis[child]==true) 
            return true;
        if(isCyc(child, adj, vis, checked, stk))
            return true;
    }
    checked[node] = true;
    stk.pop(); vis[t]=false;
    return false;
}

bool isCyclic(int V, vector<int> adj[]){
    vb vis(V, false);
    vb checked(V, false);
    stack <int> stk;
    for (int t = 0; t < V; ++t){
        if(checked[t]==true) continue;     
        if(isCyc(t, adj, vis, checked, stk))
            return true;        
    }
    return false;
}


// Method 2 for checking cycle in graph:- (better method)
// state[i] == 'w' if node i is still to process; 
//             'g' if node i is in process; 
//             'b' if node i has been processed;
// diring bfs if we encounter a node which has state='g', then it means 
// that node is a part of cycle;


bool isCyc2(int t, vi adj[], vector <char> &state){
    state[t] = 'g';
    for (int child : adj[t]){
        if(state[child]=='b')
            continue;
        if(state[child]=='g') 
            return true;
        if(isCyc2(child, adj, state))
            return true;
    }
    state[t] = 'b';
    return false;
}

bool isCyclic2(int V, vector<int> adj[]){
    vector <char> state(V, 'w');
    for (int t = 0; t < V; ++t){
        if(state[t]=='b')
            continue;
        if(isCyc2(t, adj, state))
            return true;
    }
    return false;
}


void toporder(int t, vi adj[], vb &vis, stack <int> &stk){
    for(int child : adj[t]){
        if(vis[child]==true) continue;
        toporder(child, adj, vis, stk);
    }
    vis[t]=true;
    stk.push(t);
}


int* topoSort(int V, vi adj[]) {
    // checking if given graph is cyclic, if true then no 
    // topogical sort is possible;
    // if(isCyclic1(V, adj))  method 1
    if(isCyclic2(V, adj))  // method 2
        return NULL;

    int *a = new int[V];
    vb vis(V, false);
    stack <int> stk;

    for(int i=0; i<V; i++){
        if(vis[i]==true) continue;
        toporder(i, adj, vis, stk);
    }
    for(int i=0; i<V; i++){
        a[i] = stk.top();
        stk.pop();
    }
    return a;
}





bool check(int V, int* res, vector<int> adj[]) {
    bool flag = true;
    for (int i = 0; i < V && flag; i++) {
        int n = adj[res[i]].size();
        for (auto j : adj[res[i]]) {
            for (int k = i + 1; k < V; k++) {
                if (res[k] == j) n--;
            }
        }
        if (n != 0) flag = false;
    }
    if (flag == false) return 0;
    return 1;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, E;
        cin >> E >> N;
        int u, v;

        vector<int> adj[N];

        for (int i = 0; i < E; i++) {
            cin >> u >> v;
            adj[u].push_back(v);
        }

        int* res = topoSort(N, adj);

        cout << check(N, res, adj) << endl;
    }
}