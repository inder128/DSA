// below program computes nCr % M;
// it can also compute x^^y % M;

#include <bits/stdc++.h>
using namespace std;

const int N = 200043;
const int MOD = 998244353;

// operation keeping MOD in mind;
int add(int x, int y){
    x += y;
    while(x >= MOD) x -= MOD;
    while(x < 0) x += MOD;
    return x;
}

int mul(int x, int y){
    // to avoid overflow;
    return (x * 1ll * y) % MOD;
}

int fact[N];

// return (x raised to power y) % MOD;
int binpow(int x, int y){
    int z = 1;
    while(y){
        if(y & 1) z = mul(z, x);
        x = mul(x, x);
        y >>= 1;
    }
    return z;
}

int inv(int x){
    return binpow(x, MOD - 2);
}

// return x/y;
int divide(int x, int y){
    return mul(x, inv(y));
}

// array of factorials;
void precalc(){
    fact[0] = 1;
    for(int i = 1; i < N; i++)
        fact[i] = mul(fact[i - 1], i);
}

// returns nCk;
int C(int n, int k){
    return divide(fact[n], mul(fact[k], fact[n - k]));
}

int main() {
    precalc();
}

// inline int fast_expo(int base,int power,int modulo=mod){
//     base%=modulo;
//     if (base<0) base+=modulo;
//     ll x=base,cnt=power,ans=1;
//     while(cnt){
//         if (cnt&1) ans=(ans*x)%modulo;
//         x=(x*x)%modulo;
//         cnt>>=1;
//     }
//     // int tmp=ans;
//     return ans;
// }
// inline int inv(int base,int modulo=mod){
//     return fast_expo(base,modulo-2,modulo);
// }