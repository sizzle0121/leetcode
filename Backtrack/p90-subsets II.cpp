/*
 * Backtrack (by level, Solution1):
 * too complicated, not a prefered approach
 * 
 *
 * Enumeration (generate by previous subsets):
 * If no duplicate, for each number, we can either pick it or not
 * The duplicate numbers can be viewed as for the same number, we can either pick n, n-1, n-2, ..., 1, 0 of it
 * Therefore, we count the number and append (1 - n) of it to the previous generated subsets\ 
 * then push them into the answer
 * The previous generated subsets are those don't contain the current number
 *
 * Time complexity: O((n1+1)(n2+1)...(nk+1)), ni: the count of each number in the array
 * Space complexity: O(1)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void backtrack(int len, int curlv, vector<vector<int> > &ans, vector<int> &cur, vector<int> &lev, vector<int> &nums){
	if(curlv >= lev.size()) return;

	int curNum = nums[lev[curlv]];
	for(int i=lev[curlv]; i<nums.size(); ++i){
		if(nums[i] != curNum){
			while(!cur.empty() && cur.back() == curNum){
				for(int lv=1; lv<lev.size(); ++lv)
					backtrack(len, curlv+lv, ans, cur, lev, nums);
				cur.pop_back();
			}
			return;
		}
		if(cur.size() < len){
			cur.push_back(nums[i]);
		}
		if(cur.size() == len){
			ans.push_back(cur);
			while(1){
				cur.pop_back();
				if(cur.empty() || cur.back() != curNum) return;
				for(int lv=1; lv<lev.size(); ++lv)
					backtrack(len, curlv+lv, ans, cur, lev, nums);
			}
			return;
		}
	}
	while(!cur.empty() && cur.back() == curNum)
		cur.pop_back();
}

vector<vector<int> > Solution(vector<int> &nums){
	int N = nums.size();
	sort(nums.begin(), nums.end());
	vector<int> lev;
	lev.push_back(0);
	for(int i=1; i<N; ++i){
		if(nums[i] != nums[i-1])
			lev.push_back(i);
	}
	vector<vector<int> > ans;
	ans.push_back(vector<int>());
	for(int i=1; i<=N; ++i){
		for(int j=0; j<lev.size(); ++j){	
			vector<int> cur;
			int z = ans.size();
			backtrack(i, j, ans, cur, lev, nums);
			if(ans.size() == z) break;
		}
	}
	return ans;
}

vector<vector<int> > Solution2(vector<int> &nums){
	int N = nums.size();
	sort(nums.begin(), nums.end());
	int idx = 0;
	vector<vector<int> > ans{{}};
	while(idx < N){
		int cnt = 0;
		for(int i=idx; i<N; ++i){
			if(nums[i] == nums[idx]) cnt++;
			else break;
		}
		int n = ans.size();
		for(int i=0; i<n; ++i){
			vector<int> tmp(ans[i]);
			for(int j=0; j<cnt; ++j){
				tmp.push_back(nums[idx]);
				ans.push_back(tmp);
			}
		}
		idx += cnt;
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(auto &num: nums)
		cin >> num;
	vector<vector<int> > ans = Solution2(nums);
	for(int i=0; i<ans.size(); ++i){
		for(int j=0; j<ans[i].size(); ++j)
			cout << ans[i][j] << " ";
		cout << endl;
	}
}
