#include <bits/stdc++.h>
using namespace std;

#define deb(x) cout<<#x<<"="<<x<<endl
#define deb2(x,y) cout<<#x<<"="<<x<<", "<<#y<<"="<<y<<endl
#define deb3(x,y,z) cout<<#x<<"="<<x<<", "<<#y<<"="<<y<<", "<<#z<<"="<<z<<endl
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

// codeforces question link;
// https://codeforces.com/contest/1179/problem/C

const int N = 1e6;
vi ST(3*N), lazy(3*N);
int n = N;
vector <pi> rg(3*N);

void increase(int si, int ss, int se, int inc){
	lazy[si] += inc;
	ST[si] += inc;
}

void shift(int si, int ss, int se){
	int mid = (ss+se)/2;
	increase(si*2 + 1, ss, mid, lazy[si]);
	increase(si*2 + 2, mid+1, se, lazy[si]);
	lazy[si] = 0;
}

void increaseUtil(int si, int ss, int se, int qs, int qe, int inc){
	if (se < qs || ss > qe) return;

	if (qs <= ss && qe >= se) return increase(si, ss, se, inc); 

	shift(si, ss, se);
	int mid = (ss+se)/2;
	increaseUtil(2*si + 1, ss, mid, qs, qe, inc);
	increaseUtil(2*si + 2, mid+1, se, qs, qe, inc);
	ST[si] = max(ST[si*2 + 1], ST[si*2 + 2]);
}

void increase(int qe, int inc){
	return increaseUtil(0, 0, n-1, 0, qe, inc);
}

int getMaxUtil(int si, int ss, int se) { 
	if(ss == se) return ss;

	shift(si, ss, se);
	int mid = (ss + se)/2;

	if(ST[2*si + 2] > 0) 
		return getMaxUtil(2*si + 2, mid+1, se);

	return getMaxUtil(2*si + 1, ss, mid);
}

int get(){
	return getMaxUtil(0, 0, n-1);
}

void con(int si = 0, int ss = 0, int se = n-1){
	rg[si] = {ss, se};

	if(ss == se) return;

	int mid = (ss + se)/2;


	con(2*si + 1, ss, mid);
	con(2*si + 2, mid + 1, se);
}

void show(){
	for (int i = 0; i < 30; ++i){
		deb3(ST[i], rg[i].F, rg[i].S);
	}
}

void solve(){
	// con();

	int nn, m; cin>>nn>>m;
	vi dish(nn), pupil(m);
	for(int &i : dish){
		cin>>i; i--;
		increase(i, 1);
	}
	for(int &i : pupil){
		cin>>i; i--;
		increase(i, -1);
	}
	int q; cin>>q;
	while(q--){
		int op; cin>>op;
		if(op==1){
			int i, x; cin>>i>>x;
			i--; x--;
			increase(dish[i], -1);
			dish[i] = x;
			increase(dish[i], 1);
		}else{
			int i, x; cin>>i>>x;
			i--; x--;
			increase(pupil[i], 1);
			pupil[i] = x;
			increase(pupil[i], -1);
		}
		// show();
		if(ST[0] <= 0) cout<<"-1\n";
		else cout<<get()+1<<el;
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





const int N = 1e6;
vi ST(3*N), lazy(3*N);
vi arr(N);
int n = N;

void increase(int si, int ss, int se, int inc){
	lazy[si] += inc;
	ST[si] += inc;
}

void shift(int si, int ss, int se){
	int mid = (ss+se)/2;
	increase(si*2 + 1, ss, mid, lazy[si]);
	increase(si*2 + 2, mid+1, se, lazy[si]);
	lazy[si] = 0;
}

void increaseUtil(int si, int ss, int se, int qs, int qe, int inc){
	if (se < qs || ss > qe) return;

	if (qs <= ss && qe >= se) return increase(si, ss, se, inc); 

	shift(si, ss, se);
	int mid = (ss+se)/2;
	increaseUtil(2*si + 1, ss, mid, qs, qe, inc);
	increaseUtil(2*si + 2, mid+1, se, qs, qe, inc);
	ST[si] = min(ST[si*2 + 1], ST[si*2 + 2]);
}

void increase(int qs, int qe, int inc){
	return increaseUtil(0, 0, n-1, qs, qe, inc);
}

int getMinUtil(int si, int ss, int se) { 
	if(ss == se) return ST[ss];

	shift(si, ss, se);
	int mid = (ss + se)/2;

	return min(getMinUtil(2*si + 1, ss, mid), getMinUtil(2*si + 2, mid + 1, se));
}

int get(){
	return getMinUtil(0, 0, n-1);
}

int constructSTUtil(int si, int ss, int se) {
	if (ss == se) { 
		ST[si] = arr[ss]; 
		return ST[si]; 
	} 
	int mid = (ss + se)/2; 
	ST[si] = min(constructSTUtil(si*2+1, ss, mid), 
				constructSTUtil(si*2+2, mid+1, se)); 
	return ST[si]; 
}

void constructST() { 
	constructSTUtil(0, 0, n-1); 
}