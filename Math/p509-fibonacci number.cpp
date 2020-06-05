/*
 * Trivial.
 *
 * Time complexity: O(N)
 * Space complexity: O(1)
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

int Solution(int N){
	if(N == 0) return 0;
	else if(N == 1) return 1;
	int prev1 = 1, prev2 = 0;
	for(int i=2; i<=N; i++){
		int cur = prev1 + prev2;
		prev2 = prev1;
		prev1 = cur;
	}
	return prev1;
}

int main(){
	int N;
	cin >> N;
	cout << Solution(N) << endl;
}
