/*
 * Enumeration:
 * For letters, we can either append its lower/upper case to all the previously generated strings
 * For numbers, we simply append it to all the previously generated strings
 * Base: "" (empty string)
 *
 * Time complexity: O(2^k), k: the number of letters
 * Space complexity: O(2^k)
 *
 * */
#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

vector<string> Solution(string &S){
	vector<string> ans;
	queue<string> que;
	que.push("");
	int conv = (int)('a') - (int)('A');
	for(auto &s: S){
		if((s >= 'a' && s <= 'z' ) || (s >= 'A' & s <= 'Z')){
			int n = que.size();
			while(n--){
				string tmp = que.front();
				tmp.push_back(s);
				que.push(tmp);
				tmp.pop_back();
				tmp.push_back(((int)(s) - (int)('a') >= 0)? (char)((int)(s) - conv) : (char)((int)(s) + conv));
				que.push(tmp);
				que.pop();
			}
		}else{
			int n = que.size();
			while(n--){
				string tmp = que.front();
				tmp.push_back(s);
				que.push(tmp);
				que.pop();
			}
		}
	}
	ans.reserve(que.size());
	while(!que.empty()){
		ans.push_back(move(que.front()));
		que.pop();
	}
	return ans;
}

int main(){
	string S;
	getline(cin, S);
	vector<string> ans(Solution(S));
	for(auto &a: ans)
		cout << a << endl;
}
