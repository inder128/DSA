// pi[i] is the length of the longest proper prefix (lenght <= i) of 
// the substring str[0..i] which is also a suffix of this substring.
vi prefixFunction(string str) {
    int n = SZ(str);
    vi pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while(j > 0 and str[i] != str[j]){
            j = pi[j-1];
        }
        if(str[i] == str[j]){
            j++;
        }
        pi[i] = j;
    }
    return pi;
}