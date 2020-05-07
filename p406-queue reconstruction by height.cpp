/*
	Since taller people are independent with the shorter (k value only restricts >= h)\ 
	we start from tallest people to the shortest one (the shorter can be inserted to their appropiate positions arbitrarily when all the taller are placed)
	In order to do so, sort them first according to their h value then their k value if the h value is equal
	Then we update all k value to (k - number of people with the same height in front of the person) (since we already sort them by their k value, the 'equal' part is done)
	Now, we only have to move them backward k' positions to finish this problem 

	Time complexity: O(nlogn + n + n^2) = O(n^2)
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct cmp{
	bool operator()(vector<int> &a, vector<int> &b){
		if(a[0] != b[0])	return a[0] < b[0];
		else	return a[1] < b[1];
	}
};

vector<vector<int> > Solution(vector<vector<int> > &people){
	if(people.empty())	return people;
	sort(people.begin(), people.end(), cmp());//sort by h then k
	int h = people[0][0], cnt = 1;
	vector<int> gt(people.size());
	gt[0] = people[0][1];
	for(int i=1; i<people.size(); i++){//update k to k' (minus the equal part)
		if(h == people[i][0]){
			gt[i] = people[i][1] - cnt;
			cnt++;
		}else{
			gt[i] = people[i][1];
			h = people[i][0];
			cnt = 1;
		}
	}
	for(int i=people.size()-1; i>=0; --i){//move backward k' pos
		int cur = i;
		while(gt[i]--){
			swap(people[cur], people[cur+1]);
			cur++;
		}
	}
	return people;
}

int main(){
	int T;
	cin >> T;
	vector<vector<int> > people(T, vector<int>(2));
	for(int i=0; i<T; i++)
		cin >> people[i][0] >> people[i][1];
	vector<vector<int> > ans = Solution(people);
	for(int i=0; i<ans.size(); i++){
		cout << '[' << ans[i][0] << " " << ans[i][1] << ']' << " ";
	}cout << endl;
}
