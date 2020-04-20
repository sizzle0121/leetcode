/*
	DP:	max_sum(i) is denoted as the maximum sum from array[0] to array[i]
		max_sum(n) = max_sum(n-1) or (sum_from_max_sum(n-1) + array[n]) or (array[n])
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Solution(vector<int> &nums){
	int dp[nums.size()];
	dp[0] = nums[0];
	int maxi = nums[0];
	for(int i=1; i<nums.size(); i++){
		dp[i] = max(dp[i-1]+nums[i], nums[i]);
		//cout << "head: " << head << " SFM: " << sum_from_max << endl;
		if(dp[i] > maxi)	maxi = dp[i];
	}	
	return maxi;
}

int main(){
	int T, tmp;//T: number of inputs
	vector<int> nums;
	cin >> T;
	while(T--){
		cin >> tmp;
		nums.push_back(tmp);
	}
	cout << Solution(nums) << endl;
	return 0;
}
