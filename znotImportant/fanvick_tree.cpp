#include <bits/stdc++.h>
using namespace std;

#define deb(x) cout<<#x<<"="<<x<<endl
#define deb2(x,y) cout<<#x<<"="<<x<<", "<<#y<<"="<<y<<endl
#define deb3(x,y,z) cout<<#x<<"="<<x<<", "<<#y<<"="<<y<<", "<<#z<<"="<<z <<endl
typedef long long ll; typedef vector<ll> vl;

// FANVICK TREE (Binary Index Tree)
// It performs same operations as segment tree but more efficiently;
// For easy implemantation of fanvick tree, 
// we need to predefine the size of array or vector;

// Codeforces Question Link :-
// https://codeforces.com/problemset/problem/1311/F

// below function returns sum of values upto index pos(included);
ll get(vector<ll> &f, int pos) {
	ll res = 0;
	for (; pos >= 0; pos = (pos & (pos + 1)) - 1){
	    res += f[pos];
	}
	return res;
}

// below function increase the value in vector f at index
// pos by val and all its ansestors in the tree;
// Can also be used to put values initially;
void update(vector<ll> &f, int pos, int val) {
	for (; pos < int(f.size()); pos = (pos | (pos + 1))) {
		f[pos] += val;
	}
}


// ll get(int pos) {
// 	ll res = 0;
// 	for (; pos >= 0; pos = (pos & (pos + 1)) - 1)
// 	    res += f[pos];
// 	return res;
// }
// void update(int pos, int val){
// 	for (; pos < int(f.size()); pos = (pos | (pos + 1)))
// 		f[pos] += val;
// }
// delete element at K'th order statatic (count of values);
// void del(int k){
// 	int l = 0, r = N - 1, a;
// 	while(l <= r){
// 		int m = (l+r)/2;
// 		if(get(m) >= k) a = m, r = m-1;
// 		else l = m+1;
// 	}
// 	update(a, -1);
// }

// For searching sum :-
// vi BIT(1000);

// void update(int x, int delta){
//     for(; x < BIT.size(); x += x&-x)
//     	BIT[x] += delta;
// }

// ll query(int x){
//     ll sum = 0;
//     for(; x > 0; x -= x&-x)
//         sum += BIT[x];
//     return sum;
// }

// int searchNumber(long long prefSum){
//     long long sum = 0, num = 0;
//     for(int i = 21; i>=0 ; --i)
//         if((num + (1<<i) < BIT.size()) && 
//            (sum + BIT[num + (1<<i)] <= prefSum))
//             num += (1<<i), sum += BIT[num];
//     return num + 1;
// }

int main() {
    int n;
	cin >> n;
	vector<pair<int, int>> p(n);
	for (auto &pnt : p) cin >> pnt.first;
	for (auto &pnt : p) cin >> pnt.second;
	sort(p.begin(), p.end()); // sorted acc to val of x
	
	vector<int> vs;
	for (auto &pnt : p) vs.push_back(pnt.second); // pushing speeds
	sort(vs.begin(), vs.end()); // sorted vector of speeds

	// Index Compression;
	vs.resize(unique(vs.begin(), vs.end()) - vs.begin()); // removing duplicate speeds
	// we do this when we need indexed set of sorted values;
	// vs => vector of unique speeds in sorted order;

	// there can be multiple occurences of speed
	// vs is used as a hash table which maps speed to a index
	// and that index can be used in below vaetors to get in formation;
	
	long long ans = 0;
	vector<long long> cnt_of_speeds(vs.size()); // implemented as a fanvick tree
	// cnt_of_speeds[pos] => count of speeds which is equal to vs[pos];
	
	vector<long long> sum_of_cords(vs.size()); // implemented as a fanvick tree
	// sum_of_cords[pos] => sum of all coordinates whose speed is equal to vs[pos];

	// Suppose we don't use cnt_of_speeds, then we can get sum of coords whose
	// speed is less or more or equal to a particular speed, but we can't get 
	// get the count of such coords and we need count too, that why we used cnt vector;
	
	for (auto &pnt : p) {
		int pos = lower_bound(vs.begin(), vs.end(), pnt.second) - vs.begin();
		// pos => index of speed of point p in vs
		
		ans += get(cnt_of_speeds, pos) * 1ll * pnt.first - get(sum_of_cords, pos);
		
		update(cnt_of_cords, pos, 1); // increment the count of speed (vs[pos]) by 1;
		update(sum_of_cords, pos, pnt.first); // increment the count of sum at index pos by pnt.first (coordinates);
	}
	cout << ans << endl;
	return 0;
}