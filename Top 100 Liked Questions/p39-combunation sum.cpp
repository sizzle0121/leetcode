/*
**	backtracking: O(n*m) 
	sort the array first
	at each position, try evry number
	be aware of the repeated combination, try the numbers with index >= last position

**	DP: O(n*m)
	sort the array first
	iterate all candidates[i] (i from 0 to T-1)
	calculate the combinations of candidates[i] to target (j: candidates[i] to target)
	comb[0] = 1;
	comb[j] = comb[j - candidates[i]] + 1;	(former combination plus candidates[i] itsself)
	push (j-candidates[i])'s combination list + candidates[i] to j's combination list
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void backtrack(vector<vector<int> > &ans, vector<int> &tmp, vector<int> &c, int target, int pos){
	if(target == 0){
		ans.push_back(tmp);
		return;
	}

	for(int i=pos; i<c.size(); i++){
		if(target - c[i] >= 0){
			tmp.push_back(c[i]);
			backtrack(ans, tmp, c, target-c[i], i);
			tmp.pop_back();
		}else{
			return ;
		}
	}
}

void Solution(vector<int> &candidates, int target){
	if(candidates.empty())	return;

	sort(candidates.begin(), candidates.end());
	vector<vector<int> > ans;
	vector<int> tmp;
	backtrack(ans, tmp, candidates, target, 0);
	
	for(int i=0; i<ans.size(); i++){
		for(int j=0; j<ans[i].size(); j++)
			cout << ans[i][j] << " ";
		cout << endl;
	}
}

int main(){
	int T, tmp;//T: number of input
	int target;
	cin >> T;

	vector<int> candidates;
	while(T--){
		cin >> tmp; 
		candidates.push_back(tmp);
	}
	cin >> target;
	Solution(candidates, target);

	return 0;
}
