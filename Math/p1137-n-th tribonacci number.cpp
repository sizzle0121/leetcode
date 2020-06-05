/*
 * Trivial.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

int Solution(int n){
	if(n == 0) return 0;
	else if(n == 1) return 1;
	else if(n == 2) return 1;
	int prev1 = 1, prev2 = 1, prev3 = 0;
	for(int i=3; i<=n; i++){
		int cur = prev1 + prev2 + prev3;
		prev3 = prev2;
		prev2 = prev1;
		prev1 = cur;
	}
	return prev1;
}

int main(){
	int n;
	cin >> n;
	cout << Solution(n) << endl;
}
