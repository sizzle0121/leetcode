#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

int main(){
 	vector<int> num;
	vector<int> ans;
	unordered_map<int, int> mapNum;
 	int T, target;		//T, number of inputs for testing 
 		
 	while(cin >> T){
 		for(int i=0; i<T; i++){
			int tmp;
			cin >> tmp;
			num.push_back(tmp);
		}
		cin >> target;

		for(int i=0; i<num.size(); i++){
			int dif = target - num.at(i);
			if(mapNum.find(dif) != mapNum.end()){
				ans.push_back(mapNum[dif]);
				ans.push_back(i);
				break;
			}
			mapNum[num.at(i)] = i;
		}
		
		cout << ans.at(0) << " " << ans.at(1) << endl;
		num.clear();
		ans.clear();		
 		mapNum.clear();
	}
 	return 0;
}
