/*
 * Backtrack:
 * To avoid duplicate permutations, we should iterate through different kinds of numbers instead of indices\ 
 * for each digit
 * Also notice the total counts of numbers in the input
 * and the remain is simply doing backtrack
 *
 * Time complexity: O(n!)
 *
 * */
#include <iostream>
#include <vector>
#include <map>
using namespace std;

void backtrack(vector<vector<int> > &ans, map<int,int> &cnt, vector<int> &cur, int N){
	if(N == 0){
		ans.push_back(cur);
		return;
	}

	for(auto &itr: cnt){
		if(itr.second > 0){
			itr.second--;
			cur.push_back(itr.first);
			backtrack(ans, cnt, cur, N-1);
			cur.pop_back();
			itr.second++;
		}
	}
}

vector<vector<int> > Solution(vector<int> &nums){
	vector<vector<int> > ans;
	if(nums.empty()) return ans;
	map<int,int> cnt;
	for(auto &num: nums)
		cnt[num]++;
	vector<int> cur;
	int N = nums.size();
	backtrack(ans, cnt, cur, N);
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(auto &num: nums)
		cin >> num;
	vector<vector<int> > ans = Solution(nums);
	for(int i=0; i<ans.size(); i++){
		for(int j=0; j<ans[i].size(); j++)
			cout << ans[i][j] << " ";
		cout << endl;
	}
}
