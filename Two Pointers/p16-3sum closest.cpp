/*
 * Two Pointers:
 * First sort the array
 * Then similar as 3Sum, iterate each num\ 
 * and for each num, use two pointers to find the other two numbers that makes their sum closer to the target
 * If their sum > the target, then right-- (if left++, then they will move away from the target)
 * If their sum < the target, then left++ (if right--, then they will move away from the target)
 * No right++ or left--, since it's like the mismove at the last step
 * If sum == the target, then simply return the target
 * update the answer for each pointer update (if closer)
 *
 * Time complexity: O(n^2)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Solution(vector<int> &nums, int target){
	sort(nums.begin(), nums.end());
	int ans = nums[0] + nums[1] + nums[2], n = nums.size();
	for(int i=0; i<n; i++){
		int l = i+1, r = n-1;
		while(l < r){
			int tmp = nums[i] + nums[l] + nums[r];
			if(abs(tmp - target) < abs(ans - target))
				ans = tmp;
			if(tmp > target){
				r--;
			}else if(tmp < target){
				l++;
			}else if(tmp == target){
				return tmp;
			}
		}
	}
	return ans;
}

int main(){
	int T, target;
	cin >> T;
	vector<int> nums(T);
	for(auto &num: nums)
		cin >> num;
	cin >> target;
	cout << Solution(nums, target) << endl;
}
