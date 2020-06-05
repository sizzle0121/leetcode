/*
 * DP:
 * Let dp[i] be denoted as the minimum steps required to reach to the top from position i
 *
 * One-step difference (also the optimal substructure):
 * At pos[i], we can only skip to pos[i+1] or pos[i+2], dp[i] will be cost[i] + min(dp[i+1], dp[i+2])
 * 
 * Base case:
 * dp[N-1] = cost[N-1]
 * dp[N-2] = cost[N-2]
 *
 * return min(dp[0], dp[1]) if there are greater than 1 step, otherwise, return 0 or 1 (empty or onlu 1 step)
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Solution(vector<int> &cost){
	int N = cost.size();
	if(N == 0) return 0;
	else if(N == 1) return cost[0];
	int step1 = cost[N-2], step2 = cost[N-1];
	for(int i=N-3; i>=0; --i){
		int cur = cost[i] + min(step1, step2);
		step2 = step1;
		step1 = cur;
	}
	return min(step1, step2);
}

int main(){
	int T;
	cin >> T;
	vector<int> cost(T);
	for(auto &c: cost)
		cin >> c;
	cout << Solution(cost) << endl;
}
