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

const int N = 2e5;
vi ST(N), arr(N), lazy(N);
int n;

void update(int si, int ss, int se, int inc){//	increase all members in this interval by x
	lazy[si] += inc;
	ST[si] += (se - ss + 1) * inc;
}

void shift(int si, int ss, int se){//pass update information to the children
	int mid = (ss+se)/2;
	update(si*2+1, ss, mid, lazy[si]);
	update(si*2+2, mid+1, se, lazy[si]);
	lazy[si] = 0;// passing is done
}

void increaseUtil(int si, int ss, int se, int qs, int qe, int inc){
	if (se < qs || ss > qe) return;

	if (qs <= ss && qe >= se) return update(si, ss, se, inc); 

	shift(si, ss, se);
	int mid = (ss+se)/2;
	increaseUtil(2*si+1, ss, mid, qs, qe, inc);
	increaseUtil(2*si+2, mid+1, se, qs, qe, inc);
	ST[si] = ST[si*2+1] + ST[si*2+2];
}

void increase(int qs, int qe, int inc){
	return increaseUtil(0, 0, n-1, qs, qe, inc);
}

int getSumUtil(int si, int ss, int se, int qs, int qe) { 
	if (se < qs || ss > qe) return 0; 
	
	if (qs <= ss && qe >= se) return ST[si]; 

	shift(si, ss, se);
	int mid = (ss + se)/2;
	return getSumUtil(2*si+1, ss, mid, qs, qe) + 
		getSumUtil(2*si+2, mid+1, se, qs, qe); 
}

int getSum(int qs, int qe) { 
	return getSumUtil(0, 0, n-1, qs, qe); 
}

int constructSTUtil(int si, int ss, int se) {
	// rp[si] = {ss, se};
	if (ss == se) { 
		ST[si] = arr[ss]; 
		return ST[si]; 
	} 
	int mid = (ss + se)/2; 
	ST[si] = constructSTUtil(si*2+1, ss, mid) + 
			constructSTUtil(si*2+2, mid+1, se); 
	return ST[si]; 
}

void constructST() { 
	constructSTUtil(0, 0, n-1); 
}

void showST(){
	for (int i = 0; i <= 12; ++i){
		cout<<rp[i].F<<" "<<rp[i].S<<" : "<<ST[i]<<el;
	}
}
 
void solve(){
	cin>>n;
	for (int i = 0; i < n; ++i){
		cin>>arr[i];
	}
	constructST(); 

	int q; cin>>q;
	while(q--){
		int t; cin>>t;
		if(t==1){
			// range sum;
			int l, r; cin>>l>>r;
			cout<<getSum(l, r)<<el;
		}else{
			// range updates;
			int l, r, inc; cin>>l>>r>>inc;
			increase(l, r, inc);
		}
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

