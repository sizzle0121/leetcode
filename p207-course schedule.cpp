/*
	Like topology sort, if the graph has ring, then it's impossible to finish all courses
	BFS Approach:
		We record the number of links link to each node
		Then start from the nodes no one link to, push them into queue
		Each round of the que.front, we remove the edge it links to
		After that, if the node it links to has no other link to it, it will be push into queue
		By repeating so, if the number of nodes we push into queue match the numCourses, return true, otherwise, return false
	Time complexity: O(V*E), where V is the number of nodes, E is the number of edges
	
	DFS Approach:
		Similarly, we start from the nodes no one link to
		Each round of DFS, we remove the edges current node links to, if after removing the edge, the other node has no one links to it, we go deep into it and set its number of edges to -1 (avoiding repeat travels)
		By recursion, if the number of nodes we travel matches the numCourses, return true, otherwise, return false
	Time complexity: O(V*E)	
	
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool Solution(int numCourses, vector<vector<int> > &prerequisites){
	int cnt = 0;
	vector<vector<int> > graph(numCourses, vector<int>());
	vector<int> edges(numCourses);
	for(int i=0; i<prerequisites.size(); i++){
		graph[prerequisites[i][0]].push_back(prerequisites[i][1]);
		edges[prerequisites[i][1]]++;
	}
	queue<int> que;
	for(int i=0; i<numCourses; i++){
		if(edges[i] == 0){
			que.push(i);
			cnt++;
		}
	}
	while(!que.empty()){
		int cur = que.front();
		que.pop();
		for(int i=0; i<graph[cur].size(); i++){
			if((--edges[graph[cur][i]]) == 0){
				que.push(graph[cur][i]);
				cnt++;
			}
		}
	}
	return (cnt == numCourses);
}

void DFS(int &cnt, int cur, vector<int> &edges, vector<vector<int> > &graph){
	for(int i=0; i<graph[cur].size(); i++){
		if((--edges[graph[cur][i]]) == 0){
			cnt++;
			edges[graph[cur][i]] = -1;
			DFS(cnt, graph[cur][i], edges, graph);
		}
	}
}

bool Solution2(int numCourses, vector<vector<int> > &prerequisites){
	int cnt = 0;
	vector<vector<int> > graph(numCourses, vector<int>());
	vector<int> edges(numCourses);
	for(int i=0; i<prerequisites.size(); i++){
		graph[prerequisites[i][0]].push_back(prerequisites[i][1]);
		edges[prerequisites[i][1]]++;
	}
	for(int i=0; i<numCourses; i++){
		if(edges[i] == 0){
			cnt++;
			DFS(cnt, i, edges, graph);
		}
	}
	return (cnt == numCourses);
}

int main(){
	int N, T;
	cin >> N >> T;
	vector<vector<int> > prerequisites(T, vector<int>(2));
	for(int i=0; i<T; i++){
		cin >> prerequisites[i][0] >> prerequisites[i][1];
	}
	cout << Solution(N, prerequisites) << endl;
	cout << Solution2(N, prerequisites) << endl;
}












