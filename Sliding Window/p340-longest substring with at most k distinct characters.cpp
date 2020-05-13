/*
 * Another Sliding Window Problem:
 * 1. Extend the window to meet the requirements\ 
 * Here, the requirement is the distinct characters should <= k, so less than k is also valid
 * -> also may need to update the answer
 * Hash table records the counts of characters inside the window
 *
 * 2. Once we reach the limit of the requirement (k), we should maintain it
 * If s[r] is a new character, we should delete a character completely out of the window\ 
 * in order to maintain <= k distinct characters
 * We move the left pointer to the leftmost position that can exclude a character previously included in the window
 * By doing so, we can possibly find substring that has k distinct characters which is longer than we found before
 * If s[r] is not a new character, then just update the count of it and update the answer if right - left + 1 is longer than the current answer
 *
 * Time complexity: O(2n) = O(n), the left pointer moves at most n, so does the right pointer
 *
 * */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

int Solution(string s, int k){
	int l = 0, r = 0, ans = 0, dist = 0;
	unordered_map<char,int> cnt;//character, count of it iside the window
	while(r < s.length()){
		if(dist < k){
			if(cnt[s[r]] == 0)	dist++;
			cnt[s[r]]++;
		}
		else if(dist == k){
			if(cnt[s[r]] == 0){
				while(cnt[s[l]] - 1 > 0){
					cnt[s[l]]--;
					l++;
				}
				cnt[s[l]]--;
				l++;
			}
			cnt[s[r]]++;
		}
		ans = max(ans, r-l+1);
		r++;
	}
	return ans;
}

int main(){
	string s;
	int k;
	getline(cin, s);
	cin >> k;
	cout << Solution(s, k) << endl;
}
