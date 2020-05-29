/*
 * Hash Table:
 * Use hash table to record the counts for each alphabet in s
 * Then counts - 1 when meeting the same alphabet in string t
 * If counts - 1 < 0, representing that t contains alphabet that is not in s, or contains alphabet that is in s but t has more count than s, so we should return false
 *
 * Anagram: equal length && same counts of all alphabets
 *
 * Time complexity: O(n)
 * Space complexity: O(1), always 26 sizeof(int) extra memory
 *
 * */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool Solution(string s, string t){
	if(s.length() != t.length()) return false;
	vector<int> cnt(26);
	for(int i=0; i<s.length(); i++)
		cnt[s[i]-'a']++;
	for(int i=0; i<t.length(); i++){
		if(cnt[t[i]-'a'] - 1 < 0) return false;
		else cnt[t[i]-'a']--;
	}
	for(int i=0; i<26; i++)
		if(cnt[i] != 0) return false;
	return true;
}

int main(){
	string s, t;
	getline(cin, s);
	getline(cin, t);
	cout << Solution(s, t) << endl;
}
