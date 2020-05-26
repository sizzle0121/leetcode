/*
 * Backtrack:
 * Iterate throught all sequences that can sum up to the target
 * Time complexity: O(n^n), n is nums.size()
 *
 * DP:
 * Like coin change problem (since different sequences are counted as different combinations)
 * Time complexity: O(target * n)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void backtrack(vector<int> &nums, int target, int &ans, int sum){
	int N = nums.size();
	for(int i=0; i<N; i++){
		if(nums[i] + sum < target){
			backtrack(nums, target, ans, sum + nums[i]);
		}else if(nums[i] + sum == target){
			ans++;
			return;
		}else{
			return;
		}
	}
}

int Solution(vector<int> &nums, int target){
	int ans = 0;
	if(nums.empty()) return ans;
	sort(nums.begin(), nums.end());
	backtrack(nums, target, ans, 0);
	return ans;
}



int Solution2(vector<int> &nums, int target){
	if(nums.empty()) return 0;
	vector<unsigned long long> dp(target+1);
	dp[0] = 1;
	int N = nums.size();
	for(int i=1; i<=target; i++){
		for(int j=0; j<N; j++){
			if(nums[j] <= i)
				dp[i] += dp[i-nums[j]];
		}
	}
	return dp[target];
}

int main(){
	int T, target;
	cin >> T;
	vector<int> nums(T);
	for(auto &num: nums)
		cin >> num;
	cin >> target;
	cout << Solution2(nums, target) << endl;
	cout << Solution(nums, target) << endl;
}
