/*
 * Backtrack:
 * Start from 1 to n, itreate all possible combinations
 * When go to next level of recursion, start from i+1 to n
 *
 * Time complexity: O(n^min{k, n-k})
 * 
 * for k <= n-k
 * n! / ((n-k)!k!) = ((n-k+1) (n-k+2) (n-k+3) ... n ) / k!
 * -> (n^k + O(n^(k-1))) / k!
 * -> O(n^k)
 *
 * for k > n-k
 * get O(n^(n-k))
 *
 * Therefore, O(n^min{k, n-k})
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

void backtrack(vector<vector<int> > &ans, int n, vector<int> &cur, int icur, int k){
	if(cur.size() == k){
		ans.push_back(cur);
		return;
	}
	for(int i=icur; i<=n; i++){
		cur.push_back(i);
		backtrack(ans, n, cur, i+1, k);
		cur.pop_back();
	}
}

vector<vector<int> > Solution(int n, int k){
	vector<vector<int> > ans;
	if(k > n) return ans;
	vector<int> cur;
	backtrack(ans, n, cur, 1, k);
	return ans;
}

int main(){
	int n, k;
	cin >> n >> k;
	vector<vector<int> > ans = Solution(n, k);
	for(auto &a: ans){
		for(auto &aa: a)
			cout << aa << " ";
		cout << endl;
	}
}
