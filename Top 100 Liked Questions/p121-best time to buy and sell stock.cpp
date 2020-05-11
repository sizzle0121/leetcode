/*
	Brute-force method is O(n^2)

	Greedy:
	Initialize maximum as 0, since if every transaction will lose our money, we do nothing
	The maximum should be updated by max(currentMax, prices[i] - minBuy)
	minBuy is the minimum price from day 1 to day i
	if we want to make more profit, we either can find greater price in the following days or find lower price to buy and wait until (price - lower price we found) greater than the maximum

	Time complexity: O(n)

*/
#include <iostream>
#include <vector>

using namespace std;

int Solution(vector<int> &prices){
	int minBuy = prices[0], ans = 0;
	for(int i=1; i<prices.size(); i++){
		if(prices[i] < minBuy)	minBuy = prices[i];
		if(ans < prices[i]-minBuy)	ans = prices[i]-minBuy;
	}
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> prices(T);
	for(int i=0; i<T; i++)
		cin >> prices[i];
	cout << Solution(prices) << endl;
	return 0;
}
