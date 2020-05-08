/*
	Using extra memory is trivial

	Since numbers will be in the interval [1, n] and we have n numbers in total,\ 
	we can placed the number to its position in the array, then see which position doesn't match the number in it
	However, this will use additional memory or exceed O(n) time complexity
	Therefore, I then thought to just mark the position it should be placed by turning the number at that position into its negative
	By doing so, we can check which position still contains positive and push the index+1 into our answer

	Time complexity: O(n)
	Space complexity: O(1), the answer list doesn't count as extra memory
*/
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

vector<int> Solution(vector<int> &nums){
	if(nums.empty())	return vector<int>();
	for(int i=0; i<nums.size(); i++)
		if(nums[abs(nums[i]) - 1] > 0)
			nums[abs(nums[i]) - 1] = -nums[abs(nums[i]) - 1]; 
	vector<int> ans;
	for(int i=0; i<nums.size(); i++)
		if(nums[i] > 0)
			ans.push_back(i+1);
	return ans;
}

vector<int> trivialSol(vector<int> &nums){
	int n = nums.size();
	if(n == 0)	return vector<int>();
	vector<bool> pres(n+1);
	vector<int> ans;
	for(int i=0; i<n; i++)
		pres[nums[i]] = true;
	for(int i=1; i<=n; i++)
		if(!pres[i])	ans.push_back(i);
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	vector<int> ans = Solution(nums);
	for(int i=0; i<ans.size(); i++)
		cout << ans[i] << " ";
	cout << endl;
}
