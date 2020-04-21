/*
	DP: 
	optimal substructure: mini_sum(i,j) = Min( mini_sum(i-1,j), mini_sum(i,j-1) ) + grid[i][j]
	mini_sum(0,0) = grid[0][0]
	
	Time complexity: O(n*m)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Solution(vector<vector<int> > &grid){
	if(grid.empty())	return 0;
	for(int i=0; i<grid.size(); i++){
		for(int j=0; j<grid[i].size(); j++){
			if(i == 0 && j == 0)	continue;
			else if(i == 0 && j != 0)	grid[i][j] += grid[i][j-1];
			else if(i != 0 && j == 0)	grid[i][j] += grid[i-1][j];
			else	grid[i][j] += min(grid[i-1][j], grid[i][j-1]);
		}
	}
	return grid.back().back();
}

int main(){
	int n, m, v;
	cin >> n >> m;
	vector<vector<int> > grid;
	for(int i=0; i<n; i++){
		vector<int> tmp;
		for(int j=0; j<m; j++){
			cin >> v;
			tmp.push_back(v);
		}
		grid.push_back(tmp);
	}
	cout << Solution(grid) << endl;
	return 0;
}
