/*
 * Binary Search:
 * The objective is to search for a number\ 
 * plus there is a pattern for us to search when the randomly picked number is not what we want
 * Thus, binary search is highly possible a way to solve this
 *
 * Time complexity: O(logn)
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

int vb;

bool isBadVersion(int version){
	return version >= vb;
}

int Solution(int n){
	long long l = 1, r = n, mid;
	while(l <= r){
		mid = (l+r)/2;
		if(isBadVersion(mid)){
			if(mid == 1 || !isBadVersion(mid-1)) return mid;
			else r = mid-1;
		}else{
			l = mid+1;
		}
	}
	return -1;
}

int main(){
	int n;
	cin >> n >> vb;
	cout << Solution(n) << endl;
}
