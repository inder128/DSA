// Median of two sorted  arrays of any sizes.
// geeksforgeeks link of the question:-
// https://www.geeksforgeeks.org/median-of-two-sorted-arrays-of-different-sizes/

#include <iostream>
using namespace std;

// time complexity -> O(log(min(n, m)));
// space complexity -> O(log(min(n, m)));

int n, m, len;

double mean(int a, int b){
	return (a+b)/2.0;
}

double median_1arr(int arr[], int n){
	if(n%2==1) return arr[n/2];
	return mean(arr[n/2-1], arr[n/2]);
}

// handle final cases
double base_case(int a[], int b[], int s){


	// x1 = last element in arr a which is in left partition;
	// x2 = last element in arr b which is in left partition;
	int x1 = s;
	int x2 = len - (x1+1) - 1;
	// y1 = first element in arr a which is in right partition;
	// y2 = first element in arr b which is in right partition; 
	int y1 = x1+1, y2 = x2+1;

	int l=n+m;

	// if total elements are odd
	if(l%2==1)
		// because left partion have more elements then right partition 
		// so median will be max element of left partition
		return max(a[x1], b[x2]);

	// if total elements are even, both partitions have equal elements.
	// here median will be mean of max element of left patrtion and 
	// min element of right element.
	return mean(max(a[x1], b[x2]), min(a[y1], b[y2]));
}

double bs_median(int a[], int b[], int s, int e){

	// if s==e the we have reached our answer, no further patition can occur
	if(s==e) return base_case(a, b, s);

	int x1 = s+(e-s)/2;
	int x2 = len - (x1+1) - 1;
	int y1 = x1+1, y2 = x2+1;

	// checking if mid(x1) partition gives us answer
	// if below conditions are true then we don't have to do further checking.
	if(a[x1]<=b[y2] and b[x2]<=a[y1])
		return base_case(a, b, x1);

	// Note :- 
	// (a[x1]>b[y2] and b[x2]>a[y1]) this can never be true;
	// suppose above conditions are true then :-
	// this (a[x1]>b[y2] and b[y2]>b[x2] and b[x2]>a[y1]) will be true
	// which means (a[x1]>a[y1]) will be true, which can't happen
	// so above conditions cannot be true;

	// if below condition is true then it means that we have to reduce x1
	// which means optimal x1 is in left of present x1;
	if(a[x1]>b[y2])
		return bs_median(a, b, s, x1-1);

	// optimal x1 is in right of present x1;
	return bs_median(a, b, x1+1, e);
}

double median(int a[], int b[]){

	// handling edje cases;
	if(n==0 and m==0) return -1;
	if(n==0) return median_1arr(b, m);
	if(m==0) return median_1arr(a, n);
	if(n==1 and m==1) 
		return mean(a[0], b[0]);

	// taking care of the case when all elementation on left partition are from
	// one of the arrays, we cant apply partition algorithm in that case.
	int l = n+m;
	if(l%2==1){
		int mid = l/2;

		// it is necessary to check if length of the array allows this case to happen.
		if(mid<n and a[mid]<=b[0])
			return a[mid];
		if(mid<m and b[mid]<=a[0])
			return b[mid];
	}
	else{
		int m1 = l/2-1, m2 = l/2;
		if(m2<n and a[m2]<=b[0])
			return mean(a[m1], a[m2]);
		if(m2<m and b[m2]<=a[0])
			return mean(b[m1], b[m2]);
	}

	// len is the no. of elements in the left partition.
	// if total elements are even then len = total/2
	// if total elements are odd then len = totla/2 + 1;
	// for ex: total=10 then len=5; total = 11 then len=6; 
	len = l/2 + l%2;

	// passing the shorter array in the partion algorithm;
	if(n<=m)
		return bs_median(a, b, 0, n-1);
	return bs_median(b, a, 0, m-1);
}

int main(){
	cin>>n>>m;
	int a[n], b[m];
	for (int i = 0; i < n; ++i)
		cin>>a[i];
	for (int i = 0; i < m; ++i)
		cin>>b[i];
	cout<<median(a, b)<<endl;
	return 0;
}




