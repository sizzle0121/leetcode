/*
 * First Solution is wrong, since if all the slots of the largest task are full, the rest of the\ 
 * task should be inserted into the back of each slot, not the back of the largest task and do the same thing again
 * Inserting to the back of each slot can prevent from collision as well as producing additional idle when we do the same thing at the back of the largest task
 * Solution3 is its correct version:
 * First we calculate the time that we at least need to process the largest task\ 
 * which is (M-1) * n + M-1(itself) = (M-1)*(n+1), M is the count of the largest task
 * then add others tasks which have the same size as the largest tasks (append at the back)
 * If the above time < tasks.size()
 * tasks.size() will be our answer, since as we mentioned before, the rest of the tasks can be inserted into the back of each slot
 *
 * Time complexity: O(n)
 *
 *
 * Solution2:
 * The key point is to make ilde time as short as possible\ 
 * In other words, we have to diversify the rest of the tasks, since if all remain tasks are the\ 
 * same, the CPU will have lots of time being idle
 * Therefore, in every interval (cycle), we must first consume the largest task, or it will make the rest of tasks all the same\ 
 * This can be done by using priority queue to store the count of each task
 * In each interval, we can only consume the same task once, since no tasks can be processed within the same n timesteps twice --- (1)
 * Thus, we minus the counts of tasks by 1, then pop them out from the queue\ 
 * After the interval, we then push them back and make ans += interval\ 
 * (if types of tasks < interval, we still need to add the whole interval, since (1) )
 * If all counts of tasks become 0, ans += (number of tasks being processed this interval)
 *
 * Time complexity: O(the total timesteps) = O(answer)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
using namespace std;

struct cmp{
	bool operator()(const pair<char,int> &a, const pair<char,int> &b){
		return a.second < b.second;
	}
};

int Solution(vector<char> &tasks, int n){
	vector<pair<char,int> > cnt(26, pair<char,int>('#', 0));
	for(int i=0; i<tasks.size(); i++){
		cnt[tasks[i] - 'A'].first = tasks[i];
		cnt[tasks[i] - 'A'].second++;
	}
	for(int i=0; i<26; i++){
		cout << cnt[i].first << " " << cnt[i].second << endl;
	}
	priority_queue<pair<char,int>, vector<pair<char,int> >, cmp> pq(cnt.begin(), cnt.end());
	int ans = 0;
	vector<pair<char,int> > buffer;
	while(!pq.empty() && pq.top().second != 0){
		pair<char,int> p = pq.top();
		pq.pop();

		int interval = (p.second-1) * n, gap = p.second-1;
		ans += p.second + interval;
		while(interval && pq.top().second != 0){
			pair<char,int> tmp = pq.top();
			pq.pop();
			if(tmp.second >= interval){
				tmp.second -= interval;
				pq.push(tmp);
				interval = 0;
			}else if(tmp.second > gap){
				tmp.second -= gap;
				buffer.push_back(tmp);
				interval -= gap;
			}else{
				interval -= tmp.second;
			}
		}
		while(!buffer.empty()){
			pq.push(buffer.back());
			buffer.pop_back();
		}
	}
	return ans;
}

int Solution3(vector<char> tasks, int n){
	int ans = 0, max_count = 0;
	vector<int> cnt(26);
	for(int i=0; i<tasks.size(); i++){
		cnt[tasks[i] - 'A']++;
		max_count = max(max_count, cnt[tasks[i] - 'A']);
	}
	ans += (max_count-1) * (n+1);
	for(int i=0; i<26; i++){
		if(cnt[i] == max_count)
			ans++;
	}
	return tasks.size()>ans? tasks.size():ans;
}

int Solution2(vector<char> tasks, int n){
	vector<int> cnt(26);
	for(int i=0; i<tasks.size(); i++)
		cnt[tasks[i] - 'A']++;
	
	priority_queue<int> pq;
	for(int i=0; i<cnt.size(); i++){
		if(cnt[i])	pq.push(cnt[i]);
	}
	int ans = 0, interval = n+1, rest;
	vector<int> buffer;
	while(!pq.empty()){
		rest = 0;
		for(int i=0; i<interval; i++){
			if(!pq.empty()){
				if(pq.top()-1 > 0)
					buffer.push_back(pq.top()-1);
				rest++;
				pq.pop();
			}
		}
		while(!buffer.empty()){
			pq.push(buffer.back());
			buffer.pop_back();
		}
		ans += !pq.empty()? interval : rest;
	}
	return ans;
}

int main(){
	int T, n;
	cin >> T;
	vector<char> tasks(T);
	for(int i=0; i<T; i++){
		cin >> tasks[i];
	}
	cin >> n;
	cout << Solution3(tasks, n) << endl;
}
