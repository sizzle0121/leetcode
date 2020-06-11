/*
 * Hash Table + Sliding Window:
 * Extend the window:
 * The size of the window is fixed
 *
 * Update the answer:
 * For each window, we analyze its contents\ 
 * Extract the substring per len (words[0].size)\ 
 * If all substrings match the word in "words", push the left bound of the window into the answer array
 *
 * Maintain the window:
 * If the substring doesn't match any word in "words", the current window fails
 * If the substring match a word in "words", but the number of the same word are already full, the current window fails
 * Move the window one index ahead
 *
 *
 * Time complexity: O(l * k), l: s.length, k: the sieze of the window (= words.size() * words[0].size())
 * Space complexity: O(k)
 *
 * */
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> Solution(string &s, vector<string> &words){
	vector<int> ans;
	if(words.empty()) return ans;
	int k = words.size(), len = words[0].length();
	unordered_map<string,int> cnt;
	for(int i=0; i<k; ++i)
		cnt[words[i]]++;

	int idx = 0, lenS = s.length(), winSize = k*len, i = 0;
	if(lenS == 0) return ans;
	while(idx <= lenS-winSize){
		i = 0;
		while(i < k){
			unordered_map<string,int> cntS;
			string tmp = s.substr(idx + i*len, len);
			if(cnt.find(tmp) != cnt.end()){
				cntS[tmp]++;
				if(cntS[tmp] > cnt[tmp]) break;
			}else break;
			i++;
		}
		if(i == k) ans.push_back(idx);
		idx++;
	}
	return ans;
}

int main(){
	string s;
	getline(cin, s);
	int T;
	cin >> T;
	cin.ignore();
	vector<string> words(T);
	for(auto &w: words)
		getline(cin, w);
	vector<int> ans = Solution(s, words);
	for(auto &a: ans)
		cout << a << " ";
	cout << endl;
}
