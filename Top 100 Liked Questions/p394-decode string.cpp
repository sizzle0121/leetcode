/*
	Stack:
	Keep pushing characters into stack<string> until we meet ']'
	When we meet ']', we extract the string between the corresponding '[' by concatanating to string tmp
	When we meet the corresponding '[', we start to calculate the k (how many times we have to repeat it)
	After we meet the non-numerical character, we repeat concatanating the extracted string k times
	Then we push the whole string into the stack again
	By doing so, the stack will finally contains the answer in reverse order
	Therefore, we reverse it and ace this problem
	Actually, the difficult point is the conversion between char and string, as well as the segmentation fault caused by stack.empty()

	Time complexity: O(n+S), where n is the length of the original input string, S is the length of the decoded string

*/
#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

string Solution(string s){
	if(s.length() == 0)	return "";
	stack<string> decoder;
	for(int i=0; i<s.length(); i++){
		if(s[i] == ']'){
			string tmp = "";
			string rtmp = "";
			while(1){
				if(decoder.top()[0] == '['){
					decoder.pop();
					int k = 0, dec = 1;
					while(!decoder.empty() && (decoder.top()[0] >= '0' && decoder.top()[0] <= '9')){
						k += (decoder.top()[0]-'0') * dec;
						dec *= 10;
						decoder.pop();
					}
					while(k--){ rtmp += tmp; }
					decoder.push(rtmp);
					break;
				}else{
					tmp += decoder.top();
					decoder.pop();
				}
			}
		}else{
			string tmp(1, s[i]);
			decoder.push(tmp);
		}
	}
	string ans = "";
	while(!decoder.empty()){
		ans += decoder.top();
		decoder.pop();
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

int main(){
	string ipt;
	getline(cin, ipt);
	cout << Solution(ipt) << endl;
}

