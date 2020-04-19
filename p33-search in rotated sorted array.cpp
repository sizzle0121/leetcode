/*
	Binary Search w special case handling
*/
#include <iostream>
#include <vector>

using namespace std;

int Solution(vector<int> &nums, int target){
	if(nums.empty())	return -1;
	//first round
	int flag = 0;
	if(target > nums[0])	flag = 1;	
	else if(target < nums[0])	flag = -1;
	else	return flag;
	
	//after first round
	int l = 0, r = nums.size()-1, mid;
	while(l <= r){
		mid = (l+r)/2;
		if(flag == 1){
			if(target > nums[mid]){
				if(nums[mid] < nums[l])	r = mid-1;
				else					l = mid+1;
			}
			else if(target < nums[mid])	r = mid-1;
			else						return mid;
		}else if(flag == -1){
			if(target > nums[mid])		l = mid+1;	
			else if(target < nums[mid]){
				if(nums[mid] > nums[r])	l = mid+1;
				else					r = mid-1;
			}else						return mid;
		}
	}
	return -1;
}

int main(){
	int T, tmp;//T: numbers of input
	int target;
	cin >> T;

	vector<int> nums;
	while(T--){
		cin >> tmp;
		nums.push_back(tmp);
	}
	cin >> target;
	cout << Solution(nums, target) << endl;

	return 0;
}
