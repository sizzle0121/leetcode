/*
	If stack is empty, call stack.top() will receive segmentation fault
	Be aware of the cases '(' and ')'
*/
#include <iostream>
#include <stack>

using namespace std;

bool Solution(string s){
	//(([][]){})
	stack<char> para;
	for(int i=0; i<s.length(); i++){
		if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
			para.push(s[i]);
		}else{
			if(para.empty())	return false;
			else if(s[i] == ')' && para.top() == '(')	para.pop();
			else if(s[i] == ']' && para.top() == '[')	para.pop();
			else if(s[i] == '}' && para.top() == '{')	para.pop();
			else	return false;
		}
	}
	if(para.empty())	return true;
	else	return false;
}

int main(){
	string s;
	getline(cin, s);
	cout << Solution(s) << endl;
	return 0;
}
