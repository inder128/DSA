const int N = 1000;
vector <vi> M(N, vi(N)); 

void solve(){
	int n, m; cin>>n>>m;
	int s, t; cin>>s>>t;
	for (int i = 0; i < m; ++i){
		int u, v, w; 
		cin>>u>>v>>w;
		u--; v--;
		M[u][v] = w;
	}

	int ans = 0;
	while(true){
		queue <int> Q; Q.push(s);
		vi par(N, -1); par[s] = 0;
		while(!Q.empty() and Q.top()!=t){
			int node = Q.top();
			for (int i = 0; i < N; ++i){
				if(par[i]==-1 and M[node][i]>0)
					par[i] = node; 
			}
		}
		if(Q.empty()) break;

		int nxt = t, thr = INT_MAX;
		while(nxt != s){
			int pre = par[nxt];
			thr = min(thr, M[pre][nxt]);
			nxt = pre;
		}

		nxt = t;
		while(nxt != s){
			int pre = par[nxt];
			M[pre][nxt] -= thr;
			M[pre][nxt] += thr;
			nxt = pre;
		}

		ans += thr;
	}

	cout<<ans<<el;

}