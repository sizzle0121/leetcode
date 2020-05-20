/*
 * The worst case: all numbers are the same, will be O(n)
 * Implement binary search by determining the target will be at the right side of the mid or the left side
 * However, when nums[mid] == nums[l], we are not able to decide which side to search
 * Therefore, we should move the l until nums[l] != nums[mid]
 * 	if all numbers are the same, we will have O(n) run-time complexity
 *
 * Time complexity: O(n)
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

bool Solution(vector<int> &nums, int target){
	if(nums.empty()) return false;
	int l = 0, r = nums.size()-1, mid;
	while(l <= r){
		mid = (r+l)/2;
		if(nums[mid] == target) return true;
		else if(nums[mid] > nums[l]){
			if(target > nums[mid]) l = mid+1;
			else{
				if(target < nums[l]) l = mid+1;
				else if(target > nums[l]) r = mid-1;
				else return true;
			}
		}else if(nums[mid] < nums[l]){
			if(target < nums[mid]) r = mid-1;
			else{
				if(target > nums[l]) r = mid-1;
				else if(target < nums[l]) l = mid+1;
				else return true;
			}
		}else{
			while(l <= r && nums[l] == nums[mid]) l++;
		}
	}
	return false;
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
