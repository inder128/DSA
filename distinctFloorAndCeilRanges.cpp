#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef pair<int,int> pi;

int main(){
    int n; cin >> n;
    vector <pi> lr;
    for(int l = 1, r; l <= n; l = r + 1){
	    r = n / (n / l);
	    lr.pb({l, r});
	}

	vector <pi> lrCeil;
    for(int l, r = n; r >= 1; r = l - 1){
        int d = (n + r - 1) / r;
        l = (n + d - 1) / d;
        lrCeil.pb({l, r});
    }
    return 0;
}