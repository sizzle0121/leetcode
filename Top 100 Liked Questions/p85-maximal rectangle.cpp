/*
 * Stack (Inspired by p84):
 * To be updated.
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
