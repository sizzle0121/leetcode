/*
 * DP:
 * Let dp[i][j] be denoted as the minimum HP should be given if we start from dungeon[i][j] to the bottom-right cell
 *
 * One-step difference (also the optimal substructure):
 * dp[i][j] will be the more negative one of 1) dungeon[i][j] itself and 2) dungeon[i][j] + max(dp[i+1][j], dp[i][j+1])
 * For 2), it's the minimum HP required for starting from dungeon[i][j] to the target (the minimum of the whole path)
 * For 1), if it's more negative, we need to give the prince a minimum HP to prevent him from dying at the beginning
 * However, if both 1) and 2) are >= 0, we can let dp[i][j] become any non-negative number\ 
 *
 * Why?
 * Consider its left or top is a negative number, it will increase them, but we still need abs(the negative number) + 1 to prevent the prince from dying at the beginning
 * And, if it's left or top is a non-negative number, the minimum HP for them will still be 1
 * Therefore, if both 1) and 2) >= 0, the dp[i][j] won't affect the following procedure as long as it's a non-negative number
 *
 * Time complexity: O(n * m)
 * Space complexity: O(n * m)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Solution(vector<vector<int> > &dungeon){
	if(dungeon.empty()) return 1;
	int N = dungeon.size(), M = dungeon[0].size();
	vector<vector<int> > dp(N, vector<int>(M));
	dp[N-1][M-1] = dungeon[N-1][M-1];
	for(int i=N-1; i>=0; --i){
		for(int j=M-1; j>=0; --j){
			if(i+1 < N && j+1 < M){
				int tmp = dungeon[i][j] + max(dp[i+1][j], dp[i][j+1]);
				if(dungeon[i][j] >= 0 && tmp >= 0) dp[i][j] = tmp;
				else dp[i][j] = min(dungeon[i][j], tmp);
			}else if(i+1 < N){
				int tmp = dungeon[i][j] + dp[i+1][j];
				if(dungeon[i][j] >= 0 && tmp >= 0) dp[i][j] = tmp;
				else dp[i][j] = min(dungeon[i][j], tmp);
			}else if(j+1 < M){
				int tmp = dungeon[i][j] + dp[i][j+1];
				if(dungeon[i][j] >= 0 && tmp >= 0) dp[i][j] = tmp;
				else dp[i][j] = min(dungeon[i][j], tmp);
			}
		}
	}
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++)
			cout << dp[i][j] << " ";
		cout << endl;
	}
	return (dp[0][0] >= 0)? 1 : abs(dp[0][0])+1;
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<vector<int> > dungeon(n, vector<int>(m));
	for(auto &d: dungeon)
		for(auto &dd: d)
			cin >> dd;
	cout << Solution(dungeon) << endl;
}
