/*
 * Brute-force:
 * Concatenate each pair of strings, and check if it is palindromic
 * for(int i=0; i<words.size(); i++)
 * 		for(int j=i+1; j<words.size(); j++)
 * 			if(isPalindromic( words[i] + words[j] ))
 * 				ans.push_back(vector<int>{i, j});
 * 			if(isPalindromic( words[j] + words[i] ))
 * 				ans.push_back(vector<int>{j, i});
 * 
 * Time complexity: O(n^2 * 2 * m) = O(n^2 * m), where n is words.size(), m is the longest concatenated word
 *
 *
 * HashTable + Trie:
 * 1. For each string, enumerate all possible strings that can make it become a palindrome
 * 2. For each of the possible, check if it exists in our "words"
 *    If so, check if is palindromic
 * 
 * For step 2, we can implement Trie structure to search for it efficiently, O(S), S is the length of the target string\ 
 * Directly search in the array for the string is O(n*S), n = array.size()
 * For step 1, the possible strings will be the substrings of the reversed string of the original one\ 
 * ans they can be only rev.substr(0, len=1) to rev.substr(0, len=revLen), which concatenated in front of the original one\ 
 * and rev.substr(1) to rev.substr(revLen-1), which concatenated behind the original one
 * There are revLen*2 - 1 possibles in total
 *
 * Time complexity: O(n * 2 * k * (k + m)) = O(n * k * m), where n is words.size(), m is the longest concatenated word, k is the length of the longest word in words
 *
 * */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct TreeNode{
	int n;
	TreeNode *next[26];
	TreeNode(): n(0){
		memset(next, 0, sizeof(TreeNode*) * 26);
	}
};

bool isPalindrome(string s){
	int n = s.length();
	for(int i=0; i<n/2; i++)
		if(s[i] != s[n-1-i])
			return false;
	return true;
}

vector<vector<int> > Solution(vector<string> &words){
	TreeNode *root = new TreeNode();
	unordered_map<string,int> hashTab;
	for(int i=0; i<words.size(); i++){
		TreeNode *tmp = root;
		hashTab[words[i]] = i;
		for(int j=0; j<words[i].size(); j++){
			if(!tmp->next[words[i][j]-'a'])
				tmp->next[words[i][j]-'a'] = new TreeNode();
			tmp = tmp->next[words[i][j]-'a'];
		}
		tmp->n++;
	}
	vector<vector<int> > ans;
	if(hashTab.find("") != hashTab.end()){//empty string exists
		for(auto &s: words){
			if(s != "" && isPalindrome(s)){//add all self-aplindromic strings to the answer
				ans.push_back(vector<int>{hashTab[""], hashTab[s]});
				ans.push_back(vector<int>{hashTab[s], hashTab[""]});
			}
		}	
	}
	for(auto &s: words){
		string rev(s);
		reverse(rev.begin(), rev.end());
		int revLen = rev.length();
		for(int i=1; i<2*revLen; i++){
			string target = (i<=revLen)? rev.substr(0, i) : rev.substr(i-revLen);
			if(target == s)	continue;
			TreeNode *node = root;
			bool found = true;
			for(int j=0; j<target.length(); j++){	
				if(node->next[target[j]-'a']){
					node = node->next[target[j]-'a'];
				}else{
					found = false;
					break;
				}
			}
			if(found && node->n){
				if(i <= revLen && isPalindrome(target+s))		ans.push_back(vector<int>{hashTab[target], hashTab[s]});
				else if(i > revLen && isPalindrome(s+target))	ans.push_back(vector<int>{hashTab[s], hashTab[target]});
			}
		}
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	cin.ignore();
	vector<string> ipt(T);
	for(auto &s: ipt)
		getline(cin, s);
	vector<vector<int> > ans = Solution(ipt);
	for(auto &opt: ans)
		cout << opt[0] << " " << opt[1] << endl;
}
