/*
	backtracking
	for each size of subset, enumerate the combination
	at each position, only iterate from current position + 1 to nums.size() so as to avoid duplicate subsets
	
	Time complexity: O(2^n), since each element can be absent or present
*/
#include <iostream>
#include <vector>

using namespace std;

void enumerate(vector<vector<int> > &ans, vector<int> &tmp, vector<int> &nums, int len, int curLen){
	if(tmp.size() == len){
		ans.push_back(tmp);
		return;
	}
	for(int i=curLen; i<nums.size(); i++){
		tmp.push_back(nums[i]);
		enumerate(ans, tmp, nums, len, i+1);
		tmp.pop_back();
	}
}

void Solution(vector<int> &nums){
	vector<vector<int> > ans;
	vector<int> tmp;
	for(int i=0; i<=nums.size(); i++){
		enumerate(ans, tmp, nums, i, 0);
	}
	for(int i=0; i<ans.size(); i++){
		for(int j=0; j<ans[i].size(); j++)
			cout << ans[i][j] << ", ";
		cout << endl;
	}
}

int main(){
	int T, tmp;
	cin >> T;
	vector<int> nums;
	while(T--){
		cin >> tmp;
		nums.push_back(tmp);
	}
	Solution(nums);
	return 0;
}
