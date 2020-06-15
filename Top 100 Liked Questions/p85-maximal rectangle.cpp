/*
 * Stack (Inspired by p84):
 * For every row, we calculate the heights for matrix[i][j] (If matrix[i][j] == '1' -> the height of the top + 1)
 * Then calculate the largest rectangle for this row by using the method of calculating the largest rectangle of histograms
 *
 *
 * Process of thinking:
 * First I thought to use DP\ 
 * If we let dp[i][j] be the bottom-right corner of the largest rectangle\ 
 * however, there is no relation of transition from the previous largest area to the current dp[i][j] (no overlap)
 * For example,
 * 0 0 0   1    1
 * 0 0 0   1    1
 * 1 1 1 "#1" "@1"
 *
 * For #1, the largest rectangle is the horizontal four 1s
 * But for @1, the largest rectangle is the six 1s at the right -> didn't use the previous largest area
 *
 * What if we record the heights and width in dp[i][j], similarly, what we should record depends on the later i, j\ 
 * so still doesn't work
 *
 * Then I turn into think about fix the height and let the dp[i][j] represents the largest rectangle\ 
 * the heights at j can make (the height must be heights[j])
 * Now the subproblems overlap! since the current height can make a larger rectangle if previous heights >= current height\ 
 * and if previous heights < current height, then that will be the left boundary of the largest rectangle with current height
 * Then the answer will be max(dp[i][j]), i: 0 to N-1, j: 0 to M-1
 * At the meantime, I recognize that this is exactly the way we used to solve p84
 *
 * Time complexity: O(n * m)
 * Space complexity: O(n * m)
 *
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

int Solution(vector<vector<char> > &matrix){
	if(matrix.empty()) return 0;
	int N = matrix.size(), M = matrix[0].size(), ans = 0;
	vector<vector<int> > heights(N, vector<int>(M));
	stack<int> left;
	for(int i=0; i<N; ++i){
		for(int j=0; j<M; ++j){
			if(matrix[i][j] == '1'){
				if(i-1 >= 0) heights[i][j] = heights[i-1][j] + 1;
				else heights[i][j] = 1;
			}
			while(!left.empty() && heights[i][left.top()] > heights[i][j]){
				int h = heights[i][left.top()];
				left.pop();
				int l = left.empty()? -1 : left.top();
				ans = max(ans, h * (j - l - 1));
			}
			left.push(j);
		}
		while(!left.empty()){
			int h = heights[i][left.top()];
			left.pop();
			int l = left.empty()? -1 : left.top();
			ans = max(ans, h * (M - l - 1));
		}
	}
	return ans;
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<vector<char> > matrix(n, vector<char>(m));
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			cin >> matrix[i][j];
	cout << Solution(matrix) << endl;
}
