#include <bits/stdc++.h>
using namespace std;

// better method;
void range_count(int x[], int y[], int n, int x_cnt[], int r){
	for (int i = 0; i < n; ++i)
		x_cnt[x[i]]++, x_cnt[y[i]+1]--;

	for (int i = 1; i < r; ++i)
		x_cnt[i] += x_cnt[i-1];
}


void range_count_2(int x[], int y[], int n, int x_cnt[]){
	vector <pair<int, bool> > ranges;
	for (int i = 0; i < n; ++i){
		ranges.push_back(make_pair(x[i], true));
		// push one more then ending of the range;
		ranges.push_back(make_pair(y[i]+1, false));
	}
	sort(ranges.begin(), ranges.end());

	int open=0; // no of open range at a time;
	for (int i = 0; i < ranges.size()-1; ++i){
		if(ranges[i].second) open++;
		else open--;
		int l = ranges[i].first, r = ranges[i+1].first;
		for (int i = l; i < r; ++i)
			x_cnt[i] = open;
	}
}

int main(){
	int n=5, r=12; // range is max_range+1;
	// yi>=xi and range_i = [xi, yi] and max(yi)<r and min(x1)>=0;
	int x[] = {1, 3, 6, 7, 4};
	int y[] = {4, 5, 9, 8, 7};

	int x_cnt[r];
	memset(x_cnt, 0, sizeof(x_cnt));

	range_count(x, y, n, x_cnt, r);
	// range_count_2(x, y, n, x_cnt);
	
	for (int i = 0; i < r; ++i)
		cout<<x_cnt[i]<<" ";
	cout<<endl;
	return 0; 
}