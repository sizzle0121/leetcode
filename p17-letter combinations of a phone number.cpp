/*
**	brute-force


*/
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

const char phoneNum[8][4] = {
		{'a', 'b', 'c', '#'},
		{'d', 'e', 'f', '#'},
		{'g', 'h', 'i', '#'},
		{'j', 'k', 'l', '#'},
		{'m', 'n', 'o', '#'},
		{'p', 'q', 'r', 's'},
		{'t', 'u', 'v', '#'},
		{'w', 'x', 'y', 'z'}
	};
vector<string> ans;

void enumerate(string &digits, int ptr, string current){
	if(ptr >= digits.length()){
		ans.push_back(current);
		return;
	}
	for(int i=0; i<4; i++){
		if(phoneNum[digits[ptr]-50][i] != '#'){
			enumerate(digits, ptr+1, current+phoneNum[digits[ptr]-50][i]);
		}		
	}
}

void Solution(string &digits){
	if(digits.length() == 0)	return;
	enumerate(digits, 0, "");
	
	for(int i=0; i<ans.size(); i++)
		cout << ans[i] << "  ";
	cout << endl;
}

int main(){
	string digits;
	getline(cin, digits);
	Solution(digits);
	
	return 0;
}
