/*
 * Brute-force:
 * Starting from i=1 and search for i in the array
 * Time complexity: O(n^2)
 * Space complexity: O(1)
 *
 * Sort:
 * Sort the array and search for 1, 2, ...
 * Time complexity: O(nlogn)
 * Space complexity: O(1)
 *
 * Using extra memory:
 * Scan the array once to mark all positive numbers existing in the array, and store the record in a table\ 
 * then find 1, 2, ... from the table, if not found -> return
 * Time complexity: O(n)
 * Space complexity: O(n)
 *
 * 
 * Optimal Solution:
 * The main idea is to place all positive numbers into their correct position\ 
 * correct position: the index of the position matches the number itself
 * Iterate through the array, if the current number doesn't match current index, place it to its correct position\ 
 * Before placing it, we should first temporarily store the number in the correct position\ 
 * After placing it, we should go to the correct position of the number we temporarily stored and repeat the above process\ 
 * until the number in the correct position <= 0 or > nums.size() or already matches the index
 * 
 * After placing all positive numbers in the array to their correct positions, we can simply scan through the array and see\ 
 * if the index matches the number in the position, if not, then return the index
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * */
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int NaiveSolution(vector<int> &nums){
	if(nums.empty()) return 1;
	unordered_set<int> exist;
	for(auto &num: nums)
		if(num > 0)
			exist.insert(num);

	int n = 1;
	while(1){
		if(exist.find(n) == exist.end()) break;
		n++;
	}
	return n;
}

int Solution(vector<int> &nums){//time complexity: O(n), space complexity: O(1)
	if(nums.empty()) return 1;
	int N = nums.size();
	nums.push_back(-1);
	for(int i=0; i<N; i++){
		if(nums[i] > 0 && nums[i] <= N && nums[i] != i){
			int ii = nums[i];
			while(1){
				if(nums[ii] > 0 && nums[ii] < nums.size() && nums[ii] != ii){
					int tmp = nums[ii];
					nums[ii] = ii;
					ii = tmp;
				}else{
					nums[ii] = ii;
					break;
				}
			}
		}
	}
	for(int i=1; i<=N; i++){
		//cout << i << ": " << nums[i] << endl;
		if(nums[i] != i)
			return i;
	}
	return N+1;
}

int Solution2(vector<int> &nums){//by swap, same time/space complexity
	if(nums.empty()) return 1;
	int N = nums.size();
	for(int i=0; i<N; i++){
		while(nums[i] > 0 && nums[i] <= N && nums[nums[i]-1] != nums[i])
			swap(nums[i], nums[nums[i]-1]);
	}
	for(int i=0; i<N; i++)
		if(nums[i] != i+1)
			return i+1;
	return N+1;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(auto &num: nums)
		cin >> num;
	cout << NaiveSolution(nums) << endl;
	cout << Solution(nums) << endl;
}
