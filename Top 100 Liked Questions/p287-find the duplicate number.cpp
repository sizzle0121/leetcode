/*
	Solve by sorting or set is trivial (see solution 1 & 2)
	Time complexity: O(nlogn) for sorting, O(n) for set
	Space complexity: O(1) for sorting, O(n) for set
	
	
	Solve by Floyd's Tortoise and Hare
	Use two pointers, fast and slow, one moves two steps a time, the other moves one step a time
	The value of array[i] is the node linked from i, e.g. nums[5]=2 -> node 5 link to node 2
	Starting from index 0, the slow and fast will finally meet (since there is a ring in the linked list)
	Then set another pointer from index 0 to move 1 step a time together with the slow pointer moving from the meeting point
	When they meet, the node they point to will be our answer (the duplicate number)

	Time complexity: O(n)
	Space complexity: O(1)
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int Solution1(vector<int> &nums){
	sort(nums.begin(), nums.end());
	for(int i=1; i<nums.size(); i++)
		if(nums[i] == nums[i-1])
			return nums[i];
	return 0;
}

int Solution2(vector<int> &nums){
	set<int> pool;
	for(int i=0; i<nums.size(); i++){
		if(pool.find(nums[i]) != pool.end())	return nums[i];
		else	pool.insert(nums[i]);
	}
	return 0;
}

int Solution3(vector<int> &nums){
	int fast = 0, slow = 0;
	bool flag = false;
	while(slow != fast || !flag){
		flag = true;
		slow = nums[slow];
		fast = nums[nums[fast]];
	}
	fast = 0;
	while(slow != fast){
		slow = nums[slow];
		fast = nums[fast];
	}
	return slow;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	cout << Solution3(nums) << endl;
}
