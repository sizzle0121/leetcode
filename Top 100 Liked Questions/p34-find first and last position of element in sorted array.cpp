/*

**	brute-force, scan through the array -> O(n)

**	Binary Search -> O(logn)
	logn + logn (left + right)

*/
#include <iostream>
#include <vector>

using namespace std;

bool BS(vector<int> &ans, vector<int> &nums, bool flag, int target){	
	bool found = false;
	int l = 0, r = nums.size()-1, mid;
	while(l <= r){
		mid = (l + r)/2;
		if(target > nums[mid])	l = mid+1;
		else if(target < nums[mid])	r = mid-1;
		else{
			found = true;
			if(flag){
				if((mid == 0) || (mid > 0 && nums[mid] != nums[mid-1])){	ans[0] = mid;	return found; }
				else	r = mid-1;
			}else{
				if((mid == nums.size()-1) || (mid < nums.size()-1 && nums[mid] != nums[mid+1])){	ans[1] = mid;	return found; }
				else	l = mid+1;
			}
		}
	}
	return found;
}

vector<int> Solution(vector<int> &nums, int target){
	bool found = false;
	vector<int> ans(2);
	if(!nums.empty()){
		found = BS(ans, nums, 1, target);
		found = BS(ans, nums, 0, target);
	}
	if(found)	return ans;
	else{
		ans[0] = -1;
		ans[1] = -1;
		return ans;
	}
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
	
	vector<int> ans;
	ans = Solution(nums, target);
	cout << ans[0] << " " << ans[1] << endl;

	return 0;
}
