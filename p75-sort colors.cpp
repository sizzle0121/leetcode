/*
	three pointers point to the place in which the next corresponding color can put
	move the first element of the next adjacent color to its last, and put the current color into the place its pointer points to

	Time complexity: O(n)
*/
#include <iostream>
#include <vector>

using namespace std;

void Solution(vector<int> &nums){
	int red = 0, white = 0, blue = 0;		
	for(int i=0; i<nums.size(); i++){
		if(nums[i] == 0){
			int save = nums[i];
			nums[blue++] = nums[white];
			nums[white++] = nums[red];
			nums[red++] = save;
		}else if(nums[i] == 1){
			int save = nums[i];
			nums[blue++] = nums[white];
			nums[white++] = save;
		}else{
			blue++;
		}
	}

	for(int i=0; i<nums.size(); i++)
		cout << nums[i] << " ";
	cout << endl;
}

int main(){
	int T, tmp;
	cin >> T;
	vector<int> nums;
	while(T--){
		cin >> tmp;
		nums.push_back(tmp);
	}
	Solution(nums);
	return 0;
}
