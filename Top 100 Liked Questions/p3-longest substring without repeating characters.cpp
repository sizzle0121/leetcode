#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<char, int> substringChar;
int Solution(string s){
	int cnt = 0, max = 0, i = 0;
	bool toEnd;
	while(i < s.length()){
		substringChar.clear();
		substringChar[s.at(i)] = i;
		cnt = 1;
		toEnd = true;
		for(int j=i+1; j<s.length(); j++){
			if(substringChar.find(s.at(j)) != substringChar.end()){
				i = substringChar[s.at(i)] + 1;
				toEnd = false;
				break;
			}else{
				cnt++;
				substringChar[s.at(j)] = j;
			}
		}
		if(cnt > max)   max = cnt;
		if(toEnd)	return max;
	}

	return max;
}

int main(){
	string s;
	getline(cin, s);
	cout << Solution(s) << endl;		

	return 0;
}
