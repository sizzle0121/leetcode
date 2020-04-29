/*
	Brute-force:
	Starting from num[i=0], each time we add num[i+2] to our accumulated sum until we reach the end
	Then, in the same level of recursion, we try to add num[i+3] instead of num[i+2] to our accumulated sum, and update the maximum if it's greater
	Then we return to upper level, and try i+1 -> (i+1)+2 and (i+1)+3, by recursion, iterate through all possible solutions
	For example:
		for 1 2 3 4 5 6
		we try 	1 3 5
		then	1 3 6
		then 	1 4 6
		then	2 4 6
		then	2 5

	Why no need to try i+4, i+5, ...?
	Since i+4 = (i+2)+2, i+5 = (i+2)+3 -> therefore, they've already been try in i+2, i+3 rounds
	Also, if we directly try from i+4, we will miss i+2
	
	Time complexity: O(2^(n/2))
	
	DP:
	We can simplify the brute-force solution by recording the maximum of num[i to end]
	Therefore, next time we arrive at num[i], we don't need to go deeper and are still able to get the accumulated sum
	Moving further, we can come into the DP solution
		Starting from the back,
		num[i] = num[i] + max(max_sum_from_end[i+2] , max_sum_from_end[i+3])
		
		Base case: 	num[size()-1] = num[size()-1]
					num[size()-2] = num[size()-2]
	
	Time complexity: O(n)
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Solution(vector<int> &nums){
	if(nums.empty())	return 0;
	if(nums.size() == 1)	return nums[0];
	for(int i=nums.size()-1; i>=0; i--){
		if(i+2 < nums.size() && i+3 < nums.size())
			nums[i] += max(nums[i+2], nums[i+3]);
		else if(i+2 < nums.size())
			nums[i] = nums[i+2];
	}
	return max(nums[0], nums[1]);
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<nums.size(); i++)
		cin >> nums[i];
	cout << Solution(nums) << endl;
}
