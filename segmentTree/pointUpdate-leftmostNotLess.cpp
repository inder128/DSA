#define lsi 2*si + 1
#define rsi 2*si + 2
class segmentTree{
public :
	int size, n, neutral = LLONG_MIN;
	vi ST;
	segmentTree(int _n){
		n = _n;
		size = 1;
		while(size < n) size <<= 1;
		ST.assign(2 * size, neutral);
	}


	inline int getMid(int &sl, int &sr){
		return (sl + sr) >> 1;
	}
	void printUtil(int si, int sl, int sr){
		cout<<si<<" : "<<sl<<" - "<<sr<<" : "<<ST[si]<<el;

		if(sl == sr) return;

		int mid = getMid(sl, sr);
		printUtil(lsi, sl, mid);
		printUtil(rsi, mid + 1, sr);
	}
	void print(){
		return printUtil(0, 0, n - 1);
	}


	void updateUtil(int si, int sl, int sr, int i, int newVal){
		if(sl == sr){
			ST[si] = newVal;
			return;
		}

		int mid = getMid(sl, sr);
		if(i <= mid)
			updateUtil(lsi, sl, mid, i, newVal);
		else
			updateUtil(rsi, mid + 1, sr, i, newVal);

		ST[si] = max(ST[lsi], ST[rsi]);
	}
	void update(int i, int newVal){
		return updateUtil(0, 0, n - 1, i, newVal);
	}


	int getUtil(int si, int sl, int sr, int val){
		if(ST[si] < val) return -1;

		if(sl == sr) return sl;

		int mid = getMid(sl, sr);
		int ans = getUtil(lsi, sl, mid, val);
		if(ans == -1){
			ans = getUtil(rsi, mid + 1, sr, val);
		}
		return ans;
	}
	int getLeftmostNotLess(int val){
		return getUtil(0, 0, n - 1, val);
	}
};