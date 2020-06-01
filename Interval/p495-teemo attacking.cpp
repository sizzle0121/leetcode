/*
 * Interval Overlapped Question:
 * General idea:
 * Determine if i and i+1 are overlapped or not
 * If overlapped, merge, if not update the answer
 *
 * For this problem:
 * The "merge" step becomes calculate the total duration of the overlapped intervals
 * And we can simply record the initial time when overlap occurs\ 
 * When no overlap, update the answer by adding previous overlapped time series\ 
 * (by calculating the difference of the end and the initial time + 1)
 * 
 * Time complexity: O(n)
 * Space complexity: O(1)
 *
 * */
#include <iostream>
#include <vector>
using namespace std;

int Solution(vector<int >&timeSeries, int duration){
	if(timeSeries.empty() || duration == 0) return 0;
	int ans = 0, start = -1;
	for(int i=0; i<timeSeries.size(); i++){
		unsigned long long tmp = timeSeries[i] + duration - 1;
		if(i+1 < timeSeries.size() && tmp >= timeSeries[i+1] && start == -1){
			start = i;
		}else if(i+1 >= timeSeries.size() || tmp < timeSeries[i+1]){
			if(start != -1) ans += tmp - timeSeries[start] + 1;
			else ans += tmp - timeSeries[i] + 1;
			start = -1;
		}
	}
	return ans;
}                

int main(){
	int T, duration;
	cin >> T;
	vector<int> timeSeries(T);
	for(auto &t: timeSeries)
		cin >> t;
	cin >> duration;
	cout << Solution(timeSeries, duration) << endl;
}
