class BIT{
public :
	int n;
	vi f;
	BIT(int n){
		this->n = n;
		f.assign(n, 0);
	}

	int get(int pos){
		int res = 0;
		for (; pos >= 0; pos = (pos & (pos + 1)) - 1){
		    res += f[pos];
		}
		return res;
	}

	int get(int l, int r){
		if(l > r) return 0;
		return get(r) - get(l - 1);
	}

	void increase(int pos, int val){
		for (; pos < SZ(f); pos = (pos | (pos + 1))) {
			f[pos] += val;
		}
	}

	// (logn)^2;
	int operator[](int i){
		int l = -1, r = n;
		// invarients;
		// get(r) > i, get(l) <= i;
		while(l + 1 < r){
			int m = (l + r) >> 1;
			if(get(m) > i){
				r = m;
			}
			else{
				l = m;
			}
		}
		return r;
	}
};