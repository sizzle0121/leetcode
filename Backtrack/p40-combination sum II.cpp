/*
 * Backtrack:
 * The main idea is to visit all possible combinations and avoid duplicate combinations
 * Sort the array first will speed up the backtracking process\ 
 * since we can simply return when the current sum is already greater than or equal to the target
 * About avoiding duplicate combinations, we should keep in mind that for duplicate numbers in the array,\ 
 * the exploration of the first number of them will cover that of the others\ 
 * so when the exploration returns, we have to skip all duplicate numbers, ans then continue our exploration
 *
 * Time complexity: O(2^n)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void backtrack(vector<vector<int> > &ans, vector<int> &cur, vector<int> &candidates, int icur, int sum, int target){
	for(int i=icur; i<candidates.size(); ){
		if(candidates[i] + sum < target){
			cur.push_back(candidates[i]);
			backtrack(ans, cur, candidates, i+1, candidates[i]+sum, target);
			cur.pop_back();
			while(i+1<candidates.size() && candidates[i+1] == candidates[i]) i++;//skip duplicatenumbers when the exploration return
			i++;
		}else if(candidates[i] + sum == target){
			cur.push_back(candidates[i]);
			ans.push_back(cur);
			cur.pop_back();
			return;
		}else{
			return;
		}
	}
}

vector<vector<int> > Solution(vector<int> &candidates, int target){
	vector<vector<int> > ans;
	if(candidates.empty()) return ans;
	sort(candidates.begin(), candidates.end());
	vector<int> cur;
	backtrack(ans, cur, candidates, 0, 0, target);
	return ans;
}

int main(){
	int T, target;
	cin >> T;
	vector<int> candidates(T);
	for(auto &c: candidates)
		cin >> c;	
	cin >> target;
	vector<vector<int> > ans = Solution(candidates, target);
	for(auto &a: ans){
		for(auto &aa: a)
			cout << aa << " ";
		cout << endl;
	}
}
