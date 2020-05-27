/*
 * Priority Queue + BFS:
 * Inspiration from "Trapping Rain Water":
 * 1. we need to define a container to hold the water
 * 2. the maximum volume of water the conatiner can hold is determined by the minimum boundary of it
 * 3. If the minimum boundary of the container is larger than before, update the maximum volume of water it can hold
 * (since 3, we should start from the minimum height to see if we can update the volume,\ 
 * if the height is less than the volume height, then add the difference to the answer)
 * (also, we can determine the water of the height near by and less than the minimum boundary, so does the height near by it
 * so we should always start from the minimum height)
 *
 * For this version 2, the container starts from a rectangle (instead of two bars/sides)\ 
 * the maximum volume of water it can hold is determined by the minimum height of the container
 * Since the container consists of multiple heights instead of only two heights, we need a priority queue to extract the minimum of them efficiently
 * Additionally, to see if we can update the maximum volume or add some volume to the answer, we should explore all the heights near by the current minimum height in the priority queue\ 
 * therefore, we traverse the map by a BFS way (push all neighborhood into the queue)
 *
 * Time complexity: O(n * m * log(n*m))
 * Space complexity: O(n * m)
 *
 * */
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

struct cmp{
	bool operator()(const pair<int,pair<int,int> > &a, const pair<int,pair<int,int> > &b){
		return a.first > b.first;
	}
};

int Solution(vector<vector<int> > &heightMap){
	int N = heightMap.size(), M = heightMap[0].size();
	priority_queue<pair<int,pair<int,int> >, vector<pair<int,pair<int,int> > >, cmp> pq;
	//pair(height, pair(n, m))
	for(int i=0; i<N; i++){
		pq.push(pair<int,pair<int,int> >(heightMap[i][0], pair<int,int>(i, 0)));
		pq.push(pair<int,pair<int,int> >(heightMap[i][M-1], pair<int,int>(i, M-1)));
		heightMap[i][0] = -1;
		heightMap[i][M-1] = -1;
	}
	for(int i=0; i<M; i++){
		pq.push(pair<int,pair<int,int> >(heightMap[0][i], pair<int,int>(0, i)));
		pq.push(pair<int,pair<int,int> >(heightMap[N-1][i], pair<int,int>(N-1, i)));
		heightMap[0][i] = -1;
		heightMap[N-1][i] = -1;
	}
	
	int ans = 0, container_min = -1;
	int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	while(!pq.empty()){
		int curH = pq.top().first, x = pq.top().second.first, y = pq.top().second.second;
		if(curH > container_min) container_min = curH;
		pq.pop();
		heightMap[x][y] = -1;
		for(int i=0; i<4; i++){
			int x_ = x+dir[i][0], y_ = y+dir[i][1]; 
			if(x_ >= 0 && x_ < N && y_ >= 0 && y_ < M && heightMap[x_][y_] != -1){
				if(heightMap[x_][y_] < container_min) ans += container_min - heightMap[x_][y_];
				pq.push(pair<int,pair<int,int> >(heightMap[x_][y_], pair<int,int>(x_, y_)));
				heightMap[x_][y_] = -1;
			}
		}
	}
	return ans;
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<vector<int> > heightMap(n, vector<int>(m));
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			cin >> heightMap[i][j];
	cout << Solution(heightMap) << endl;
}
