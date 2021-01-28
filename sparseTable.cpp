class sparseTable{
public:
	vvi spt;
	vi arr, numLog;
	int k, n;

	sparseTable(vi &arr_){
		build(arr_);
	}

	sparseTable(){
	}

	void build(vi &arr_){
		arr = arr_;
		n = arr.size();

		numLog.resize(n + 1);
		numLog[1] = 0;
		for(int i = 2; i <= n; ++i){
			numLog[i] = numLog[i / 2] + 1;
		}

		k = numLog[n];

		spt = vvi(k + 1, vi(n));
		iota(rng(spt[0]), 0);
		for(int b = 1; b <= k; ++b){
			for(int i = 0, j = i + (1 << b) - 1; j < n; ++i, ++j){
				int s1 = spt[b - 1][i], s2 = spt[b - 1][i + (1 << b) / 2];
				spt[b][i] = compare(s1, s2);
			}
		}
	}

	int compare(int s1, int s2){
		return (arr[s1] < arr[s2] ? s1 : s2);
	}

	int get(int l, int r){
		int lg = numLog[r - l + 1];
		return compare(spt[lg][l], spt[lg][r - (1 << lg) + 1]);
	}

	int getVal(int l, int r){
		return arr[get(l, r)];
	}
};