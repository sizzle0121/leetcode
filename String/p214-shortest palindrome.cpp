/*
 * Solution 1 (enumerate center + expand from center) 
 * & 
 * Solution 2 (reverse string + find the largest overlapped substring)
 * all got TLE
 *
 * Solution 3 (MP Algorithm):
 * Actually, here only use the concept of failure function
 * Inspired by solution 2, we can concatenate the original string and the reversed string\ 
 * then find the longest matched prefix and suffix of the concatenated string (except for the whole string itself)
 * (since the longest mateched prefix & suffix is equivalent to the largest overlapped substring of the original string and the reversed string)
 * 
 * Failure Function:
 * Let the string be denoted as S
 * The value of the function f(i) represents the corresponding position for S[i] in the longest matched prefix in S[0, i]
 * If the suffix of S[0, i] doesn't match any prefix, then f(i) will be -1 (means no position it can correspond to)
 * 
 * For example:
 * S = "abcabz"
 * f = -1, -1, -1, 0, 1, -1
 * for S[4]='b', the longest matched prefix in S[0, 4] is 'ab', and its corresponding position is S[1], so f(4) = 1
 * for S[5]='z', it doesn't match the next position of the longest matched preifix of S[0, i-1] = S[0, 4], that is, S[2]='c'
 * but we should keep checking if it match f(f(i-1))+1
 * f(f(i-1)) is the corresponding position of f(i-1) in S[0, f(i-1)], and the next position of it can be also possible to put S[i], otherwise, directly set f(i) to -1 may miss the prefix can be matched
 * However, for this example, f(f(i-1)) = f(f(4)) = f(1) = -1, and the next of position -1 is 0, 'z' still not match S[0]='a', so f(5) = -1
 *
 * By doing this bottom-up, we can derive the failure function of the concatenated string
 * and the f(string length-1) is the last character's corresponding position in the longest matched prefix in the concatenated string
 * It will at least be zero (the first character of the original string)
 *
 * reversed string.substring(0, length - 1 - f(last character)) + original string will be our answer
 *
 * Time complexity: O(2n) = O(n)
 *
 * */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool check(int left, int right, string &s){
	while(left >= 0 && right < s.length()){
		if(s[left--] != s[right++])
			return false;
	}
	return true;
}

string addFront(int idx, string &s, bool flag){
	string ans = "";
	int tmp = flag? idx+idx : idx+idx+1;
	while(tmp < s.length())
		ans += s[tmp++];
	reverse(ans.begin(), ans.end());
	return ans;
}

string Solution(string s){
	string ans = "";
	bool even = s.length()%2? false : true;
	for(int i=s.length()/2; i>=0; --i){
		if(even && i > 0){	
			if(check(i-1, i, s)){
				ans = s.substr(i+i);
				break;
			}	
			if(check(i-1, i-1, s)){
				ans = s.substr(i+i-1);
				break;
			}
		}else{
			if(check(i, i, s)){
				ans = s.substr(i+i+1);
				break;
			}
			if(check(i-1, i, s)){
				ans = s.substr(i+i);
				break;
			}
		}
	}
	reverse(ans.begin(), ans.end());
	ans += s;
	return ans;
}

string Solution2(string s){
	string tmp(s), ans = "";
	int len = s.length();
	reverse(tmp.begin(), tmp.end());
	if(tmp == s)	return s;
	for(int i=1; i<len; i++){
		if(tmp.substr(i) == s.substr(0, len-i)){
			return ans = tmp + s.substr(len-i);
		}
	}
	return ans;
}

string Solution3(string s){
	if(s.length() == 0)	return "";
	string rev(s);
	reverse(rev.begin(), rev.end());
	string tmp = s + "#" + rev;//add '#' to prevent from mixing s and rev
	vector<int> failure(tmp.length(), -1);
	failure[0] = -1;
	for(int i=1, j=-1; i<tmp.length(); i++){
		while(j >= 0 && tmp[j+1] != tmp[i]){//j is actually f(i-1)
			j = failure[j];//keep checking f(f(i-1))
		}
		if(tmp[j+1] == tmp[i])	j++;//put i to its corresponding position j+1
		failure[i] = j;//so f(i) = j+1
	}
	return rev.substr(0, rev.length()-1-failure.back()) + s;
}


int main(){
	string s;
	getline(cin, s);
	cout << Solution3(s) << endl;
}
