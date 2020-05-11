#include <iostream>

using namespace std;

struct ListNode {
	int val;
 	ListNode *next;
 	ListNode(int x) : val(x), next(NULL) {}
 };

ListNode* CreateListNum(long long num){
	ListNode *front = new ListNode(num%10);
	ListNode *rear = front;
	num /= 10;
	while(num > 0){
		rear->next = new ListNode(num%10);
		rear = rear->next;
		num /= 10;
	}
	return front;
}

void OutputList(ListNode *l){
	int num[200], i = 0;
	while(l){
		num[i++] = l->val;
		l = l->next;
	}
	for(i=i-1; i>=0; i--)
		cout << num[i];
	cout << endl;
}

int main(){
	long long num1, num2;
	//if num1/num2 is zero, just output the other one
	cin >> num1 >> num2;
	ListNode *l1 = CreateListNum(num1), *l2 = CreateListNum(num2);
	
	//add two numbers
	ListNode *ans = NULL, *rear = NULL;
	bool flag = true;//first node
	int c = 0;
	while(l1 != NULL || l2 != NULL){
		int v;
		if(!l1){
			v = l2->val + c;
			l2 = l2->next;
		}else if(!l2){
			v = l1->val + c;
			l1 = l1->next;
		}else{
			v = l1->val + l2->val + c;
			l1 = l1->next;
			l2 = l2->next;
		}
		c = v/10;
		if(flag){
			flag = false;
			ans = new ListNode(v%10);
			rear = ans;
		}else{
			rear->next = new ListNode(v%10);
			rear = rear->next;
		}
	}
	if(c > 0)	rear->next = new ListNode(c);
	OutputList(ans);
	
	return 0;
}
