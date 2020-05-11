/*
	Brute-force:
	Enumerate all starting points and find the next number that is greater than it by recursion
	Update the LIS simultaneously, then we can get the answer

	Time complexity: O(2^n), since we look through all possible combination


	DP:
	If we can memorize the LIS of a position, then when we do brute-force, we can return when we reach it
	Therefore, starting from the backl, we can calculate the LIS for position i by look up from i+1 to nums.size()
	If nums[j] < nums[i] (i < j < nums.size()), then LIS(i) = max(current length of LIS(i) , LIS(j) + 1)
	The above is the one step difference and the optimal substructure
	By doing so and update our answer by comparing it to each LIS(i), we will eventually get the LIS of the array

	Time complexity: O(n^2)


	Binary search:
	If nums[i] is greater than the largest number in our sequence so far, we then push it back into our sequence\ 
	since it's obvious that it can increase our LIS sequence
	If nums[i] is not greater than the largest number in our sequence so far, we than use binary search to find its position in our sequence and replace the number at that position\ 
	since it is either a new starting point or the continual point for our LIS\ 
	by doing so, the length of our sequence won't change, but we will have a chance to look for a number that is greater than all numbers except for the largest number of our sequence, and it will replace it, then we can find smaller number to append to our sequence, making it longer
	The result sequence is not LIS, but its length will be the same as LIS

	Time complexity: O(nlogn)
*/
#include <iostream>
#include <vector>
using namespace std;

int Solution2(vector<int> &nums){
	if(nums.empty())	return 0;
	vector<int> seq;
	seq.push_back(nums[0]);
	for(int i=1; i<nums.size(); i++){
		if(nums[i] > seq.back())
			seq.push_back(nums[i]);
		else{
			int l = 0, r = seq.size()-1, mid;
			while(l <= r){
				mid = (l+r)/2;
				if(nums[i] > seq[mid])
					l = mid+1;
				else if(nums[i] < seq[mid])
					r = mid-1;
				else
					break;
			}
			if((mid != 0) || (mid == 0 && nums[i] <= seq[mid]))
				seq[mid] = nums[i];
			else
				seq[mid+1] = nums[i];
		}
	}
	return seq.size();
}

int Solution(vector<int> &nums){
	if(nums.empty()) return 0;
	vector<int> dp(nums.size());
	int ans = 1;
	dp[nums.size()-1] = 1;
	for(int i=nums.size()-2; i>=0; --i){
		int tmp = 1;
		for(int j=i+1; j<nums.size(); j++){
			if(nums[j] > nums[i]){
				tmp = max(tmp, dp[j]+1);
			}
		}
		dp[i] = tmp;
		if(dp[i] > ans)	ans = dp[i];
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	cout << Solution(nums) << endl;
	cout << Solution2(nums) << endl;
}
