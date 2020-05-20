/*
 * Naive Solution:
 * Simply put all numbers into array and sort them, then link and output
 * Time complexity: O(nlogn), n is number of the numbers
 *
 *
 * Put numbers one by one:
 * Each time, compare all the heads of all linked lists, then put the smallest one to the answer list
 * Let k be the total number of lists in the array
 * Time complexity: O(k*n), since each number should be put into the answer, and before putting a number, we compare k numbers a time, so we will compare n*k times
 *
 *
 * Priority Queue + Put number one by one:
 * It's not hard to come up with the idea of using a priority queue to save time of searching for the least number
 * By the priority queue, extracting the least number will become O(1)
 * However, we should spend O(logk) each time for inserting a number to the heap (the next element of the element that has been popped out)
 * Time complexity: O(n*logk)
 * Space complexity: O(k) (run-time)
 *
 *
 * Inspiration from Merge Sort (Solution2):
 * We can view each list as the element of an array (actually, it is so)
 * And then sort them as we use merge sort to sort an array
 * Split the array until there is only one list left
 * Like merge sort, a single number will directly return, since it's already sorted
 * The single list in the array now is already sorted as well, so we can directly return it, too
 * Then we merge all lists pair by pair, level by level until reach the root
 * 
 * Time complexity: O(n*logk), each level has n elements to compare and put, and we have logk levels in total
 * Space complexity: O(1)
 *
 * */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct ListNode{
	int val;
	ListNode *next;
	ListNode(int _val): val(_val), next(NULL){}
};

vector<ListNode*> BuildList(vector<vector<int> > &nums){
	vector<ListNode*> lists;
	for(int i=0; i<nums.size(); i++){
		ListNode *head = NULL, *tail = NULL;
		for(int j=0; j<nums[i].size(); j++){
			if(!head){
				head = new ListNode(nums[i][j]);
				tail = head;
			}else{
				tail->next = new ListNode(nums[i][j]);
				tail = tail->next;
			}
		}
		lists.push_back(head);
	}
	return lists;
}

struct cmp{
	bool operator()(const ListNode *a, const ListNode *b){
		return a->val > b->val;
	}
};

ListNode* Solution(vector<ListNode*> &lists){
	priority_queue<ListNode*, vector<ListNode*>, cmp> pq;
	for(int i=0; i<lists.size(); i++){
		if(lists[i]) pq.push(lists[i]);
	}
	ListNode *ans = NULL, *tail = NULL;
	while(!pq.empty()){
		if(!ans){
			ans = pq.top();
			tail = ans;
			if(pq.top()->next) pq.push(pq.top()->next);
			pq.pop();
		}else{
			tail->next = pq.top();
			tail = tail->next;
			if(pq.top()->next) pq.push(pq.top()->next);
			pq.pop();
		}
	}
	return ans;
}

ListNode* merge(vector<ListNode*> &lists, int l, int r){
	if(l == r) return lists[l];
	
	int mid = (r+l)/2;
	ListNode *L = merge(lists, l, mid);
	ListNode *R = merge(lists, mid+1, r);
	ListNode *head = NULL, *tail = NULL;
	while(L || R){
		if(L && R){
			if(L->val < R->val){
				if(!head){
					head = L;
					tail = head;
				}else{
					tail->next = L;
					tail = tail->next;
				}
				L = L->next;
			}else{
				if(!head){
					head = R;
					tail = head;
				}else{
					tail->next = R;
					tail = tail->next;
				}
				R = R->next;
			}
		}else if(L){
			if(!head){
				head = L;
				tail = head;
			}else{
				tail->next = L;
				tail = tail->next;
			}
			L = L->next;
		}else if(R){
			if(!head){
				head = R;
				tail = head;
			}else{
				tail->next = R;
				tail = tail->next;
			}
			R = R->next;
		}
	}
	return head;
}

ListNode* Solution2(vector<ListNode*> &lists){
	if(lists.empty()) return NULL;
	return merge(lists, 0, lists.size()-1);
}

int main(){
	int T;
	cin >> T;
	vector<vector<int> > nums(T);
	for(int i=0; i<T; i++){
		int tmp;
		cin >> tmp;
		for(int j=0; j<tmp; j++){
			int ipt;
			cin >> ipt;
			nums[i].push_back(ipt);
		}
	}
	vector<ListNode*> lists = BuildList(nums);
	ListNode *ans = Solution2(lists);
	while(ans){
		cout << ans->val << " ";
		ans = ans->next;
	}cout << endl;
}
