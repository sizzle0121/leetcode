/*
	Sol.1  Brute-force:
	Iterate through the matrix and look for the target
	Time complexity: O(n*m) -> TLE

	Sol.2  Search from Top Side to Left Side:
	Set a vertical bound (= 0) and a horizontal bound (= matrix[0].size(); rightmost)
	The position (x, y), x should > vertical bound, and y should < horizontal bound
	Each time when we find matrix[x][y] > target\ 
	We move the vertical bound to y, and the horizontal bound to x
	Then start searching from matrix[y][0]
	By shrinking the matrix and search, we can finally find our target if it exists

	Time complexity: O(m(m+1)/2)

	Sol.3  (Binary Search)Search from the Top-Right corner:
	Starting from the top-right corner\ 
	If the target < it, we then move our horizontal bound from column(m) to column(m-1)
		(since the elements of the rightmost column will all greater than the target)
	If the target > it, we then move our vertical bound from row(0) to row(1)
		(since the elements of the topmost column will all smaller than the target)
	Each time after we update one of the bound, we start from the new top-right corner and repeat the above steps
	Eventually, we are able to find the target if it exists

	Time complexity: O(n+m)
*/
#include <iostream>
#include <vector>
using namespace std;

bool DFS(int x, int y, vector<vector<int> > &matrix, vector<vector<bool> > &visited, int target){
	visited[x][y] = true;
	if(target == matrix[x][y])	return true;
	if(target > matrix[x][y]){
		if(y+1 < matrix[0].size() && !visited[x][y+1] && DFS(x, y+1, matrix, visited, target))	return true;
		if(x+1 < matrix.size() && !visited[x+1][y] && DFS(x+1, y, matrix, visited, target))	return true;
	}else if(target < matrix[x][y]){
		if(y-1 >= 0 && !visited[x][y-1] && DFS(x, y-1, matrix, visited, target))	return true;
		if(x-1 >= 0 && !visited[x-1][y] && DFS(x-1, y, matrix, visited, target))	return	true;
	}
	return false;
}

bool Solution(vector<vector<int> > &matrix, int target){
	if(matrix.empty() || matrix[0].empty())	return false;
	int N = matrix.size(), M = matrix[0].size();
	vector<vector<bool> > visited(N, vector<bool>(M));
	return DFS(0, 0, matrix, visited, target);
}

bool Solution2(vector<vector<int> > &matrix, int target){
	if(matrix.empty() || matrix[0].empty())	return false;
	int N = matrix.size(), M = matrix[0].size();
	int hb = M, vb = 0;
	// >= vb, < hb
	int x = 0, y = 0;
	while(!(vb > N-1) && !(hb < 1)){
		if(matrix[x][y] == target)	return true;
		else if(matrix[x][y] < target){
			if(y+1 < hb)	y++;
			else if(x+1 < N) x++;
			else	return false;
		}else if(matrix[x][y] > target){
			hb = y;
			vb = x;
			x = vb;
			y = 0;
		}
	}
	return false;
}

bool Solution3(vector<vector<int> > &matrix, int target){
	if(matrix.empty() || matrix[0].empty())	return false;
	int N = matrix.size(), M = matrix[0].size();
	int x = 0, y = M-1;
	while(x < N && y >= 0){
		if(target == matrix[x][y])	return true;
		else if(target < matrix[x][y]){
			y--;
		}else if(target > matrix[x][y]){
			x++;
		}
	}
	return false;
}

int main(){
	int n, m, target;
	cin >> n >> m;
	vector<vector<int> > matrix(n, vector<int>(m));
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			cin >> matrix[i][j];
	cin >> target;
	cout << Solution3(matrix, target) << endl;
}
