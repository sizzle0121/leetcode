/*
 * Summary:
 * 1. Find the median
 * 2. Three-way partition
 * 3. Index mapping
 *
 *
 * Three-way partition:
 * (The typical three-way partitioning problem is p75-sort colors)
 * 
 * First, the intuition: it's not hard to observe that we can partition numbers into three groups by the median\ 
 * and we can then place numbers less than the median on even positions and numbers greater than the median on odd positions
 *
 * Here is the key point of this problem: how should we place those medians?
 * For this part of problem, we need some observations
 * We cannot start from the intersection of S and L (Smaller/Larger than the median)\ 
 * since medians will meet at the back
 * For example:
 * Original array: 1 1 2 2 2 2 3 3
 * The resuilt: 1 3 1 3 2 2 2 2
 *
 * We should seperate those medians apart, how about mapping the indices to 0 2 4 6 1 3 5 7, and do three-way partition
 * The result will become: 1 2 1 2 2 3 2 3 
 * (for the mapped indices, the array is 1 1 2 2 2 2 3 3)
 * This way still cannot seperate all the medians
 *
 * By further observation, we need to let S and L meet as soon as possible, then put the medians at the rest of the slots\ 
 * (slots: between two L or two S)
 * Therefore, the solution is to map the indices to 1 3 5 7 0 2 4 6, and do three-way partition\ 
 * but this time, we put L-group first, then M-group, then S-group, in order to fit the problem (large one should be at odd positions)
 * By doing so, we can seperate the medians to 7 and 0 (farthest), the previous method only seperate them to 6 and 1
 * The result: 2 3 2 3 1 2 1 2 (correct) 
 *
 * Time comeplxity: O(n), average, because of the nth_element sort
 * Space complexity: O(1)
 *
 * Appendix:
 * The least condition to satisfy the wiggle pattern is that the number of non-median numbers should >= half of nums.size()\ 
 * otherwise, it's impossible to sort the array in wiggle order
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void Solution(vector<int> &nums){
	int N = nums.size(), mid = (N-1)/2;
	nth_element(nums.begin(), nums.begin()+mid, nums.end());
	int median = nums[mid], less = 0, eq = 0, great = N-1;
	auto mapi = [N] (int i) { return ((i*2+1) % (N|1)); };
	while(eq <= great){
		if(nums[mapi(eq)] < median){
			swap(nums[mapi(eq)], nums[mapi(great)]);
			great--;
		}else if(nums[mapi(eq)] > median){
			swap(nums[mapi(eq)], nums[mapi(less)]);
			less++;
			eq++;
		}else{
			eq++;
		}
	}
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(auto &num: nums)
		cin >> num;
	
	Solution(nums);
	for(auto &num: nums)
		cout << num << " ";
	cout << endl;
}
