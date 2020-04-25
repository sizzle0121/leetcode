/*
	Using hash table to count/calculate math is simple

	XOR:
	a XOR 0 = a
	a XOR a = 0
	therefore, A XOR B XOR A = B

	Time complexity: O(n)
	Space complexity: in-place
*/

#include <iostream>
#include <vector>

using namespace std;

int Solution(vector<int> &nums){
	for(int i=1; i<nums.size(); i++)
		nums[i] ^= nums[i-1];
	return nums.back();
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	cout << Solution(nums) << endl;
	return 0;
}
