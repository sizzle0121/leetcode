/*
 * Sliding Window:
 * It's the same as finding an anagram of s1 in s2
 * Anagram:
 * 1. Counts of all alphabets should be matched
 * 2. Length is the same as the original string
 *
 * Keep a array(usually a hashmap, but here, we can use an array instead, since it only contains lowercase letters) to records the counts for alphabets in s1, and the total counts should be matched 
 *
 * Extending the window:
 * If an alphabet is matched and count(alpha) - 1 >= 0, total counts -= 1
 * If there are still alphabets in s1 not being matched, we should continue to extend the window
 *
 * 
 * Update the answer:
 * Once the total count becomes zero, which means both conditions of anagram have been met\ 
 * Therefore, we can then return true
 *
 *
 * Maintain the window:
 * If count(alpha) < 0, we should make it up (exclude the extra one) from the left and discard all alphabets passed through\ 
 * since the anagram is impossible to contain any of them to the current right bound (will have an additional alphabet)
 * If current alphabet is not in s1, we should let the left bound be at r+1\ 
 * Still, we should maintain the counts of all alphabets we passed through from the left and the total count
 *
 * Time complexity: O(max(len1, len2)), len1: length of s1, len2: length of s2
 * Space complexity: O(1), the size of the vector is always 26
 *
 * */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool Solution(string &s1, string &s2){
	vector<int> cnt(26, -1);
	int len1 = s1.length(), len2 = s2.length(), total = 0;
	for(int i=0; i<len1; ++i){
		if(cnt[s1[i]-'a'] == -1) cnt[s1[i]-'a'] = 1;
		else cnt[s1[i]-'a']++;
		total++;
	}
	int l = 0, r = 0;
	while(r < len2){
		if(cnt[s2[r]-'a'] != -1){
			if(cnt[s2[r]-'a'] - 1 >= 0){
				total--;
			}
			cnt[s2[r]-'a']--;
			while(cnt[s2[r]-'a'] < 0){
				cnt[s2[l]-'a']++;
				if(s2[l] != s2[r]) total++;
				l++;
			}
		}else{
			while(l < r){
				cnt[s2[l++]-'a']++;
				total++;
			}
			l++;
		}
		if(total == 0) return true;
		r++;
	}
	return false;
}

int main(){
	string s1, s2;
	getline(cin, s1);
	getline(cin, s2);
	cout << Solution(s1, s2) << endl;
}
