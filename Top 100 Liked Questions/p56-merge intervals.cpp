/*
	sort the intervals, then merge them with conditions
	Time complexity: O(nlogn)
	Space complexity: O(1)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(vector<int> &a, vector<int> &b){
	return a[0] < b[0];
}

void Solution(vector<vector<int> > &intervals){
	if(intervals.empty())	return;
	for(int i=0; i<intervals.size(); i++){
		if(intervals[i][0] > intervals[i][1])
			swap(intervals[i][0], intervals[i][1]);
	}
	sort(intervals.begin(), intervals.end(), cmp);
	int head = 0;
	for(int i=1; i<intervals.size(); i++){
		if(intervals[i][0] <= intervals[head][1]){
			intervals[head][1] = (intervals[i][1] > intervals[head][1])? intervals[i][1]:intervals[head][1];

		}else{
			head++;
			intervals[head][0] = intervals[i][0];
			intervals[head][1] = intervals[i][1];
		}
	}
	while(intervals.size() > head+1)
		intervals.pop_back();
	
	//Print the answer
	for(int i=0; i<intervals.size(); i++){
		cout << intervals[i][0] << "," << intervals[i][1] << endl;
	}
}

int main(){
	int T, tmp1, tmp2;//T: numbers of intervals
	cin >> T;
	vector<vector<int> > intervals;
	while(T--){
		cin >> tmp1 >> tmp2;
		vector<int> tmp;
		tmp.push_back(tmp1);
		tmp.push_back(tmp2);
		intervals.push_back(tmp);
	}
	Solution(intervals);

	return 0;
}
