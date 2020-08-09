// Dymanic programing caps problem;
// geeksforgeeks link:-
// https://www.geeksforgeeks.org/bitmasking-and-dynamic-programming-set-1-count-ways-to-assign-unique-cap-to-every-person/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

void printvec(vector <int> v){
    vector<int>::iterator ptr;
    for (ptr = v.begin(); ptr < v.end(); ptr++) 
        cout<<(*ptr)<<" ";  
    cout<<endl;  
}

int main(){
	int n;
	cin>>n;
	int dp[101][1<<n];
	vector <int> caplist[101];
	for (int i = 0; i < (1<<n); ++i)
		dp[0][i]=0;
	string temp, str; 
    int x; 
    getline(cin, str); 
    for (int i=1; i<n+1; i++){ 
        getline(cin, str); 
        stringstream ss(str); 
        while (ss >> temp){ 
            stringstream s; 
            s << temp; 
            s >> x; 
            caplist[x].push_back(i); 
        } 
    } 
    dp[0][0]=1;
    for (int i = 1; i < 101; ++i){
    	for (int j = 0; j < (1<<n); ++j){
    		dp[i][j] = dp[i-1][j];
    		for (int k = 0; k < caplist[i].size(); ++k){
    			if(j & 1<<(caplist[i][k]-1))
    				dp[i][j] += dp[i-1][j-(1<<(caplist[i][k]-1))];
    		}
    	}
    }
    cout<<dp[100][(1<<n)-1]<<endl;
	return 0;
}
