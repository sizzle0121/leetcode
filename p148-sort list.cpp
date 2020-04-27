/*
	Merge Sort:
	iterate through the list and count the length for splitting
	left = head, right = the node at length/2, remember to set the tail of left to NULL
	When merge, simply relink the nodes according to their value (thus, no extra space)

	Time complexity: O(nlogn)
	Space complexity: O(1)
*/
#include <iostream>
#include <vector>
using namespace std;

struct ListNode{
	int val;
	ListNode *next;
	ListNode(int _val): val(_val), next(NULL){}
};

ListNode* BuildList(vector<int> &nums){
	if(nums.empty())	return NULL;
	ListNode *head = NULL, *tail = NULL;
	for(int i=0; i<nums.size(); i++){
		if(!head){
			head = new ListNode(nums[i]);
			tail = head;
		}else{
			tail->next = new ListNode(nums[i]);
			tail = tail->next;
		}
	}
	return head;
}

ListNode* Solution(ListNode *head){
	//Split
	int len = 0;
	ListNode *tmp = head;
	while(tmp){
		len++;
		tmp = tmp->next;
	}
	ListNode *left = head, *right = head, *prev = NULL;
	for(int i=0; i<len/2; i++){
		prev = right;
		right = right->next;
		if(i == (len/2)-1)	prev->next = NULL;//should set the tail of left to NULL
	}
	
	if(left == right)	return head;
	left = Solution(left);
	right = Solution(right);

	//Merge
	ListNode *tail = NULL, *ans = NULL;
	while(left && right){	
		if(left->val < right->val){
			if(!tail){
				tail = left;
				ans = tail;
			}else{
				tail->next = left;
				tail = tail->next;
			}
			left = left->next;
		}else{
			if(!tail){
				tail = right;
				ans = tail;
			}else{
				tail->next = right;
				tail = tail->next;
			}
			right = right->next;
		}
	}
	if(left)	tail->next = left;
	if(right)	tail->next = right;
	return ans;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	ListNode *head = BuildList(nums);
	ListNode *ans = Solution(head);
	while(ans){
		cout << ans->val << " ";
		ans = ans->next;
	}cout << endl;
}
