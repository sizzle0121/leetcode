/*
	In-place Approach:
	Simply move each non-zero element to the left, and place it at the right of all previously moved non-zero elements
	When all non-zero elements have been moved, fill up the rest of the array with zeros

	Time complexity: O(n)
	Space complexity: O(1)
*/
#include <iostream>
#include <vector>
using namespace std;

void Solution(vector<int> &nums){
	int N = nums.size(), nonzero = 0;
	for(int i=0; i<N; i++)
		if(nums[i] != 0)
			nums[nonzero++] = nums[i];
	for(int i=nonzero; i<N; i++)
		nums[i] = 0;
	
	for(int i=0; i<N; i++)
		cout << nums[i] << " ";
	cout << endl;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	Solution(nums);
}
