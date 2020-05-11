/*
	DP:
	optimal substructure: paths(i, j) = paths(i-1, j) + paths(i, j-1)
	Time Complexity: O(n*m)

*/

#include <iostream>

using namespace std;

int Solution(int m, int n){
	int grid[n][m];
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			grid[i][j] = 0;
	grid[0][0] = 1;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(i-1 >= 0)	grid[i][j] += grid[i-1][j];
			if(j-1 >= 0)	grid[i][j] += grid[i][j-1];
		}
	}
	return grid[n-1][m-1];
}

int main(){
	int m, n;
	cin >> m >> n;
	cout << Solution(m, n) << endl;
	return 0;
}
