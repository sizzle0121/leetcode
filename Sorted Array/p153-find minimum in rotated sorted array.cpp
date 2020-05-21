/*
 * Binary Search:
 * The problem makes me notice that the way I choose the "mid" element for binary search\ 
 * will let nums[l] == nums[mid] when there are only two elements left
 * Therefore, if we compare nums[mid] with nums[l] to identify the situation will be a little bit more difficult
 * So I compare nums[mid] with nums[r]
 * And when there are only two left, campare nums[mid] with nums[r] will be comparing the last two elements
 * 
 * Time complexity: O(logn)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Solution(vector<int> &nums){
	int l = 0, r = nums.size()-1, mid;
	while(l < r){
		mid = (l+r)/2;
		if(nums[mid] > nums[r]){
			l = mid+1;//since we know nums[mid] already greater than an element, it must not the minimum
		}else{
			r = mid;//nums[r] is still possible the minimum
		}
	}
	return nums[l];
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(auto &num: nums)
		cin >> num;
	cout << Solution(nums) << endl;
}
