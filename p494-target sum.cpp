#include <iostream>
#include <vector>
using namespace std;

int Solution(vector<int> &nums, int S){
	if(nums.empty())	return 0;
	int sum = 0;
	for(int i=0; i<nums.size(); i++)
		sum += nums[i];
	int target = sum - S;
	if(target < 0 || target % 2 == 1)	return 0;
	target /= 2;
	vector<int> dp(target+1);
	dp[0] = 1;
	for(int i=0; i<nums.size(); i++){
		for(int j=target; j-nums[i]>=0; --j){
			if(dp[j-nums[i]] > 0)
				dp[j] += dp[j-nums[i]];
		}
	}
	return dp[target];
}

int main(){
	int T, S;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	cin >> S;
	cout << Solution(nums, S) << endl;
}
