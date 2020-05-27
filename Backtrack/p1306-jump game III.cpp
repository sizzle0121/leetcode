/*
 * DP (bottom-up):
 * Scan through the array, and at each node, jump to i+arr[i], i-arr[i] and see if the destinations are zero\ 
 * if not, scan to i+1
 * if yes, change arr[i] to zero (represents if we can reach this node, we can reach the zero node)
 * Repeat scanning the array and update arr[i] if it can reach any zero, if i == start -> return true
 * Once we didn't update any arr[i] to zero in a scanning round, and arr[start] is still not zero -> return false
 *
 * Time complexity: O(n^2)
 * 
 * 
 * BFS (backtracking + pruning):
 * Starting from arr[start],\ 
 * if arr[que.front()] != 0, push all nodes (at most 2) the que.front() can reach && not haven't been visited before into queue, also, mark those nodes as visited
 * if arr[qur.front()] == 0, return true
 *
 * Time complexity: O(2^n), even if we've marked nodes avoiding re-visit, but for each node, we still need to check both sides of jumping
 *
 * */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool Solution(vector<int> &arr, int start){
	bool flag;
	int N = arr.size();
	while(1){
		flag = false;
		for(int i=0; i<N; i++){
			if(arr[i] != 0){
				if(i+arr[i] < N && arr[i+arr[i]] == 0){
					arr[i] = 0;
					flag = true;
				}
				if(i-arr[i] >= 0 && arr[i-arr[i]] == 0){
					arr[i] = 0;
					flag = true;
				}
			}
			if(arr[i] == 0 && i == start) return true;
		}
		if(!flag) return false;
	}
	return false;
}

bool Solution2(vector<int> arr, int start){
	queue<int> que;
	que.push(start);
	int N = arr.size();
	vector<bool> visited(N);
	visited[start] = true;
	while(!que.empty()){
		int tmp = que.front();
		que.pop();
		if(arr[tmp] == 0) return true;
		else{
			if(tmp + arr[tmp] < N && !visited[tmp + arr[tmp]]){
				que.push(tmp + arr[tmp]);
				visited[tmp + arr[tmp]] = true;
			}
			if(tmp - arr[tmp] >= 0 && !visited[tmp - arr[tmp]]){
				que.push(tmp - arr[tmp]);
				visited[tmp - arr[tmp]] = true;
			}
		}
	}
	return false;
}

int main(){
	int T, start;
	cin >> T;
	vector<int> arr(T);
	for(auto &a: arr)
		cin >> a;
	cin >> start;
	cout << Solution2(arr, start) << endl;
	cout << Solution(arr, start) << endl;
}
