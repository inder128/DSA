#include <bits/stdc++.h>
using namespace std;
 
#define rng(x) x.begin(), x.end()
#define maxi(x, y) x = max(x, (y))
#define mini(x, y) x = min(x, (y))
#define pb push_back
#define F first
#define S second
#define el '\n'
template<typename T>
istream&operator>>(istream&is,vector<T>&v){for(auto&it:v)is>>it;return is;}
template<class L, class R> ostream& operator<<(ostream &os, pair<L,R> P) {
    return os << "(" << P.F << "," << P.S << ")"; }
template<class T> ostream& operator<<(ostream &os, vector<T> V) {
    os << "[ "; for(auto v : V) os << v << " "; return os << "]"; }
template<class T> ostream& operator<<(ostream &os, set<T> S){
    os << "{ "; for(auto s:S) os<<s<<" "; return os<<"}"; }
#define db(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) { cout<<name<<" : "<<arg1<<'\n';}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
    const char* comma = strchr(names + 1, ',');
    cout.write(names,comma-names)<<" : "<<arg1<<" |";__f(comma+1, args...);}
typedef pair<int,int> pi; typedef vector<int> vi; typedef vector<vi> vvi;
 
/*-----------------------------Code begins----------------------------------*/

int rand(int l, int r){
	return l + rand() % (r - l + 1);
}

void solve(int bin){
	int n = rand(5, bin * 5 + 5);
    int mxW = bin * 5 + 5;
	set <pi> edges;
	for (int j = 1; j < n; ++j){
		edges.insert({rand(0, j - 1), j});
	}
	for (int j = 0; j < rand(0, n/bin)*n; ++j){
		int u = rand()%n, v = rand()%n;
		if(u == v) continue;
		if(u > v) swap(u, v);
		edges.insert({u, v});
	}
	

	cout<<n<<" "<<edges.size()<<el;
	for(pi p : edges){
		cout<<p.F<<" "<<p.S<<" "<<rand(1, mxW)<<el;
	}
    int a = rand(1, n), b;
    do{
        b = rand(1, n);
    }while(b == a);

    cout<<a<<" "<<b<<" "<<rand(1, mxW)<<el;
}
 
int main(int argc, char* argv[]){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int T=1;
    //cin>>T;
    srand(atoi(argv[1]));
    while(T--){
        solve(atoi(argv[1]));
    }
    return 0;
}