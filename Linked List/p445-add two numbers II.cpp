#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct ListNode{
	int val;
	ListNode *next;
	ListNode(int _val): val(_val), next(NULL){}
};

ListNode* BuildList(vector<int> &num){
	if(num.empty())	return NULL;
	ListNode *head = NULL, *tail = NULL;
	for(auto &i: num){
		if(!head){
			head = new ListNode(i);
			tail = head;
		}else{
			tail->next = new ListNode(i);
			tail = tail->next;
		}
	}
	return head;
}

ListNode* reverseList(ListNode *head){
	ListNode *prev = NULL, *cur = head, *right = NULL;
	while(cur){
		right = cur->next;
		cur->next = prev;
		prev = cur;
		cur = right;
	}
	return prev;
}

ListNode* Solution2(ListNode *l1, ListNode *l2){
	l1 = reverseList(l1);
	l2 = reverseList(l2);
	ListNode *ans = NULL, *anstail = NULL;
	int c = 0;
	while(l1 || l2 || c != 0){
		c += l1? l1->val : 0;
		c += l2? l2->val : 0;
		if(!ans){
			ans = new ListNode(c%10);
			anstail = ans;
		}else{
			anstail->next = new ListNode(c%10);
			anstail = anstail->next;
		}
		c /= 10;
		if(l1)	l1 = l1->next;
		if(l2)	l2 = l2->next;
	}
	ans = reverseList(ans);
	return ans;
}

ListNode* Solution(ListNode *l1, ListNode *l2){
	vector<int> num1;
	vector<int> num2;
	vector<int> res;
	ListNode *ans = NULL, *anstail = NULL;
	while(l1){
		num1.push_back(l1->val);
		l1 = l1->next;
	}
	while(l2){
		num2.push_back(l2->val);
		l2 = l2->next;
	}
	int i = num1.size()-1, j = num2.size()-1, c = 0;
	while(i >= 0 || j >= 0 || c != 0){
		c += (i >= 0)? num1[i--] : 0;
		c += (j >= 0)? num2[j--] : 0;
		res.push_back(c%10);
		c /= 10;
	}
	while(!res.empty()){
		if(!ans){
			ans = new ListNode(res.back());
			anstail = ans;
		}else{
			anstail->next = new ListNode(res.back());
			anstail = anstail->next;
		}
		res.pop_back();
	}
	return ans;
}

int main(){
	int T1, T2;
	cin >> T1 >> T2;
	vector<int> num1(T1);
	vector<int> num2(T2);
	for(auto &i: num1)
		cin >> i;
	for(auto &i: num2)
		cin >> i;
	ListNode *head1 = BuildList(num1);
	ListNode *head2 = BuildList(num2);
	ListNode *ans = Solution(head1, head2);
	while(ans){
		cout << ans->val;
		ans = ans->next;
	}
	cout << endl;
	ListNode *ans2 = Solution2(head1, head2);
	while(ans2){
		cout << ans2->val;
		ans2 = ans2->next;
	}
	cout << endl;
}
