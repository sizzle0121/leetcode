/*
	**	backtrack: search for all points equals to the first character of the word as starting point, then travel from it, at each step we look for the next character of the word from 4 direction(down, right, up, left), and keep an array (visited) to note the place we already visited, since the same letter cell can be only used once
	
	Time complexity: O(n*m*k), where n*m is the board size, k is the length of the word
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool travel(vector<vector<char> > &board, string word, int pos, bool **visited, int x, int y){
	if(pos >= word.length())	return true;
	bool found = false;
	if(!found && x+1 < board.size() && board[x+1][y] == word[pos] && !visited[x+1][y]){
		visited[x+1][y] = true;
		found = travel(board, word, pos+1, visited, x+1, y);
		visited[x+1][y] = false;
	}
	if(!found && y+1 < board[0].size() && board[x][y+1] == word[pos] && !visited[x][y+1]){
		visited[x][y+1] = true;
		found = travel(board, word, pos+1, visited, x, y+1);
		visited[x][y+1] = false;
	}
	if(!found && x-1 >= 0 && board[x-1][y] == word[pos] && !visited[x-1][y]){
		visited[x-1][y] = true;
		found = travel(board, word, pos+1, visited, x-1, y);
		visited[x-1][y] = false;
	}
	if(!found && y-1 >= 0 && board[x][y-1] == word[pos] && !visited[x][y-1]){
		visited[x][y-1] = true;
		found = travel(board, word, pos+1, visited, x, y-1);
		visited[x][y-1] = false;
	}
	return found;
}

bool Solution(vector<vector<char> > &board, string word){
	bool **visited = new bool*[board.size()];
	for(int i=0; i<board.size(); i++){
		visited[i] = new bool[board[i].size()];
		for(int j=0; j<board[i].size(); j++)
			visited[i][j] = false;
	}

	for(int i=0; i<board.size(); i++){
		for(int j=0; j<board[i].size(); j++){
			if(board[i][j] == word[0]){
				visited[i][j] = true;
				if(travel(board, word, 1, visited, i, j))	return true;
				visited[i][j] = false;
			}
		}
	}
	return false;
}

int main(){
	int n, m;
	cin >> n >> m;
	vector<vector<char> > board;
	char c;
	for(int i=0; i<n; i++){
		board.push_back(vector<char>());
		for(int j=0; j<m; j++){
			cin >> c;
			board[i].push_back(c);
		}
	}
	string word;
	cin >> word;
	cout << Solution(board, word) << endl;
	return 0;
}
