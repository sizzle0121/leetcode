/*
 * DP:
 * Similar as "unique path" but to notice the edge case\ 
 * (top & left borders)
 *
 * Time complexity: O(n * m)
 * Space complexity: O(n * m), could be O(1) if use the input array as path counts array\ 
 * and if obstacleGrid[i][j] == 1, set it to 0 (won't add obstacles to the counts because top and left are the paths we've iterated through) 
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

int Solution(vector<vector<int> > &obstacleGrid){
	int n = obstacleGrid.size();
	if(n == 0) return 0;
	int m = obstacleGrid[0].size();
	if(m == 0) return 0;
	vector<vector<int> > ans(n, vector<int>(m));
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(obstacleGrid[i][j] == 0){
				if(i-1 >= 0 && j-1 >= 0) ans[i][j] = ans[i-1][j] + ans[i][j-1];
				else if(i-1 < 0 && j-1 < 0) ans[i][j] = 1;
				else if(i-1 < 0) ans[i][j] = ans[i][j-1];
				else ans[i][j] = ans[i-1][j];
			}
		}
	}
	return ans[n-1][m-1];
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<vector<int> > obstacleGrid(n, vector<int>(m));
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			cin >> obstacleGrid[i][j];
	cout << Solution(obstacleGrid) << endl;
}
