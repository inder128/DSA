#include <bits/stdc++.h>
using namespace std;

#define deb(x) cout<<#x<<"="<<x<<endl
#define deb2(x,y) cout<<#x<<"="<<x<<", "<<#y<<"="<<y<<endl
#define deb3(x,y,z) cout<<#x<<"="<<x<<", "<<#y<<"="<<y<<", "<<#z<<"="<<z<<endl
#define rng(x) x.begin(), x.end()
#define pb push_back
#define F first
#define S second
#define el endl

typedef long long ll;
typedef pair<int,int> pi;
typedef pair<ll,ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<bool> vb;

// codeforces question link :-
// https://codeforces.com/contest/1181/problem/D;

const int N = 2e6;
vector<int> seg[N]; 
  
// Function to build the merge sort 
// segment tree of indices 
void build(int ci, int st, int end, 
           pair<int, int>* B) 
{ 
    if (st == end) { 
        // Using second property of B 
        seg[ci].push_back(B[st].second); 
        return; 
    } 
  
    int mid = (st + end) / 2; 
    build(2 * ci + 1, st, mid, B); 
    build(2 * ci + 2, mid + 1, end, B); 
  
    // Inbuilt merge function 
    // this takes two sorted arrays and merge 
    // them into a sorted array 
    merge(seg[2 * ci + 1].begin(), seg[2 * ci + 1].end(), 
          seg[2 * ci + 2].begin(), seg[2 * ci + 2].end(), 
          back_inserter(seg[ci])); 
} 
  
// Function to return the index of 
// kth smallest element in range [l, r] 
int query(int ci, int st, int end, 
          int l, int r, int k) 
{ 
    // Base case 
    if (st == end) 
        return seg[ci][0]; 
  
    // Finding value of 'p' as described in article 
    // seg[2*ci+1] is left node of seg[ci] 
    int p = upper_bound(seg[2 * ci + 1].begin(), 
                        seg[2 * ci + 1].end(), r) 
            - lower_bound(seg[2 * ci + 1].begin(), 
                          seg[2 * ci + 1].end(), l); 
  
    int mid = (st + end) / 2; 
    if (p >= k) 
        return query(2 * ci + 1, st, mid, l, r, k); 
    else
        return query(2 * ci + 2, mid + 1, end, l, r, k - p); 
} 

void solve(){
	int n, m, q; cin>>n>>m>>q;
	vector <pi> cnt(m);
	for (int i = 0; i < m; ++i)
		cnt[i].S = i;
	for (int i = 0; i < n; ++i){
		int t; cin>>t; t--;
		cnt[t].F++;
	}
	sort(rng(cnt));

	pair<int, int> B[m]; 
    for (int i = 0; i < m; i++)
        B[i] = { cnt[i].S, i }; 
    sort(B, B + m);
    build(0, 0, m - 1, B); 
    

	vector <pl> req({{1, 1}});
	ll sum = cnt[0].F;
	for (ll i = 1; i < m; ++i){
		if(cnt[i].F == cnt[i-1].F)
			req.back().S++;
		else
			req.pb({i*cnt[i].F - sum + 1, i+1});
		sum += cnt[i].F;
	}

	for (int i = 0; i < q; ++i){
		ll h; cin>>h; h -= n; 
		int l = 0, r = req.size()-1;
		while(l < r){
			int m = (l + r + 1)/2;
			if(req[m].F > h) r = m-1;
			else l = m;
		}
		h -= req[l].F - 1;
		int b = req[l].S;
		int k = h%b; if(!k) k = b;
		cout<<cnt[query(0, 0, m-1, 0, b-1, k)].S+1<<el;
	}

}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	#ifndef ONLINE_JUDGE 
		freopen("input.txt", "r", stdin); 
		freopen("output.txt", "w", stdout); 
	#endif
	int T=1, tc = 1;
	// cin>>T; 
	while(T--){
		solve();
	}
	return 0; 
}