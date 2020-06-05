/*
 * To be updated
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Solution(vector<vector<int> > &grid){
	if(grid.empty()) return 0;
	int N = grid.size(), ans = 0;
	if(grid[0][0] == -1 || grid[N-1][N-1] == -1) return 0;
	vector<vector<int> > dp(N, vector<int>(N, -1));
	dp[0][0] = grid[0][0];
	for(int step=1; step<(N+N-1); step++){
		for(int i=N-1; i>=0; --i){
			if(step-i >= 0 && step-i < N && grid[i][step-i] != -1){
				for(int j=i; j>=0; --j){
					if(step-j >= 0 && step-j < N && grid[j][step-j] != -1){
						//[i][step-i], [j][step-j]
						int tmp = -1;
						if(i-1 >= 0 && j-1 >= 0 && dp[i-1][j-1] != -1) tmp = max(tmp, dp[i-1][j-1]);
						if(i-1 >= 0 && dp[i-1][j] != -1) tmp = max(tmp, dp[i-1][j]);
						if(j-1 >= 0 && dp[i][j-1] != -1) tmp = max(tmp, dp[i][j-1]);
						if(dp[i][j] != -1) tmp = max(tmp, dp[i][j]);
						if(tmp != -1){	
							if(i != j) dp[i][j] = grid[i][step-i] + grid[j][step-j] + tmp;
							else dp[i][j] = grid[i][step-i] + tmp;
						}
					}else{
						dp[i][j] = -1;
					}
				}
			}else{
				for(int j=i; j>=0; --j)
					dp[i][j] = -1;
			}
		}
/*
		cout << "step " << step << ":\n";
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++)
				cout << dp[i][j] << " ";
			cout << endl;
		}
		cout << endl;
*/
	}
	return (dp[N-1][N-1] != -1)? dp[N-1][N-1] : 0;
}

int main(){
	int n;
	cin >> n;
	vector<vector<int> > grid(n, vector<int>(n));
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			cin >> grid[i][j];
	cout << Solution(grid) << endl;
}
