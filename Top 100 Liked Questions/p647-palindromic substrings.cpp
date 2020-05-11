/*
 * Expand from Centers:
 * Enumerate all centers (i, i) and (i, i+1)
 * Expand from them, if s[l] == s[r] -> ans++
 * if s[l] != s[r] -> return (since the inner substring of a palindromic string must be palindromic too)
 * The expansion of different centers won't duplicate
 * By enumerating through all centers and check if expansions of centers are palindromic, we can obtain the answer
 *
 * Time complexity: O(n*n/2) = O(n^2)
 *
 * */
#include <iostream>
#include <string>
using namespace std;

int check(int l, int r, const string &s){
	int ans = 0;
	while(l >= 0 && r < s.length()){
		if(s[l--] == s[r++])	ans++;
		else break;
	}
	return ans;
}

int Solution(string s){
	int ans = 0;
	for(int i=0; i<s.length(); i++){
		ans += check(i, i, s);
		ans += check(i, i+1, s);
	}
	return ans;
}

int main(){
	string s;
	getline(cin, s);
	cout << Solution(s) << endl;
}
