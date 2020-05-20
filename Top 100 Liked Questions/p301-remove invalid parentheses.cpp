/*
 * Try so many ways, still cannot lower the time complexity than O(2^n)
 * BFS:
 * Intuition: try remove one parenthesis at every position from the string,\ 
 * if none of them are valid, then remove the second parenthesis at every position from the previous strings
 * if any of them is valid, then add all valid strings with the same length to our answer
 *
 * Time complexity: O(2^n), since every position is either present or absent
 *
 * */
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

bool valid(string &s){
	int balance = 0, len = s.length();
	for(int i=0; i<len; i++){
		if(s[i] == '(')	balance++;
		else if(s[i] == ')'){
			balance--;
			if(balance < 0)	return false;
		}
	}
	if(balance != 0) return false;
	else return true;
}

vector<string> Solution(string s){
	unordered_map<string,bool> exist;
	queue<string> que;
	que.push(s);
	int endpoint = -1;
	vector<string> ans;
	while(!que.empty()){
		if(valid(que.front())){
			if(endpoint != -1 && que.front().length() == endpoint){//after we found, all valid strings should have same len
				ans.push_back(que.front());
			}else{ 
				endpoint = que.front().length();//found valid string
				ans.push_back(que.front());
			}
		}
		if(endpoint == -1){//still no valid strings
			string tmp = que.front();
			int len = tmp.length();
			for(int i=0; i<len; i++){
				if(tmp[i] == '(' || tmp[i] == ')'){
					string rm = tmp.substr(0, i);		//this   lines      a           at        i
					if(i+1 < len) rm += tmp.substr(i+1);//	  two     remove parenthesis  position
					if(exist.find(rm) == exist.end()){//avoid visiting duplicate substrings
						que.push(rm);
						exist[rm] = true;
					}
				}
			}
		}
		que.pop();
	}
	return ans;
}

int main(){
	string s;
	getline(cin, s);
	vector<string> ans = Solution(s);
	for(auto &str: ans)
		cout << str << endl;
}
