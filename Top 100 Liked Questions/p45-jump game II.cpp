/*
 * Backtrack:
 * Traverse all possible jumps until reach the last index
 * Time complexity: O(2^n)
 *
 * DP:
 * The one-step difference: 
 * 	For position i, the minimum steps jumping from i to the last index is\ 
 * 	(the minimum steps from i+0 to i+nums[i]) + 1
 * Optimal Substructure:
 * 	dp[i] = min(dp[i+0 ... i+nums[i]]) + 1
 * Base:
 * 	dp[N-1] = 0
 *
 * Time complexity: O(n^2)
 *
 *
 * BFS (Optimal Solution):
 * Inspired by the backtracking solution
 * Similarily, we traverse each node that node i can reach\ 
 * However, we traverse them level by level, and we don't visit the nodes which are already in the previous levels
 * The nodes in the same level represent that they can be reached by same steps of jumps
 * We maintain a range represent current level, and extend the right bound by the maximum of i+nums[i], where i is in the range 
 * Assume that l, r are the left and right bounds for the previous range(level)\ 
 * the left and right bounds of the new range will become l' = r+1, r' = extended max_r of the previous range
 *
 * Once the extended max_r >= N-1, return the current step
 *
 * Time complexity: O(n)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Solution(vector<int> &nums){
	int N = nums.size();
	vector<int> dp(N);
	dp[N-1] = 0;
	for(int i=N-2; i>=0; --i){
		int tmp = -1;
		for(int j=1; j<=nums[i] && i+j<N; j++){
			if(tmp == -1) tmp = dp[i+j];
			else tmp = min(tmp, dp[i+j]);
		}
		dp[i] = (tmp == -1 || tmp == 2147483647)? 2147483647 : tmp+1;
	}
	return dp[0];
}

int Solution2(vector<int> &nums){//optimal solution
	int N = nums.size(), ans = 0, l = 0, r = 0, maxr = 0;
	while(r < N-1){
		ans++;
		for(int i=l; i<=r; i++){
			if(i + nums[i] >= N-1) return ans;
			maxr = max(maxr, i + nums[i]);
		}
		l = r+1;
		r = maxr;
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(auto &num: nums)
		cin >> num;
	cout << Solution2(nums) << endl;
	cout << Solution(nums) << endl;
}
