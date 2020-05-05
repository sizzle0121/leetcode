/*
	A Classic DP Problem:
	Optimal Substructure
	fewest(i) = min( fewest(i), fewest(i - coins[j]) + 1)
	The one-step difference: the fewest number of amount i will be the minimum of the fewest( taking a type of coin[j] away )+1

	Time complexity: O(amount * S), where S is the total types of coins
	Space complexity: O(amount)

	*	use coin types as outer loop and amount in the inner loop will be faster
		for(int i=0; i<coins.size(); i++){
			for(int j=coins[i]; j<=amount; j++){
				dp[j] = min(dp[j], dp[j-coins[i]] + 1);
			}
		}
*/
#include <iostream>
#include <vector>
using namespace std;

int Solution(vector<int> &coins, int amount){
	if(coins.empty())	return -1;
	vector<int> dp(amount+1, amount+1);
	dp[0] = 0;
	for(int i=1; i<=amount; i++){
		for(int j=0; j<coins.size(); j++){
			if(i >= coins[j])
				dp[i] = min(dp[i], dp[i - coins[j]] + 1);
		}
	}
	return dp[amount] > amount? -1 : dp[amount];
}

int main(){
	int T, amount;
	cin >> T;
	vector<int> coins(T);
	for(int i=0; i<T; i++)
		cin >> coins[i];
	cin >> amount;
	cout << Solution(coins, amount) << endl;
}
