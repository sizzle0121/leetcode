/*
**	brute-force: O(n^3)

**	fix one, and then solve 2 sum problem: O(n^2)

**	fix one, and then use two pointers
	save the time of unnecessary combinations in brute-force method
	pf:	too large -> must right--
		too less -> must left++
		no reverse -> reverse is equal to the wrong direction of the last move

*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void Solution1(vector<int> &nums){
	//solution based on 2 sum
	sort(nums.begin(), nums.end());
    vector<vector<int> > ans;
	vector<int> tmp(3);//for push back
	unordered_map<int, int> hashTab;
	for(int i=0; i<nums.size(); i++){
		if(hashTab.find(nums[i]) != hashTab.end())  hashTab[nums[i]]++;
		else    hashTab[nums[i]] = 0;
	}
	
	for(int i=0; i<nums.size(); i++){
		if(i>0 && nums[i] == nums[i-1])	continue;
		else if(nums[i] > 0)	continue;
		for(int j=i+1; j<nums.size(); j++){
			if(nums[j] == nums[j-1] && j > i+1)	continue;
			int target = -(nums[i] + nums[j]);
			if(hashTab.find(target) != hashTab.end()){
				if((target == nums[j] && hashTab[target]) || target > nums[j]){
					if(target == 0 && hashTab[target] < 2)	continue;
					tmp[0] = nums[i];
					tmp[1] = nums[j];
					tmp[2] = target;
					ans.push_back(tmp);
				}
			}
		}

	}

	for(int i=0; i<ans.size(); i++){
		for(int j=0; j<ans[i].size(); j++){
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}
}

void  Solution2(vector<int> &nums){
	//solution based on two pointers
	sort(nums.begin(), nums.end());
	vector<vector<int> > ans;
	vector<int> tmp(3);
	for(int i=0; i<nums.size(); i++){
		if(i > 0 && nums[i] == nums[i-1])	continue;
		int l = i+1, r = nums.size()-1;
		while(l < r){
			int sum = nums[i] + nums[l] + nums[r];
			if(sum == 0){
				tmp[0] = nums[i];
				tmp[1] = nums[l];
				tmp[2] = nums[r];
				ans.push_back(tmp);
				r--;
				l++;
			}else if(sum > 0){
				r--;
			}else{
				l++;
			}
			while(r+1 < nums.size() && nums[r] == nums[r+1] && r > l)	r--;
			while(l-1 > i && nums[l] == nums[l-1] && l < r)	l++;
		}
	}
	for(int i=0; i<ans.size(); i++){
		for(int j=0; j<ans[i].size(); j++){
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}
}


int main(){
	int T, ipt;//size of the input array
	vector<int> nums;
	cin >> T;
	while(T--){
		cin >> ipt;
		nums.push_back(ipt);
	}
	cout << "Solution 1:\n";
	Solution1(nums);
	cout << "Solution 2:\n";
	Solution2(nums);
	return 0;
}
