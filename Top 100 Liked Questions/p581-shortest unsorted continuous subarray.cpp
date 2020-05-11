/*
 * Sorting: 
 * Sort the array and compare it to the original one from the left and from the right once respectively
 * The first different element from the left is the left boundary
 * The first different element from the right is the right boundary
 * And the answer will be right - left + 1, if it's not negative
 * If it's negative, the array is already sorted, so the answer will be zero
 *
 * Time complexity: O(nlogn)
 *
 * Solution w/o Extra Space & O(n) Time Complexity:
 * The key point is to find the left and right boundries\ 
 * thus, we can check for where the order goes wrong from the left/right\ 
 * then find the minimum/maximum value after that position
 * The minimum/maximum will be the number should be place at the left/right boundaries
 * Therefore, we can simply find there correct position by the first number greater/less than them from the left/right
 * The answer will be right_correct_pos - left_correct_pos + 1
 * If it's negative, the array is already in ascending order, so the answer will be zero
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Solution(vector<int> &nums){
	int l = 0, r = nums.size()-1;
	vector<int> correct(nums);
	sort(correct.begin(), correct.end()); 
	while(l < nums.size() && correct[l] == nums[l])	l++;
	while(r >= 0 && correct[r] == nums[r])	r--;
	return (r-l+1) > 0? (r-l+1) : 0;
}

int Solution2(vector<int> &nums){
	int mini = nums[0], mini_i = 0, maxi = nums.back(), maxi_i = nums.size()-1;
	bool flag = false;
	for(int i=1; i<nums.size(); i++){
		if(nums[i] < nums[i-1]){
			flag = true;
			mini = nums[i];
			while(i < nums.size()){
				mini = min(mini, nums[i]);
				i++;
			}
		}
	}
	for(int i=nums.size()-2; i >= 0; --i){ 
		if(nums[i] > nums[i+1]){
			flag = true;
			maxi = nums[i];
			while(i >= 0){
				maxi = max(maxi, nums[i]);
				i--;
			}
		}
	}
	for(int i=0; flag && i<nums.size(); i++){
		if(nums[i] > mini){
			mini_i = i;
			break;
		}
	}
	for(int i=nums.size()-1; flag && i>=0; --i){
		if(nums[i] < maxi){
			maxi_i = i;
			break;
		}
	}
	return (flag)? (maxi_i-mini_i+1) : 0;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	cout << Solution2(nums) << endl;
}
