/*
	Brute-force:
	Try every action in each day (buy, sell, cooldown)
	Time complexity: O(3^n)


	DP:
	dp[i] is the max profit if we buy the stock on day i
	Starting from the back, for every i, we need to find the max( selling prices + max( dp[the day after the tomorrow of selling day] ) )
	Why the day after tomorrow of selling? because we have to cool down a day after selling
	For example, if we buy the stock on day i, and sell it at day j, the selling price is prices[j] - prices[i]
				 and then we need to find the max dp value from j+2 to N-1
				 after that, we compare to other previous (selling prices + max dp) and finally obatin max dp[i]
	By doing so and updating the answer, we can get the maximum profit

	There is a trick to further speed up the above method (the above method will TLE)
	We have to repeat finding the max dp when we determined a selling day (find from day j+2 to N-1)
	If we store the max dp[j+2] in each j we can save the time
	Therefore, I set dp[i].first be the original dp value, and dp[i].second be the max dp value from i+2 to N-1
	Next time, if we want to sell a stock at day i, we can directly get the max dp after i+2 (no need to find)
	
	Time complexity: O(n^2)



	State-Machine (Sol.2):
	We have three states, S0: Hold Money; S1: After Buying stock from S0; S2: After Selling stock from S1
	For S0, we can only come from keep holding money (S0 -> S0), or after cooldown (S2 -> S0)
	For S1, we can only come from buying a stock (S0 -> S1), or after buying and wait (S1 -> S1)
	For S2, we can only come from selling a stock (S1 -> S2)

	At the beginning, we start at each of them respectively
	Initialize:
	S0 = 0
	S1 = -prices[0]
	S2 = -inf (since we cannot sell a stock without buying a stock)

	Each time, we update three of the states value by picking the maximum of the coming states\ 
	since in this way, we can make the value of each state at time i be the maximum value at that time
	Therefore, at the end, each state will still has the maximum value at that time, and we can simply choose the greatest one to be our answer (since the maximum must not be the state after we buying a stock, we can only consider S0 and S2)
	
	Time complexity: O(n)
*/
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int Solution2(vector<int> &prices){
	if(prices.size() < 2)	return 0;
	int s0 = 0, s1 = -prices[0], s2 = -2147483647;
	for(int i=1; i<prices.size(); i++){
		int prev_s0 = s0;
		s0 = max(s0, s2);
		s1 = max(s1, prev_s0 - prices[i]);
		s2 = prices[i] + s1;
	}
	return max(s0, s2);
}

int Solution(vector<int> &prices){
	if(prices.size() < 2)	return 0;
	int N = prices.size(), ans = 0, tmpMax = 0;
	vector<pair<int,int> > dp(N);//(max value of buying i, max dp first value from i+2 to N-1) 
	for(int i=N-2; i>=0; --i){
		for(int j=i+1; j<N; j++){
			if(prices[j] > prices[i]){
				int tmp = prices[j] - prices[i];
				dp[i].first = max(dp[i].first, tmp + dp[j].second);
				//for(int k=j+2; k<N; k++){		Finding the max dp after j=2, can be speed up by the above
				//	dp[i].first = max(dp[i].first, tmp + dp[k].first);
				//}
			}
		}
		if(i < N-2)		dp[i].second = max(dp[i+1].second, dp[i+2].first);//dp[i+1].second contains max dp first value from i+3 to N-1, we compare it to dp[i+2].first to get the max dp value from i+2 to N-1
		ans = max(ans, dp[i].first);
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
	cout << Solution2(prices) << endl;
}
