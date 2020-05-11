#include <iostream>
#include <vector>
#include <map>

using namespace std;

map<int, bool> use;

void backtrack(vector<vector<int> > &ans, vector<int> &tmp, vector<int> &nums){
	if(tmp.size() == nums.size()){
		ans.push_back(tmp);
		return;
	}
	for(int i=0; i<nums.size(); i++){
		if(!use[nums[i]]){
			tmp.push_back(nums[i]);
			use[nums[i]] = true;
			backtrack(ans, tmp, nums);
			tmp.pop_back();
			use[nums[i]] = false;
		}
	}
}

void Solution(vector<int> &nums){
	vector<vector<int> > ans;
	if(nums.empty())	return;
//	if(nums.empty()){					this for leetcode
//		ans.push_back(vector<int>());
//		return ans;
//	}
	for(int i=0; i<nums.size(); i++)
		use[nums[i]] = false;
	
	vector<int> tmp;
	backtrack(ans, tmp, nums);
	for(int i=0; i<ans.size(); i++){
		for(int j=0; j<ans[i].size(); j++)
			cout << ans[i][j] << " ";
		cout << endl;
	}
}

int main(){
	int T, tmp;//T: number of inputs
	vector<int> nums;
	cin >> T;
	while(T--){
		cin >> tmp;
		nums.push_back(tmp);
	}
	Solution(nums);
	return 0;
}
