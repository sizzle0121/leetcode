/*
 * Backtrack:
 * Start from 1 to 9, iterate all possible combinations
 * Valid combinations should (1) size == k (2) sum == n
 * If size already equals to k, but sum still < n, return
 * If size < k, but sum already >= n, return
 * otherwise, continue to explore or push the current combination into the answer array
 *
 * Time complexity: O(2^9)
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

void backtrack(vector<vector<int> > &ans, vector<int> &cur, int icur, int sum, int k, int n){
	if(cur.size() == k) return;
	for(int i=icur; i<=9; i++){
		if(sum + i < n){
			cur.push_back(i);
			backtrack(ans, cur, i+1, sum+i, k, n);
			cur.pop_back();
		}else if(sum + i == n && cur.size()+1 == k){
			cur.push_back(i);
			ans.push_back(cur);
			cur.pop_back();
			return;
		}else return;
	}
}

vector<vector<int> > Solution(int k, int n){
	vector<vector<int> > ans;
	if(k > 9 || n > 45) return ans;
	vector<int> cur;
	backtrack(ans, cur, 1, 0, k, n);
	return ans;
}

int main(){
	int k, n;
	cin >> k >> n;
	vector<vector<int> > ans = Solution(k, n);
	for(auto &a: ans){
		for(auto &aa: a)
			cout << aa << " ";
		cout << endl;
	}
}
