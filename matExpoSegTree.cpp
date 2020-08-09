#include <bits/stdc++.h>
using namespace std;
 
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {
    return os << "(" << P.first << "," << P.second << ")"; }
template<class T> ostream& operator<<(ostream &os, vector<T> V) {
    os << "[ "; for(auto v : V) os << v << " "; return os << "]"; }
template<class T> ostream& operator<<(ostream &os, set<T> S){
    os << "{ "; for(auto s:S) os<<s<<" "; return os<<"}"; }
template<class T> ostream& operator<<(ostream &os, multiset<T> S){
    os << "{ "; for(auto s:S) os<<s<<" "; return os<<"}"; }
template<class L, class R> ostream& operator<<(ostream &os, map<L,R> M) {
    os << "{ "; for(auto m:M) os<<"("<<m.F<<":"<<m.S<<") "; return os<<"}"; }
    #define db(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << '\n'; }
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
	const char* comma = strchr(names + 1, ',');
	cout.write(names, comma - names) << " : " << arg1 << " |"; __f(comma + 1, args...); }
#define rng(x) x.begin(), x.end()
#define pb push_back
#define F first
#define S second
#define el '\n'
 
typedef long long ll;
typedef pair<int,int> pi;
typedef pair<ll,ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<bool> vb;
 
/*-----------------------------Code begins----------------------------------*/

// codeforces question link
// https://codeforces.com/contest/1252/problem/K

typedef pair<pl,pl> ppl;
ppl am = {{1, 0}, {1, 1}};
ppl bm = {{1, 1}, {0, 1}};
ppl id = {{1, 0}, {0, 1}};
const int N = 1e5;
vector <ppl> ST(3*N);
vb lazy(3*N), arr(N);
int n = N;
const int mod = 1e9 + 7;

void mul(ppl &a, ppl b){
	ppl c = {{0, 0}, {0, 0}};
	c.F.F = (a.F.F*b.F.F + a.F.S*b.S.F) % mod;
	c.F.S = (a.F.F*b.F.S + a.F.S*b.S.S) % mod;
	c.S.F = (a.S.F*b.F.F + a.S.S*b.S.F) % mod;
	c.S.S = (a.S.F*b.F.S + a.S.S*b.S.S) % mod;
	a = c;
}

void update(int si, int ss, int se){
	lazy[si] = !lazy[si];
	ppl &p = ST[si];
	swap(p.F.F, p.S.S);
	swap(p.F.S, p.S.F);
}

void shift(int si, int ss, int se){
	if(!lazy[si]) return;
	int mid = (ss+se)/2;
	update(si*2+1, ss, mid);
	update(si*2+2, mid+1, se);
	lazy[si] = false;
}

void flipUtil(int si, int ss, int se, int qs, int qe){
	if (se < qs || ss > qe) return;

	if (qs <= ss && qe >= se) return update(si, ss, se); 

	shift(si, ss, se);
	int mid = (ss+se)/2;
	flipUtil(2*si+1, ss, mid, qs, qe);
	flipUtil(2*si+2, mid+1, se, qs, qe);

	ST[si] = id;
	mul(ST[si], ST[2*si+1]);  
	mul(ST[si], ST[2*si+2]); 
}

void flip(int qs, int qe){
	return flipUtil(0, 0, n-1, qs, qe);
}

ppl getSumUtil(int si, int ss, int se, int qs, int qe) { 
	if (se < qs || ss > qe) return {{1, 0}, {0, 1}}; 
	
	if (qs <= ss && qe >= se) return ST[si]; 

	shift(si, ss, se);
	int mid = (ss + se)/2;
	ppl ans = id;
	mul(ans, getSumUtil(2*si+1, ss, mid, qs, qe)); 
	mul(ans, getSumUtil(2*si+2, mid+1, se, qs, qe)); 
	return ans;
}

ppl getSum(int qs, int qe) { 
	return getSumUtil(0, 0, n-1, qs, qe); 
}

ppl constructSTUtil(int si, int ss, int se) {
	if (ss == se) { 
		ST[si] = (arr[ss] ? am : bm);
		return ST[si];
	} 
	int mid = (ss + se)/2; 
	ST[si] = id;
	mul(ST[si], constructSTUtil(si*2+1, ss, mid)); 
	mul(ST[si],	constructSTUtil(si*2+2, mid+1, se)); 
	return ST[si]; 
}

void constructST() { 
	constructSTUtil(0, 0, n-1); 
}

void solve(){
	int nn, q; cin>>nn>>q;
	string str; cin>>str;
	for (int i = 0; i < nn; ++i){
		arr[i] = (str[i]=='A');
	}
	constructST();
	
	while(q--){
		int op; cin>>op;
		if(op == 1){
			int l, r; cin>>l>>r;
			l--; r--;
			flip(l, r);
		}
		else{
			ll l, r, a, b; cin>>l>>r>>a>>b;
			l--; r--;
			ppl mat = getSum(l, r);
			cout<<(a*mat.F.F + b*mat.S.F) % mod<<" ";
			cout<<(a*mat.F.S + b*mat.S.S) % mod<<el;
		}
	}
}
 
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	#ifndef ONLINE_JUDGE 
		freopen("secret/robot_1_4.in", "r", stdin); 
		freopen("output.txt", "w", stdout); 
	#endif
	int T=1, tc = 1;
	// cin>>T; 
	while(T--){
		solve();
	}
	return 0; 
}