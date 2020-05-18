/*
 * Stack:
 * Similar to the valid parentheses problem
 * The characters in the input string can only be in the 'a' -> 'b' -> 'c' order
 * and if 'c' is reached, we pop out three of them and continue to see the next character in the string
 *
 * Time complexity: O(n)
 *
 * Inspiration:
 * If the problem has a rule about order
 * 	we can usually use stack or topology sort to solve it
 * especially for those with enclosed property, stack may be the solution 
 *
 * */
#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

bool Solution(string S){
	int len = S.length();
	if(len < 3)	return false;
	stack<char> buf;
	for(auto &s: S){
		if(s == 'a')	buf.push(s);
		else if(buf.empty())	return false;
		else if(s == 'b' && buf.top() == 'a')	buf.push(s);
		else if(s == 'c' && buf.top() == 'b'){
			buf.pop();
			buf.pop();
		}else 	return false;
	}
	if(buf.empty())	return true;
	else return false;
}

int main(){
	string S;
	getline(cin, S);
	cout << Solution(S) << endl;
}
