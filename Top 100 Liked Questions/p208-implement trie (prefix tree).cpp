/*
	Implement Trie Data Structure (Prefix Tree)
	Each level of the tree represents the nth character of a string, and its 0 to n-1 characters are at its upper levels
	The same level of 'abc' and 'atc', the 'c' will be at the same level but different nodes (since their parents are different)
	Each node has an array to save the characters that are possible to come up, and a counter to record how many duplicate strings or does a string exist in this tree
	
	For inserting a new string to the tree, starting from the root, we check if at this position, the character of the string in the array is null pointer
	If it's null, creat a new node and move on to look up the next character
	If not, simply move on
	At the end, update the counter

	For search and prefix, we travel from the root to check if each level of the tree has non null pointer for each position of the string
	The counter should not be 0 for searching, but it's okay for prefix



	Time complexity:
	Insert: O(n), where n is the length of the string being inserted
	Search: O(n)
	Prefix: O(m), where m is the length of the prefix being looked up
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct TrieNode{
	int n;
	//vector<TrieNode*> alpha;
	TrieNode *alpha[26];	
	TrieNode():n(0) {
		//for(int i=0; i<26; i++)
		//	alpha.push_back(NULL);
		memset(alpha, NULL, sizeof(alpha));//using memset to initialize is faster
	}
};

class Trie{
public:
	Trie(){
		root = new TrieNode();
	}
	~Trie(){
		clear(root);
	}

	void insert(string word){
		TrieNode *tmp = root;
		for(int i=0; i<word.length(); i++){
			int offset = word[i] - 'a';
			if(!tmp->alpha[offset]){
				tmp->alpha[offset] = new TrieNode();
			}
			tmp = tmp->alpha[offset];
		}
		tmp->n++;
	}

	bool search(string word){
		TrieNode *tmp = root;
		for(int i=0; i<word.length(); i++){
			int offset = word[i] - 'a';
			if(!tmp->alpha[offset])
				return false;
			tmp = tmp->alpha[offset];
		}
		return (tmp->n);
	}

	bool startsWith(string prefix){
		TrieNode *tmp = root;
		for(int i=0; i<prefix.length(); i++){
			int offset = prefix[i] - 'a';
			if(!tmp->alpha[offset])
				return false;
			tmp = tmp->alpha[offset];
		}
		return true;
	}

private:
	TrieNode *root;
	void clear(TrieNode *node){
		for(int i=0; i<26; i++){
			if(node->alpha[i]){
				clear(node->alpha[i]);
			}
		}
		delete node;
	}
};

int main(){
	string ipt;
	Trie *obj = new Trie();
	while(getline(cin, ipt)){
		int start = ipt.find_first_of('"');
		int end = ipt.find_last_of('"');
		string subs = ipt.substr(start+1, end-start-1);
		if(ipt[5] == 'i'){
			obj->insert(subs);
		}else if(ipt[6] == 'e'){
			cout << obj->search(subs) << endl;
		}else if(ipt[6] == 't'){
			cout << obj->startsWith(subs) << endl;
		}

	}

}
