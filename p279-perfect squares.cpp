/*
	DP:
	One-Step difference: count(i) = count(i-Square[j]) + 1
	If we start from 1 to n, and calculate the least steps for each number
	Then it will be least_count(i) = min( least_count(i - Square[j]) + 1 )
	The above is our Optimal substructure

	Time complexity: O(n * sqrt(n))

	BFS:
	We can view the first layer consisting of the nodes which can be reached by using only one square number, the second layer consisting of the nodes which can be reached by using exactly two square numbers, ...
	Therefore, first, we push all square numbers into queue, and their count(i) = 1(they are all at the first layer, since they can be reached by themselves)
	For each que.front(), we add a square number to the node[que.front() + square[j]], if it hasn't been visited yet, assign its count to k=2 (they are at layer 2), and push it into the queue
	If we still have not reached n, we then go to layer k+1, and do the above things until we reach n and return k
	
	Time complexity: O(sqrt(n)^3), but avg. is O(sqrt(n)) or O(n)

*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int Solution2(int n){
	queue<int> que;
	vector<int> squares;
	vector<int> cnt(n+1);
	int curCnt = 1;
	for(int i=1; i*i<=n; i++){
		if(n == i*i)	return curCnt;
		squares.push_back(i*i);
		cnt[i*i] = curCnt;
		que.push(squares.back());
	}
	while(!que.empty()){
		curCnt++;
		int N = que.size();
		for(int i=0; i<N; i++){
			int node = que.front();
			que.pop();
			for(int j=0; j<squares.size(); j++){
				if(node + squares[j] == n)	return curCnt;
				else if(node + squares[j] < n && cnt[node + squares[j]] == 0){
					cnt[node + squares[j]] = curCnt;
					que.push(node + squares[j]);
				}else if(node + squares[j] > n){
					break;
				}
			}
		}
	}
	return 0;
}

int Solution(int n){
	vector<int> squares;
	for(int i=1; i*i<=n; i++){
		squares.push_back(i*i);
	}
	vector<int> dp(n+1);
	dp[1] = 1;
	for(int i=2; i<=n; i++){
		for(int j=0; j<squares.size() && squares[j] <= i; j++){
			if(dp[i] == 0)	dp[i] = dp[i-squares[j]] + 1; 
			else	dp[i] = min(dp[i], dp[i-squares[j]]+1);
		}
	}
	return dp[n];
}

int main(){
	int n;
	cin >> n;
	cout << Solution2(n) << endl;
}
