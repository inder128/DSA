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
		D = 30;
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

	int XOR(int xr, bool mn = true){
        int curr = 0, num = 0;

        for(int i = D - 1; i >= 0; --i){
            if(xr >> i & 1){
                if(trie[curr].c[mn] != -1){
                    curr = trie[curr].c[mn];
                    num += (1 << i) * mn;
                }
                else{
                    curr = trie[curr].c[!mn];
                    num += (1 << i) * (!mn);
                }
            }
            else{
                if(trie[curr].c[!mn] != -1){
                    curr = trie[curr].c[!mn];
                    num += (1 << i) * (!mn);
                }
                else{
                    curr = trie[curr].c[mn];
                    num += (1 << i) * mn;
                }
            }
        }

        return num ^ xr;
    }
};