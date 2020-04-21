/*
	First, Maximum subarray of A(0, i) = MaxSubArray(A(0, i-1)) or MaxSubArray include array[i-1] + array[i] or array[i]
	even if the last two < current maximum, we still need to calculate them for the future element added in the array

	DP:	max_sum(i) is denoted as the maximum sum from array[0] to array[i], which must includes array[i]
		max_sum(n) = (max_sum(n-1) + array[n]) or (array[n])
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
