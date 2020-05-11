/*
	**	brute-force: O(m^n) = O(2^n), n: nums.size(), m: the largest number in nums
		at each position, first try the farthest jump
		if can't reach the last, then try the nearer one

	**	DP/pruning:	brute-force, but note the position that can't reach to the last
					avoiding repeated visit
		O(n*m) = O(n^2) cuz even if m > n, we still only visit at most n times

	** 	DP:	Reachable(i) = Reachable([i+1, i+nums[i]])
			Reachable(n) = true
			since we use i+1 as our suboptimal structrue, we should start from the last
			at the end, if Reachable(0) = true -> return true
		O(n^2)
	**	further improvement of method 3:
		since we will only search til the first meet Reachable([i+1, i+nums[i]]), that is, the leftmost one
		we can directly identify if i+nums[i] >= position of the leftmost one, and update the leftmost
		Time complexity can be reduced to O(n)

*/
#include <iostream>
#include <vector>

using namespace std;

/*	Brute-force

bool Jump(vector<int> &nums, int pos){
	if(pos >= nums.size()-1){
		return true;
	}
	for(int i=nums[pos]; i>0; i--){
		if(Jump(nums, pos + i))	return true;
	}
	return false;
}

*/

/*	O(n) method

bool Solution(vector<int> &nums){
	int leftmost = nums.size()-1;
	for(int i=nums.size()-2; i>=0; --i){
		if(i+nums[i] >= leftmost)
			leftmost = i;
	}
	return (leftmost == 0);
}

*/

bool Solution(vector<int> &nums){
	//return Jump(nums, 0);	
	bool reachable[nums.size()];
	for(int i=0; i<nums.size(); i++)
		reachable[i] = false;
	
	reachable[nums.size()-1] = true;
	for(int i=nums.size()-2; i>=0; --i){
		int farthest = (i+nums[i])>(nums.size()-1)? (nums.size()-1):(i+nums[i]);
		for(int j=i+1; j<=farthest; j++){
			if(reachable[j]){
				reachable[i] = true;
				break;
			}
		}
	}
	return reachable[0];
}

int main(){
	int T, tmp;//T: numbers of inputs
	cin >> T;
	vector<int> nums;
	while(T--){
		cin >> tmp;
		nums.push_back(tmp);
	}
	cout << Solution(nums) << endl;
	return 0;
}
