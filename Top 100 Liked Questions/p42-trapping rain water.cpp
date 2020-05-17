/*
 * Stack:
 * Find all peaks by following the trend of ascending or descending
 * For peaks, scan through the peaks\ 
 * If the right peak is lower than the top of the stack, push it into the stack
 * Once the right peak is higher than the top of the stack, replace the top() by popping it out until the top() is >= the current one
 * Why replace?
 * Since all the lower peak will become part of the bottom of the trap formed by the current higher one as the right bound\ 
 * and the top() that it cannot replace as the left bound
 * For example:
 * 5 3 1 2 1 5
 * The peaks are 5, 2, 5, and the 2 will become part of the bottom of the trap [5, 5]
 *
 * If the top() is the only element now in the stack, then we can already calculate the trap [top(), current] adding it to the answer
 * since if the right peak with height >= the left one, the trap with the left one as the left bound is already concluded
 * (even a higher peak presents later, it can still form a trap with the leftmost right peak with height >= it\ 
 * (cannot go accross it to form a trap with the higher one))
 * For example:
 * 2 1 4 1 8
 * The peaks are 2, 4, 8, and when the 4 presents, the trap of [2, 4] is already concluded (8 cannot form a trap with 2)
 *
 * After scan throught all peaks, the remains in the stack are the peaks that can be replaced by none of the peaks at the right of them
 * But there are no more peak, so we also can concluded that they can simply form a trap with the peak right aside them
 *
 *
 *
 * Time complexity: find peak=O(n), replace peak=O(2*k), k: number of peaks < n, calculate remaining peaks O(n)
 * Therefore, O(n)
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <stack>
using namespace std;

int Solution(vector<int> &height){
	int ans = 0;
	if(height.empty())	return ans;
	bool ascend = true;
	vector<pair<int,int> > peak;//h, pos
	for(int i=0; i<height.size(); i++){//find all peaks
		if(i+1 < height.size() && height[i+1] < height[i]){
			if(ascend){
				peak.push_back(pair<int,int>(height[i], i));
			}
			ascend = false;
		}else if(i+1 < height.size() && height[i+1] > height[i]){
			ascend = true;
		}else if(i == height.size()-1 && ascend){
			peak.push_back(pair<int,int>(height[i], i));
		}
	}
	stack<pair<int,int> > buf;
	buf.push(peak[0]);
	for(int i=1; i<peak.size(); i++){
		while(!buf.empty() && peak[i].first > buf.top().first){//replace peaks if the right one is higher
			if(buf.size() == 1){//if it's leftmost, calculate and add to the answer
				int L = buf.top().second, R = peak[i].second;
				while(height[R-1] >= height[L])	R--;
				ans += (R-L-1) * height[L];
				for(int j=L+1; j<R; j++)
					ans -= height[j];
			}
			buf.pop();
		}
		buf.push(peak[i]);
	}
	while(buf.size() > 1){//the remains are all that peaks at their right side cannot replace them
		int R = buf.top().second;//calculate and add to the answer
		buf.pop();
		int L = buf.top().second;
		while(height[L+1] >= height[R])	L++;
		ans += (R-L-1) * height[R];
		for(int j=L+1; j<R; j++)
			ans -= height[j];
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> height(T);
	for(auto &h: height)
		cin >> h;
	cout << Solution(height) << endl;
}
