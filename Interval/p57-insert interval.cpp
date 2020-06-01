/*
 * Interval Manipulation:
 * Solution2 is a cleaner version, but the time/space complexity is the same as Solution1
 *
 * We can split the insertion into three stages
 * 1. Push all intervals that are in front of the newInterval into the answer array
 * 2. Detect overlap & merge
 *    Once the interval is not in front of the newInterval, we only need to check if it's completely behind the newInterval
 *    If not, they must be overlapping, then we update the left and right bounds of the newInterval, and continue to see if the next interval is overlapping with the newInterval
 *    If no overlap, push the newInterval into the answer array
 * 3. Push all intervals that are behind the newInterval into the answer array
 *
 * The reason that Solution2 is cleaner is that at stage 2, it uses the opposite logic\ 
 * If the interval is neither in front of nor behind of the newInterval, then they must be overlapping
 * Instead of directly set all conditions to determine if overlap occurs
 *
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int> > Solution(vector<vector<int> > &intervals, vector<int> &newInterval){
	int l = -1, r = -1;
	vector<vector<int> > ans;
	if(intervals.empty()){
		ans.push_back(newInterval);
		return ans;
	}else if(newInterval.empty()){
		return intervals;
	}

	for(int i=0; i<intervals.size(); i++){
		if(l == -1 && newInterval[0] >= intervals[i][0] && newInterval[0] <= intervals[i][1]){
			l = intervals[i][0];
			r = max(intervals[i][1], newInterval[1]);
		}else if(l == -1 && newInterval[1] >= intervals[i][0] && newInterval[1] <= intervals[i][1]){
			l = min(intervals[i][0], newInterval[0]);
			r = intervals[i][1];
		}else if(l != -1){
			if(intervals[i][0] <= r) r = max(intervals[i][1], r);
			else{
				ans.push_back(vector<int>{l, r});
				for(int j=i; j<intervals.size(); j++)
					ans.push_back(intervals[j]);
				return ans;
			}
		}else if(l == -1 && (newInterval[0] > intervals[i][1]) && (i+1 >= intervals.size() || newInterval[1] < intervals[i+1][0])){
			ans.push_back(intervals[i]);
			ans.push_back(vector<int>{newInterval[0], newInterval[1]});
			for(int j=i+1; j<intervals.size(); j++)
				ans.push_back(intervals[j]);
			return ans;
		}else if(l == -1 && i == 0 && newInterval[1] < intervals[i][0]){
			ans.push_back(vector<int>{newInterval[0], newInterval[1]});
			for(int j=i; j<intervals.size(); j++)
				ans.push_back(intervals[j]);
			return ans;
		}else if(l == -1 && newInterval[0] < intervals[i][0] && newInterval[1] > intervals[i][1]){
			l = newInterval[0];
			r = newInterval[1];
		}else{
			ans.push_back(intervals[i]);
		}
	}
	ans.push_back(vector<int>{l, r});
	return ans;
}

vector<vector<int> > Solution2(vector<vector<int> > &intervals, vector<int> newInterval){
	vector<vector<int> > ans;
	if(intervals.empty()){
		ans.push_back(newInterval);
		return ans;
	}else if(newInterval.empty()){
		return intervals;
	}
	
	int i = 0;
	while(i < intervals.size() && intervals[i][1] < newInterval[0]){
		ans.push_back(intervals[i++]);
	}
	while(i < intervals.size() && intervals[i][0] <= newInterval[1]){
		newInterval[0] = min(intervals[i][0], newInterval[0]);
		newInterval[1] = max(intervals[i][1], newInterval[1]);
		i++;
	}
	ans.push_back(newInterval);
	while(i < intervals.size()){
		ans.push_back(intervals[i++]);
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<vector<int> > intervals(T, vector<int>(2));
	for(auto &interval: intervals)
		cin >> interval[0] >> interval[1];
	vector<int> newInterval(2);
	cin >> newInterval[0] >> newInterval[1];

	vector<vector<int> > ans = Solution(intervals, newInterval);
	for(auto &a: ans)
		cout << a[0] << " " << a[1] << endl;
	
	vector<vector<int> > ans2 = Solution2(intervals, newInterval);
	for(auto &a: ans2)
		cout << a[0] << " " << a[1] << endl;

}
