#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
 	vector<int> num;
	vector<int> ans;
 	int T, target;		//T, number of inputs for testing 
 		
 	while(cin >> T){
 		for(int i=0; i<T; i++){
			int tmp;
			cin >> tmp;
			num.push_back(tmp);
		}
		cin >> target;

		bool flag = false;
		for(int i=0; i<num.size()-1; i++){
			for(int j=i+1; j<num.size(); j++){
				if(num.at(i) + num.at(j) == target){
					ans.push_back(i);
					ans.push_back(j);
					flag = true;
					break;
				}
			}
			if(flag)	break;
		}
		
		cout << ans.at(0) << " " << ans.at(1) << endl;
		num.clear();
		ans.clear();		
 	}
 	return 0;
}
