// increasing sum of array;
// codeforces link :- https://codeforces.com/contest/1313/problem/C2

#include <bits/stdc++.h>
using namespace std;

#define min3(a, b, c) min(a, min(b, c))
#define max3(a, b, c) max(a, max(b, c))
#define deb(x) cout << #x << "=" << x << endl
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << endl
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define el endl
#define tr(it, a) for (auto it = a.begin(); it != a.end(); it++)

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<string> vs;
const int mod = 1000000007;


void inc_sum(ll a[], ll n, ll inc[]){
    ll curr_i = 1, last_pop=0;
    stack <ll> stk;
    stk.push(0); 
    inc[0] = a[0];
    while(curr_i<n){
        // Stack will never be empty at the start of every loop;
        // pop all element from the stack which are bigger or equal
        // to the current element;
        while(!stk.empty() and a[stk.top()]>=a[curr_i])  stk.pop();
        // After poping, if stack becomes empty then current element is 
        // the minimum element so far;
        if(stk.empty())
            inc[curr_i] = (curr_i+1)*a[curr_i];
        // if stack does'ot becomes empty then top element will be the 
        // nearest element to current element which is less than current
        // element;
        // all elements between top element and current element will be
        // greater than or equal to the current element;
        else 
            inc[curr_i] = (curr_i-stk.top())*a[curr_i] + inc[stk.top()];
        // finally we will push the current element in the stack;
        stk.push(curr_i);
        curr_i++;
    }
    // suppose i, j are two consecutive elements in the stack then
    // all elements between i and j will be greater than element at i
    // and j both;
    // element at j will be greater than or equal to element at i;
    return;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 //    #ifndef ONLINE_JUDGE  
 //        freopen("input.txt", "r", stdin);  
 //        freopen("output.txt", "w", stdout);  
	// #endif 
    int t, i, j, k, n;
    t=1;
    while (t--){
        cin>>n;
        ll a[n], inc[n], dec[n];
        for (int  i = 0; i < n; i++)
            cin>>a[i];
        inc_sum(a, n, inc);

        reverse(a, a+n);
        inc_sum(a, n, dec);
        reverse(a, a+n);
        reverse(dec, dec+n);          

        ll max_i = -1, max_sum = dec[0];
        for (int i = 0; i < n-1; i++){
            if(inc[i]+dec[i+1]>max_sum)
                max_sum = inc[i] + dec[i+1],
                max_i = i;
        }
        if(inc[n-1]>max_sum) max_i = n-1;

        ll max_so_far;
        if(max_i!=-1) max_so_far = a[max_i];
        for (int i = max_i-1; i >= 0; --i){
            if(a[i]<max_so_far)
                max_so_far = a[i];
            else
                a[i] = max_so_far;
        }

        if(max_i!=n-1) max_so_far = a[max_i+1];
        for (int i = max_i+2; i < n; ++i){
            if(a[i]<max_so_far)
                max_so_far = a[i];
            else
                a[i] = max_so_far;
        }

        for (int i = 0; i < n; ++i)
            cout<<a[i]<<" ";
        cout<<el;
    }
    return 0;
}