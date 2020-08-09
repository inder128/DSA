#include <bits/stdc++.h>
using namespace std;

#define deb(x) cout<<#x<<"="<<x<<endl
#define deb2(x,y) cout<<#x<<"="<<x<<", "<<#y<<"="<<y<<endl
#define deb3(x,y,z) cout<<#x<<"="<<x<<", "<<#y<<"="<<y<<", "<<#z<<"="<<z <<endl

// Elevator DP problem;
int main(){
	int n, max_limit; // n<=20
	cin>>n>>max_limit;
	vector<int> w(n);
	for(auto &i : w)
		cin>>i;

	vector<int> rides(1<<n, INT_MAX), last(1<<n, INT_MAX);
	// last[s] = minimum sum of weights of elements going up
	// in last shift in optimal arrangement of elements of s;

	rides[0] = 0; last[0] = max_limit;
	for (int i = 1; i < 1<<n; ++i){
		for (int b = 0; b < n; ++b){
			if((i&(1<<b))==0) continue;
			int tmp_set = i^(1<<b);
			int tmp_rides = rides[tmp_set] + (last[tmp_set]+w[b] > max_limit);
			int tmp_last = last[tmp_set] + w[b];
			if(tmp_rides <= rides[i]){
				rides[i] = tmp_rides;
				if(tmp_last <= max_limit and tmp_last<last[i])
					last[i] = tmp_last;
				// if w[b]<=max_limit is given;
				// we need to minimise last[i];
				else if(tmp_last>max_limit and w[b] < last[i]) 
					last[i] = w[b];
			}
			// deb3(tmp_set, tmp_rides, rides[i]);
			// deb2(tmp_last, last[i]);
		}
	}

	cout<<rides[(1<<n) - 1]<<endl;
	cout<<last[(1<<n) - 1]<<endl;
	return 0;
}