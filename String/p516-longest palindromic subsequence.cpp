/*
 * Backtrack + Memorization:
 * Start from the largest range (l = 0, r = length)
 * Enumerate all pairs (s[i] == s[j]) in the range\ 
 * the corresponding j for i is found by looking for the same character from the back (r-1)
 * If found, then we don't need to find j-1 ~ i anymore, since the longest palindromic subsequence of [i, j-1] won't longer than that of [i, j]
 * For each pair, shrink the range to [i+1, j], and continue to enumerate all pairs in the new range
 * If a range is done (found the longest palindromic subsequence in that range),\ 
 * then return the length of the subsequence + 2 (2 is for the length of the pair itself)
 * and we memorize that return value in mem[i][j], thus, next time when we encounter the pair s[i], s[j], \ 
 * we can directly return the longest palindromic subsequence of string[i, j] without shrinking and enumerating all pairs inside the range again
 * 
 * Time complexity: O(n^2)
 *
 *
 * DP:
 * For substring s[x to y], its longest palindromic subsequence is either that of s[x+1 to y-1] + 2 or\ 
 * that of max(s[x+1 to y], s[x to y-1])
 * When equals to the former, represents s[x] == s[y], otherwise, it will equal to the latter
 * Therefore the optimal substructure is:
 * dp[j][i] = s[j]==s[j+i-1]? 2+dp[j+1][i-2] : max(dp[j+1][i-1], dp[j][i-1])
 * dp[j][i] is denoted as starting from character s[j], the length of range is i
 * Base case: dp[j][0] = 0, dp[j][1] = 1
 *
 * Time complexity: O(n^2)
 *
 * */
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int Backtrack(string &s, vector<vector<int> > &mem, int l, int r){
	unordered_map<char,bool> visited;
	int maxi = 0;
	for(int i=l; i<r; i++){
		if(visited.find(s[i]) == visited.end()){//same start characters can be ignored
												//since the corresponding s[j] is the same
												//but the first s[i] with s[j] has the largest range
			for(int j=r-1; j>=i; --j){//start from the right bound
				if(s[j] == s[i]){	
					if(mem[i][j] == 0){
						if(j == i+1)	mem[i][j] = 2;//base case
						else if(j == i)	mem[i][j] = 1;//base case
						else	mem[i][j] = 2+Backtrack(s, mem, i+1, j);//2 is for s[i], s[j] themselves
					}
					maxi = max(mem[i][j], maxi);//update the longest length in current range
					break;//no need to find j-1 to i
				}
			}
			visited[s[i]] = true;
		}
	}
	return maxi;
}

int Solution(string s){
	if(s.length() == 0)	return 0;
	int ans = 0, len = s.length();
	vector<vector<int> > mem(len, vector<int>(len));
	return Backtrack(s, mem, 0, len);
}

int Solution2(string s){
	if(s.length() == 0)	return 0;
	int len = s.length();
	vector<vector<int> > dp(len, vector<int>(len+1));//start points, length
	for(int i=0; i<len; i++)
		dp[i][1] = 1;
	for(int i=2; i<=len; i++){
		for(int j=0; j<len-i+1; j++){
			if(s[j] == s[j+i-1])
				dp[j][i] = 2 + dp[j+1][i-2];
			else
				dp[j][i] = max(dp[j][i-1], dp[j+1][i-1]);
		}
	}
	return dp[0][len];
}

int main(){
	string s;
	getline(cin, s);
	cout << Solution(s) << endl;
	cout << Solution2(s) << endl;
}
