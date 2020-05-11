/*
	Iterate throught the grid:
	If grid[i][j] = '1', set it to '0' and use DFS or BFS to set all nodes of the same island to zero
	Every new '1' makes count++

	Time complexity: O((n*m)^2)

	Disjoint set:
	Initialize all '1' node as a group, our goal is to find the actual number of groups in the grid
	Once there is a '1' adjacent to our current '1', we try to union them (we can only look for right and down)
	If they are in different groups, our initial number of groups - 1 and union them to the same group
	By doing so, a group of N members will -1*(N-1) and become one group
	Eventually, we can find how many disjoint sets are in the grid

	Time complexity: O(n*m)
*/
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

void travel(vector<vector<bool> > &visit, vector<vector<char> > &grid, int x, int y){
	int N = grid.size(), M = grid[0].size();
	
	if(x+1 < N && grid[x+1][y] == '1' && !visit[x+1][y]){
		visit[x+1][y] = true;
		travel(visit, grid, x+1, y);
	}
	if(y+1 < M && grid[x][y+1] == '1' && !visit[x][y+1]){
		visit[x][y+1] = true;
		travel(visit, grid, x, y+1);
	}
	if(x-1 >= 0 && grid[x-1][y] == '1' && !visit[x-1][y]){
		visit[x-1][y] = true;
		travel(visit, grid, x-1, y);
	}
	if(y-1 >= 0 && grid[x][y-1] == '1' && !visit[x][y-1]){
		visit[x][y-1] = true;
		travel(visit, grid, x, y-1);
	}
	return;
}

int Solution(vector<vector<char> > &grid){
	if(grid.empty())	return 0;
	int N = grid.size(), M = grid[0].size();
	vector<vector<bool> > visit(N, vector<bool>(M));
	int cnt = 0;
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			if(grid[i][j] == '1' && !visit[i][j]){
				cnt++;
				visit[i][j] = true;
				travel(visit, grid, i, j);
			}
		}
	}
	return cnt;
}

int Solution2(vector<vector<char> > &grid){
	if(grid.empty())	return 0;
	int N = grid.size(), M = grid[0].size();
	int cnt = 0;
	int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	queue<pair<int,int> > que;
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			if(grid[i][j] == '1'){
				cnt++;
				que.push(pair<int,int>(i,j));
				grid[i][j] = '0';
				while(!que.empty()){
					int x = que.front().first, y = que.front().second;
					for(int k=0; k<4; k++){
						int _x = x+dir[k][0], _y = y+dir[k][1];
						if(_x >= 0 && _x < N && _y >= 0 && _y < M && grid[_x][_y] == '1'){
							que.push(pair<int,int>(_x, _y));
							grid[_x][_y] = '0';
						}
					}
					que.pop();
				}
			}
		}
	}
	return cnt;
}

int find(int a, vector<int> &root){
	if(root[a] == a)	return a;
	return root[a] = find(root[a], root);
}

bool uni(int a, int b, vector<int> &root){
	int grp1 = find(a, root);
	int grp2 = find(b, root);
	if(grp1 != grp2){
		root[grp2] = grp1;
		return true;	
	}
	return false;
}

int Solution3(vector<vector<char> > &grid){
	if(grid.empty())	return 0;
	int cnt = 0, N = grid.size(), M = grid[0].size();
	vector<int> root(N*M);
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			if(grid[i][j] == '1'){
				cnt++;
				root[i*M+j] = i*M+j;	
			}
		}
	}
	int dir[2][2] = {{1, 0}, {0, 1}};
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			if(grid[i][j] == '1'){
				for(int k=0; k<2; k++){
					int x = i+dir[k][0], y = j+dir[k][1];
					if(x >= 0 && x < N && y >= 0 && y < M && grid[x][y] == '1'){
						cnt -= uni(i*M+j, x*M+y, root);
					}
				}
			}
		}
	}
	return cnt;
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<vector<char> > grid(n);
	for(int i=0; i<n; i++){
		vector<char> tmp(m);
		for(int j=0; j<m; j++)
			cin >> tmp[j];
		grid[i] = tmp;
	}
	cout << Solution(grid) << endl;
	//cout << Solution2(grid) << endl;
	cout << Solution3(grid) << endl;
}
