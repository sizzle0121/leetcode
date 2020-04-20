/*
	Grouping:	Not to compare each pair of strings, BUT to categorize every string

	judging two strings are anagram or not:
	method 1.	- length must be the same
				- numbers of each character should count the same(already include condition 1)
	method 2.	- sorted character should be the same
*/
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

void Solution(vector<string> &strs){
	if(strs.empty())	return;
	unordered_map<string, vector<string> > category;
	for(int i=0; i<strs.size(); i++){
		vector<int> cnt(26);
		for(int j=0; j<strs[i].size(); j++){
			cnt[strs[i][j] - 'a']++;
		}

		string key = "";
		for(int j=0; j<26; j++){
			key += '#';
			stringstream ss;
			string tmp;
			ss << cnt[j];
			ss >> tmp;
			key += tmp;
		}

		if(category.find(key) != category.end()){
			category[key].push_back(strs[i]);
		}else{
			category.insert(pair<string, vector<string> >(key, vector<string>()));//cant use '=' here to insert
			category[key].push_back(strs[i]);
		}
	}
	vector<vector<string> > ans;
	for(unordered_map<string, vector<string> >::iterator i=category.begin(); i!=category.end(); i++){
		ans.push_back(i->second);
	}

	for(int i=0; i<ans.size(); i++){
		for(int j=0; j<ans[i].size(); j++)
			cout << ans[i][j] << ", ";
		cout << endl;
	}
}

int main(){
	int T;
	string tmp;
	vector<string> strs;	
	cin >> T;
	while(T--){
		cin >> tmp;
		strs.push_back(tmp);
	}
	Solution(strs);
	return 0;
}
