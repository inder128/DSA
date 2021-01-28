struct edge{
    int u, v;
    int cap, flow = 0;
    edge(int u, int v, int cap) : u(u), v(v), cap(cap) {}
};
 
 
struct Dinic{
    vi lvl, ptr;
    vvi adj;
    vector <edge> edges;
    queue <int> Q;
    int n, m = 0;
    int s, t;
    const int inf = 1e9;
    
    Dinic(int n, int s, int t) : n(n), s(s), t(t){
        adj.resize(n);
        lvl.resize(n);
        ptr.resize(n);
    }
    void addEdge(int u, int v, int c){
        edges.emplace_back(u, v, c);
        edges.emplace_back(v, u, 0);
        adj[u].pb(m);
        adj[v].pb(m + 1);
        m += 2;
    }
    
    
    bool bfs(){
        while(!Q.empty()){
            int f = Q.front();
            Q.pop();
            for(auto it: adj[f]){
                if(lvl[edges[it].v] != -1 or edges[it].cap - edges[it].flow < 1){
                    continue;
                }
                lvl[edges[it].v] = lvl[f] + 1;
                Q.push(edges[it].v);
            }
        }
        return lvl[t] != -1;
    }
    
    
    int dfs(int u, int bneck){
        if(bneck == 0 or u == t){
            return bneck;
        }
        for(int& id = ptr[u]; id < adj[u].size(); id++){
            int it = adj[u][id];
            if(lvl[edges[it].v] != lvl[u] + 1 or edges[it].cap - edges[it].flow < 1){
                continue;
            }
            int f = dfs(edges[it].v, min(bneck, edges[it].cap - edges[it].flow));
            if(f == 0){
                continue;
            }
            edges[it].flow += f;
            edges[it ^ 1].flow -= f;
            return f;
        }
        return 0;
    }
    
    
    int flow(){
        int f = 0;
        while(true){
            lvl.assign(n, -1);
            lvl[s] = 0;
            Q.push(s);
            if(bfs() == false){
                break;
            }
            ptr.assign(n, 0);
            while(int bneck = dfs(s,inf)){
                f += bneck;
            }
        }
        return f;
    }
};