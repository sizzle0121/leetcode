/*
 * Like 3Sum, sort the array first (in order to use two pointers) 
 * Enumerate all possible starting points (here is two points)\ 
 * Then use two pointer s to find the last two points which sum to (target - first two points)\ 
 * The key point is to avoid duplicate quadruplets\ 
 * This can be done by preventing from duplicate starting points(same nums[i], or same nums[j])\ 
 * as well as when we found the last two points by two pointers, we should move both pointers to different points
 *
 * Time complexity: O(n^3)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int> > Solution(vector<int> &nums, int target){
	if(nums.size() < 4)	return vector<vector<int> >();
	sort(nums.begin(), nums.end());
	vector<vector<int> > ans;
	for(int i=0; i<nums.size(); i++){
		if(i-1 >= 0 && nums[i] == nums[i-1])	continue;
		for(int j=i+1; j<nums.size(); j++){
			if(j-1 != i && nums[j] == nums[j-1])	continue;
			int k = target - (nums[i] + nums[j]);
			int l = j+1, r = nums.size()-1;
			while(l < r){
				if(k == nums[l] + nums[r]){
					ans.push_back(vector<int>{nums[i], nums[j], nums[l++], nums[r--]});
					while(l < nums.size() && nums[l] == nums[l-1])	l++;
					while(r >= 0 && nums[r] == nums[r+1])	r--;
				}else if(k > nums[l] + nums[r]){
					l++;
				}else{
					r--;
				}
			}
		}
	}
	return ans;
}

int main(){
	int T, target;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	cin >> target;
	vector<vector<int> > ans = Solution(nums, target);
	for(int i=0; i<ans.size(); i++){
		for(int j=0; j<ans[i].size(); j++)
			cout << ans[i][j] << " ";
		cout << endl;
	}
}
