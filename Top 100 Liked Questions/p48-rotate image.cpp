/*
	Rotate it ring by ring, 4 points by 4 points
	space complexity: O(1)
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void Solution(vector<vector<int> > &matrix){
	if(matrix.empty())	return;
	int lev = 0;
	int n = matrix[0].size();
	while((n - lev*2) > 1){
		for(int i=0; i<(n-lev*2)-1; i++){
			swap(matrix[lev][lev+i], matrix[n-1-lev-i][lev]);//left
			swap(matrix[n-1-lev-i][lev], matrix[n-1-lev][n-1-lev-i]);//bottom
			swap(matrix[n-1-lev][n-1-lev-i], matrix[lev+i][n-1-lev]);//right
		}
		lev++;
	}
	
	for(int i=0; i<matrix.size(); i++){
		for(int j=0; j<matrix[i].size(); j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}

}

int main(){
	int n, tmp;
	cin >> n;
	vector<vector<int> > matrix;
	for(int i=0; i<n; i++){
		vector<int> row;
		for(int j=0; j<n; j++){
			cin >> tmp;
			row.push_back(tmp);
		}
		matrix.push_back(row);
	}
	Solution(matrix);
	return 0;
}
