mt19937 mrand(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int r = 1e13){ return uniform_int_distribution<int>(0, r)(mrand); }
int rnd(int l, int r){ return uniform_int_distribution<int>(l, r)(mrand); }