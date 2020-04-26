/*
	Brute-force (Recursive solution): 
	Compare words in dictionary from S(0)
	If match (substring 0 to i), then compare words in dictionary from S(i+1)
	If no match, backtrack

	Then I came into pruning the position i where we already compare to the end
	If the comparison from i can reach to the end (all have match), we mark it as "good position"
	Next time when we arrive at i, we don't need to continue our comparison

	Therefore, I further thought it as a DP problem: like the "Jump Game" problem
	Starting from th back of string S, if word[k] in dictionary matches S(i, i + wordDict[k].length)
	We check whether (i + wordDict[k].length + 1) is a good position, if so, then i is also a good position
	Base case: S(S.length) = good position
	Eventually, the answer equals to whether S(0) is a good position or not

	Time complexity: O(n * m * k), where n = S.length, m = numbers of strings in the dictionary, k = average length of strings in the dictionary

*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool Solution(string s, vector<string> &wordDict){
	bool dp[s.length()+1];
	for(int i=0; i<=s.length(); i++)
		dp[i] = false;

	dp[s.length()] = true;
	for(int i=s.length()-1; i>=0; --i){
		for(int j=0; j<wordDict.size(); j++){
			if(s.length()-i >= wordDict[j].length() && wordDict[j].compare(0, wordDict[j].length(), s, i, wordDict[j].length()) == 0){
				if(dp[i+wordDict[j].length()] == true){
					dp[i] = true;
					break;
				}
			}
		}
	}
	return dp[0];
}

int main(){
	string s;
	cin >> s;
	int T;
	cin >> T;
	vector<string> wordDict(T);
	for(int i=0; i<T; i++)
		cin >> wordDict[i];
	cout << Solution(s, wordDict) << endl;
	return 0;
}
