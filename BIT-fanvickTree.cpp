class BIT{
	int n;
	vi f;
	BIT(int n){
		this->n = n;
		f.assign(n);
	}

	int get(int pos){
		int res = 0;
		for (; pos >= 0; pos = (pos & (pos + 1)) - 1){
		    res += f[pos];
		}
		return res;
	}

	void update(int pos, int val){
		for (; pos < int(f.size()); pos = (pos | (pos + 1))) {
			f[pos] += val;
		}
	}
}