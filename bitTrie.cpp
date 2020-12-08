struct node{
	int c[2];
};

class BitTrie{
public :
	vector <node> trie;
	int D;
	BitTrie(){
		// numbers should be less that (2 ^ D);
		// size of trie containing all elements less than (2 ^ D) will be (2 ^ (D + 1) - 1);
		D = 19;
		trie.pb({{-1, -1}});
	}

	void insert(int k){
		int curr = 0;
		for(int i = D - 1; i >= 0; --i){
			if(trie[curr].c[k >> i & 1] == -1){
				trie[curr].c[k >> i & 1] = SZ(trie);
				trie.pb({{-1, -1}});
			}
			curr = trie[curr].c[k >> i & 1];
		}
	}

	int minXOR(int xr){
		int curr = 0, num = 0;

		for(int i = D - 1; i >= 0; --i){
			if(xr >> i & 1){
				if(trie[curr].c[1] != -1){
					curr = trie[curr].c[1];
					num += (1 << i);
				}
				else{
					curr = trie[curr].c[0];
				}
			}
			else{
				if(trie[curr].c[0] != -1){
					curr = trie[curr].c[0];
				}
				else{
					curr = trie[curr].c[1];
					num += (1 << i);
				}
			}
		}

		return num ^ xr;
	}
};