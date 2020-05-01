/*
	Brute-force:
		Enumerate all possible length (start from the smaller length of the matrix)
		Check the square of the length is all composed with '1'
		If not, check shorter length

	Time complexity: O((m*n)^2)

	DP:
		Bigger square is formed by smaller square appended with two additional sides of '1'
		Let dp(i, j) be the maximal length of the square ended with the bottom-right point (i, j)
		If one of matrix(i-1,j), matrix(i-1,j-1), matrix(i,j-1) is '0', dp(i,j) must be 0+1 (itself can be a square with area 1)
		If all of them are '1', dp(i, j) wil be the smallest of their dp value, since the square is determined by the shortest length
		The above is our one-step difference between i, i-1 (here is 2-D), so we need j-1, (i-1, j-1), and now we have the optimal substructure
		By repeating so and update the maximal square area, we can obtain the answer by scanning the matrix once

	Time complexity: O(n*m)

*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Solution(vector<vector<char> > &matrix){
	if(matrix.empty())	return 0;
	int N = matrix.size(), M = matrix[0].size();
	vector<vector<int> > dp(N, vector<int>(M));
	int ans = 0;
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			if(matrix[i][j] == '1'){
				int tmp1 = (i-1 >= 0)? dp[i-1][j] : 0;
				int tmp2 = (j-1 >= 0)? dp[i][j-1] : 0;
				int tmp3 = (i-1 >= 0 && j-1 >= 0)? dp[i-1][j-1] : 0;
				tmp1 = min(tmp1, tmp2);
				dp[i][j] = min(tmp1, tmp3) + 1;
				ans = max(dp[i][j], ans);
			}
		}
	}
	return ans;
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<vector<char> > matrix(n, vector<char>(m));
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++)
			cin >> matrix[i][j];
	}
	cout << Solution(matrix) << endl;
}
