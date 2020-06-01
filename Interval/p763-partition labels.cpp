/*
 * Merge Intervals:
 * Find the interval for each letter, sort, then merge
 * If no overlap, update the answer and the left/right bounds
 *
 * Time complexity: O(nlogn), but only 26 letters -> approximate O(n)
 * Space complexity: O(1), always 26 letters
 *
 *
 * Extend Intervals (Solution2, optimal):
 * For this problem, we can look letters by letters, instead of intervals by intervals
 * Store the right bounds for each letter
 * Then scan through the string, if the right bound of the current letter is larger than the current right bound\ 
 * extend the right bound
 * If current index == the right bound, it means that this is the end of this interval, thus, we can update the answer
 *
 * Time complexity: O(n)
 * Space complexity: O(1), always 26 letters
 *
 * */
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

struct cmp{
	bool operator()(const pair<int,int> &a, const pair<int,int> &b){
		if(a.first != b.first) return a.first < b.first;
		else return a.second < b.second;
	}
};

vector<int> Solution(string &S){
	if(S.length() == 0) return vector<int>{0};
	vector<pair<int,int> > letters(26, pair<int,int>(-1, -1));
	int len = S.length();
	for(int i=0; i<len; i++){
		if(letters[S[i]-'a'].first == -1){
			letters[S[i]-'a'].first = i;
			letters[S[i]-'a'].second = i;
		}else{
			letters[S[i]-'a'].second = i;
		}
	}
	sort(letters.begin(), letters.end(), cmp());
	int i = 0;
	while(letters[i].first == -1) i++;
	int l = letters[i].first, r = letters[i].second;
	i++;
	vector<int> ans;
	for(i; i<26; i++){
		if(letters[i].first <= r && letters[i].second > r){
			r = letters[i].second;
		}else if(letters[i].first > r){
			ans.push_back(r-l+1);
			l = letters[i].first;
			r = letters[i].second;
		}
	}
	ans.push_back(r-l+1);
	return ans;
}

vector<int> Solution2(string &S){
	if(S.length() == 0) return vector<int>{0};
	vector<int> letters(26);
	int len = S.length();
	for(int i=0; i<len; i++)
		letters[S[i]-'a'] = i;
	int l = 0, r = letters[S[0]-'a'];
	vector<int> ans;
	for(int i=0; i<len; i++){
		if(i == r){
			ans.push_back(r-l+1);
			if(i+1 < len){
				l = i+1;
				r = letters[S[i+1]-'a'];
			}
		}else if(letters[S[i]-'a'] > r) r = letters[S[i]-'a'];
	}
	return ans;
}

int main(){
	string S;
	getline(cin, S);
	vector<int> ans = Solution(S);
	vector<int> ans2 = Solution2(S);
	for(auto &a: ans)
		cout << a << " ";
	cout << endl;
	for(auto &a: ans2)
		cout << a << " ";
	cout << endl;
}
