/*
 * Optimal Solution:
 * The key point is to observe the pattern (wrote some examples and came up with it)
 * Just like caompring numbers, the next permutation in lexicographical order will be the next larger number\ 
 * consists of same digits of "numbers"
 * For example, 1 2 3, we can view it as 123 (one hundred and twenty three)\ 
 * The next larger number using only 1, 2, 3 will be 132 (one hundred and thirty two)
 *
 * So, when we comparing numbers, we are actually looking for the first different digits of them from the left\ 
 * and compare the digits
 *
 * But now we are finding the next permutation, say, the least number which is larger than the current one
 * Therefore, we should replace a digit with a number (on its righthand side) that is greater than it, and\ 
 * in order to make sure it's "the least", the digit should be the rightmost one of that sort of digits
 * (only by replacing a digit with a number that is greater than it from its right can make the order larger)
 * Finally, the pattern comes up
 * 
 * Starting from the righthand side, we look for the first digit that becomes descending\ 
 * which means it must be the rightmost one that has a number on its right which is greater than it
 * We swap them and make all digits on its right become ascending order (make sure it's the least order/next permutation)
 * If we can't find any that sort of digit, it means the current order is the last lexicographical order,\ 
 * we should simply reverse it
 *
 * Time complexity: O(2n) = O(n)
 * Space complexity: O(1)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void Solution(vector<int> &nums){
	if(nums.empty()) return;
	int N = nums.size(), flag = -1;
	for(int i=N-2; i>=0; --i){
		if(nums[i] < nums[i+1]){
			flag = i;
			for(int j=N-1; j>i; --j){
				if(nums[j] > nums[i]){
					swap(nums[i], nums[j]);
					break;
				}
			}
			break;
		}
	}
	if(flag == -1) reverse(nums.begin(), nums.end());
	else reverse(nums.begin()+flag+1, nums.end());//reverse all digits behind it

	//Print
	for(auto &num: nums)
		cout << num << " ";
	cout << endl;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(auto &num: nums)
		cin >> num;
	Solution(nums);
}
