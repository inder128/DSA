class DSU{ 
public: 
    vi par;
    vector <vi> nodes;
    int n;

    DSU(int n){ 
        this->n = n; 
        par.resize(n);
        nodes.resize(n);
        for (int i = 0; i < n; ++i){
            par[i] = i;
            nodes[i].pb(i);
        }
    }

    int size(int u){
        return nodes[u].size();
    }

    bool unite(int u, int v){
        u = par[u], v = par[v];
        if(u == v) return false;

        if(size(u) > size(v)) swap(u, v);
        
        while(nodes[u].size()){
            int w = nodes[u].back(); nodes[u].pop_back();
            nodes[v].pb(w);
            par[w] = v;
        }

        return true;
    }
};