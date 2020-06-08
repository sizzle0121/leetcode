/*
 * DP:
 * Let dp[i][j] be denoted as the minimum edit distance of substring(word1[0...i]) and substring(word2[0...j])
 * The optimal substructure:
 * dp[i][j] = \ 
 * dp[i-1][j-1], when word1[i] == word2[j] (no need to edit)
 * dp[i-1][j] + 1, when word1[i] != word2[j], and we insert word1[i] or we delete word1[i]
 * dp[i][j-1] + 1, when word1[i] != word2[j], and we insert word2[j] or we delete word2[j] 
 * dp[i-1][j-1] + 1, when word1[i] != word2[j], and we replace word1[i]/word2[j] with word2[j]/word1[i]
 * 
 * When word1[i] != word2[j], we should choose the way of editting with the minimum edit distance for dp[i][j]
 *
 *
 * DP for String:
 * For 1 string, the transition: prefix(S[i]) + S[i]
 * For 2 strings, the transition: prefix(S1[i]) + S1[i], prefix(S2[j]) + S2[j]
 * The prefix part is the overlap of the subproblem and the current problem
 * For 2 strings, usually need to split the problem into 1) when S1[i] == S2[j], 2) when S1[i] != S2[j]
 *
 *
 * Time complexity: O(n * m), n and m are the length of word1 and word2 respectively
 * Space complexity: O(n * m)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Solution(string &word1, string &word2){
	int len1 = word1.length(), len2 = word2.length();
	vector<vector<int> > lcs(len1+1, vector<int>(len2+1));
	for(int i=1; i<=len1; i++) lcs[i][0] = i;
	for(int i=1; i<=len2; i++) lcs[0][i] = i;
	for(int i=0; i<len1; i++){
		for(int j=0; j<len2; j++){
			if(word1[i] == word2[j]) lcs[i+1][j+1] = lcs[i][j];
			else lcs[i+1][j+1] = min(lcs[i][j], min(lcs[i][j+1], lcs[i+1][j])) + 1;
		}
	}
/*
	cout << endl;
	for(int i=0; i<=len1; i++){
		for(int j=0; j<=len2; j++)
			cout << lcs[i][j] << " ";
		cout << endl;
	}
*/
	return lcs[len1][len2];
}


int main(){
	string word1, word2;
	getline(cin, word1);
	getline(cin, word2);
	cout << Solution(word1, word2) << endl;
}
