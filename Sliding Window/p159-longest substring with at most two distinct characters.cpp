/*
 * See the advanced problem
 * "p340 longest substring with at most k distinct characters"
 *
 * */
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

int Solution(string s){
	int l = 0, r = 0, ans = 0, dist = 0;
	unordered_map<char,int> cnt;
	while(r < s.length()){
		if(dist < 2){
			if(cnt[s[r]] == 0)	dist++;
			cnt[s[r]]++;
		}else if(dist == 2){
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
	getline(cin, s);
	cout << Solution(s) << endl;
}
