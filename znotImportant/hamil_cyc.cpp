#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int n, source = 0;
stack <int> stk;

bool chk(bool vis[]){
    for (int i = 0; i < n; ++i)
        if(vis[i]==false) 
            return false;
    return true;
}

void print_stk(){
    stack <int> tmp_stk = stk;
    cout<<"1 ";
    while(!tmp_stk.empty()){
        cout<<tmp_stk.top()+1<<" ";
        tmp_stk.pop();
    }
    cout<<"\n"; 
}

void hamcyc(int curr, vector <int> adj[], bool vis[]){
    stk.push(curr);
    vis[curr]=true;
    for (int i = 0; i < adj[curr].size(); ++i){
        int child = adj[curr][i];
        if(!vis[child])
            hamcyc(child, adj, vis);
        if(child==source and chk(vis))
            return print_stk();
    }
    stk.pop();
    vis[curr]=false;
}

int main() {
    int m, x, y;
    cin>>n>>m;
    bool vis[n];
    memset(vis, false, sizeof(vis));
    vector<int> adj[n];
    for (int i = 0; i < m; ++i){
        cin>>x>>y;
        adj[x-1].push_back(y-1);
        adj[y-1].push_back(x-1);
    }
    hamcyc(0, adj, vis);
    return 0;
}