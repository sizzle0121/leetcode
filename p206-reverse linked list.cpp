/*
	Iterative Approach:
		Use three pointers, prev(ious), cur(runt), next
		Save the next and previous nodes, change the cur->next to previous, and move prev, cur to the right
		Return prev in the end
	
	Time complexity: O(n)

	Recursive Approach:
		First, set a pointer points to the tail of the list (which will be the head of the reverse linked list)
		The recursive function every time return the next(right) node, we change the "next node's next" to current node
		Also set current node's next to NULL (since the leftest node's next should be NULL)
		Then return current node(which will be the upper-level current node's next node)
		Eventually, return the very first tail pointer(now it's the head of the reverse linked list)

	Time complexity: O(n)

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
	if(!head)	return NULL;
	ListNode *prev = NULL, *cur = head, *next = NULL;
	while(cur){
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	return prev;
}

ListNode* reverse(ListNode *cur){
	if(!cur)	return NULL;
	ListNode *right = reverse(cur->next);
	if(right)	right->next = cur;
	cur->next = NULL;
	return cur;
}

ListNode *Solution2(ListNode *head){
	if(!head)	return NULL;
	ListNode *tail = head;
	while(tail->next)
		tail = tail->next;
	reverse(head);
	return tail;
}

int main(){
	int T;
	cin >> T;
	vector<int> nums(T);
	for(int i=0; i<T; i++)
		cin >> nums[i];
	ListNode *ans = Solution(BuildList(nums));
	ListNode *ans2 = Solution2(BuildList(nums));
	while(ans){
		cout << ans->val << " ";
		ans = ans->next;
	}cout << endl;

	while(ans2){
		cout << ans2->val << " ";
		ans2 = ans2->next;
	}cout << endl;
}
