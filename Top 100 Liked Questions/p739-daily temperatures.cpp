/*
 * Tivial Solution (TLE):
 * For each day i, look from i+1 to end() for the first T[j] > T[i]
 *
 * Time complexity: O(n^2)
 *
 * 
 * Stack:
 * When the curve is descending, no temperatures are warmer than before\ 
 * Once the curve is ascending, we can update all temperatures before which are lower than the current temperature\ 
 * Then the current temperature will be the lowest temperature when it update all temperatures that are lower than it
 * After that, we continue to find the next ascending point
 * All of the above is exactly a stack manipulation\ 
 * When the curve is descending, we keep pushing temperatures into the stack\ 
 * Once we meet the first temperature that is warmer than stack.top(), we start updating ans[index(stack.top())] and popping the stack
 * After the stack.top() > current temperature, we push current temperature into stack\ 
 * When the array is scanned, answer of the rest temperatures in the stack should be update to zero (no warmer temperatures present after them) 
 *
 * Time complexity: O(n)
 *
 * */
#include <iostream>
#include <vector>
#include <stack>
#include <utility>
using namespace std;

vector<int> Solution(vector<int> &T){
	vector<int> ans(T.size());
	for(int i=0; i<T.size(); i++){
		for(int j=i+1; j<T.size(); j++){
			if(T[j] > T[i]){
				ans[i] = j-i;
				break;
			}
		}
	}
	return ans;
}

vector<int> Solution2(vector<int> &T){
	stack<pair<int, int> > buf;//idx, temperature
	buf.push(pair<int,int>(0, T[0]));
	vector<int> ans(T.size());
	for(int i=1; i<T.size(); i++){
		if(T[i] <= buf.top().second)
			buf.push(pair<int,int>(i, T[i]));
		else{
			while(!buf.empty() && T[i] > buf.top().second){
				ans[buf.top().first] = i - buf.top().first;
				buf.pop();
			}
			buf.push(pair<int,int>(i, T[i]));
		}
	}
	while(!buf.empty()){
		ans[buf.top().first] = 0;
		buf.pop();
	}
	return ans;
}

int main(){
	int n;
	cin >> n;
	vector<int> T(n);
	for(int i=0; i<n; i++)
		cin >> T[i];
	vector<int> ans = Solution(T);
	vector<int> ans2 = Solution2(T);
	for(int i=0; i<ans.size(); i++)
		cout << ans[i] << " ";
	cout << endl;
	for(int i=0; i<ans2.size(); i++)
		cout << ans2[i] << " ";
	cout << endl;
}
