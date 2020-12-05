class suffixArray{
public:
	string str;
	int n;
	// posSuffs[i] -> position of suffix str[i..n - 1] in sortedSuffs;
	// sortedSuffs[i] -> suffix str[sortedSuffs[i]..n - 1] is lexicographically i'th suffix;
	// lcp[i] -> length of longest common prefix of str[sortedSuffs[i]..n - 1] and str[sortedSuffs[i + 1]..n - 1];
	vi posSuffs, sortedSuffs, lcp;
	sparseTable spt;

	suffixArray(string str_){
		str = str_ + " ";
		n = str.length();
		posSuffs.resize(n);
		sortedSuffs.resize(n);
		lcp.resize(n - 1);

		buildPosSuffs();
		buildSortedSuffs();
		buildLCP();
		spt.build(lcp);
	}

	void buildPosSuffs(){
		for(int i = 0; i < n; ++i){
			posSuffs[i] = str[i] - 32;
		}
		int k = 0;
		while((1 << k) < n){
			// k -> k + 1;
			vi ordInds(n), sortVal(n);
			for(int i = 0; i < n; ++i){
				ordInds[i] = i;
			 	sortVal[i] = posSuffs[(i + (1 << k)) % n];
			}
			countSort(ordInds, sortVal);
			for(int i = 0; i < n; ++i){
				sortVal[i] = posSuffs[ordInds[i]];
			}
			countSort(ordInds, sortVal);
			
			vi newPosSuffs(n);
			newPosSuffs[ordInds[0]] = 0;
			for(int i = 1; i < n; ++i){
				int lastSt = ordInds[i - 1], currSt = ordInds[i];
				if(posSuffs[lastSt] == posSuffs[currSt] and 
				   posSuffs[lastSt + (1 << k)] == posSuffs[currSt + (1 << k)]){
					newPosSuffs[currSt] = newPosSuffs[lastSt];
				}
				else{
					newPosSuffs[currSt] = newPosSuffs[lastSt] + 1;
				}
			}
			posSuffs = newPosSuffs;
			if(posSuffs[ordInds.back()] == n - 1) break;
			k++;
		}
	}

	void buildSortedSuffs(){
		for(int i = 0; i < n; ++i){
	   		sortedSuffs[posSuffs[i]] = i;
	   	}
	}

	void buildLCP(){
		int k = 0;
	   	for(int i = 0; i < n - 1; ++i){
	   		int posi = posSuffs[i];
	   		assert(posi > 0);

	   		// str[i .. n - 1] is at position posi in sortedSuffs array;
	   		int previ = sortedSuffs[posi - 1];
	   		
	   		while(str[i + k] == str[previ + k]) k++;

	   		lcp[posi - 1] = k;

	   		k = max(k - 1, 0ll);
	   	}
	}

	int commonPrefix(int i, int j){
		if(i == j) return n - 1 - i;
		if(posSuffs[i] > posSuffs[j]) swap(i, j);
		return spt.getVal(posSuffs[i], posSuffs[j] - 1);
	}

	int commonPrefix(int l1, int r1, int l2, int r2){
		int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
		return min({len1, len2, commonPrefix(l1, l2)});
	}


	void countSort(vi &val, vi ord){
		int sz = val.size();
		int mx = *max_element(rng(ord)) + 1;

		vi cnt(mx);
		for(int i = 0; i < sz; ++i){
			cnt[ord[i]]++;
		}
		vi preCnt(mx);
		for(int i = 1; i < mx; ++i){
			preCnt[i] = preCnt[i - 1] + cnt[i - 1];
		}

		vi newVal(sz);
		for(int i = 0; i < sz; ++i){
			newVal[preCnt[ord[i]]] = val[i];
			preCnt[ord[i]]++;
		}

		val = newVal;
	}
};