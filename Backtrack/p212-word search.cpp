/*
 * Trie + Backtrack:
 * When it comes to match a word in a dictionary, we will usually implement Trie structure
 *
 * First, build up the trie for "words"
 * For every letter that match a letter of the root of the trie, backtrack it
 * Backtrack:
 * If any letter of the four directions match the next node of the current letter, push it into the current string and go for the next level of recursion
 * If the value of the current node > 0, which means we have matched a word in "words", push it into the answer array
 * Also notice that we should turn visited letters in the board to '#' as visited
 *
 * Time complexity: O(avg(length of word in words) * n * m)
 * Space complexity: O(number of letters in words)
 *
 * */
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

struct TrieNode{
	int v;
	TrieNode* next[26];
	TrieNode(): v(0){
		memset(next, 0, sizeof(next));
	}
};

void backtrack(int x, int y, vector<vector<char> > &board, TrieNode *node, vector<string> &ans, string &cur){
	if(node->v > 0){
		ans.push_back(cur);
		node->v--;//avoid push multiple times when the same word present multiple times in the board
	}

	char tmp = board[x][y];
	board[x][y] = '#';
	int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	for(int i=0; i<4; ++i){
		int x_ = x+dir[i][0], y_ = y+dir[i][1];
		if(x_ >= 0 && x_ < board.size() && y_ >= 0 && y_ < board[0].size() && board[x_][y_] != '#' && node->next[board[x_][y_]-'a']){
			cur.push_back(board[x_][y_]);
			backtrack(x_, y_, board, node->next[board[x_][y_]-'a'], ans, cur);
			cur.pop_back();
		}
	}
	board[x][y] = tmp;
}

vector<string> Solution(vector<vector<char> > &board, vector<string> &words){
	if(board.empty() || words.empty()) return vector<string>();
	TrieNode *root = new TrieNode();
	for(auto &word: words){
		TrieNode *ptr = root;
		for(auto &c: word){
			if(!ptr->next[c-'a'])
				ptr->next[c-'a'] = new TrieNode();
			ptr = ptr->next[c-'a'];
		}
		ptr->v++;
	}

	vector<string> ans;
	ans.reserve(words.size());
	int N = board.size(), M = board[0].size();
	for(int i=0; i<N; ++i){
		for(int j=0; j<M; ++j){
			if(root->next[board[i][j]-'a']){
				string cur = "";
				cur.push_back(board[i][j]);
				backtrack(i, j, board, root->next[board[i][j]-'a'], ans, cur);
			}
		}
	}
	return ans;
}

int main(){
	int n, m, T;
	cin >> n >> m;
	vector<vector<char> > board(n, vector<char>(m));
	for(int i=0; i<n; ++i)
		for(int j=0; j<m; ++j)
			cin >> board[i][j];
	cin >> T;
	cin.ignore();
	vector<string> words(T);
	for(auto &w: words)
		getline(cin, w);

	vector<string> ans(Solution(board, words));
	for(auto &a: ans)
		cout << a << endl;
}
