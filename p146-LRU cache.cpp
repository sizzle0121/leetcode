/*
	The key point to achieve O(1) time complexity of both get and put operation is to find the existing key and update it
	Since singly linked list should travel to the position and then delete the node and insert it to the head
	Even if we save pointers to hashmap, we still need to know which node is behind the node we want to update or we cannot delete it and link the nodes front and behind it
	Therefore, we use doubly linked list here to solve the above problem

	Time complexity: O(1)
*/

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

struct ListNode{
	int val, key;
	ListNode *next;
	ListNode *back;
	ListNode(int _key, int _val): val(_val), key(_key), next(NULL), back(NULL){}
};

class LRUCache{
public:
	LRUCache(int capacity)
	: Cap(capacity), curCap(0), head(NULL), tail(NULL){}
	
	void UpdateOrder(ListNode *node){
		if(head != node){
			if(node->back)	node->back->next = node->next;
			if(node->next)	node->next->back = node->back;
			if(node == tail)	tail = node->back;
			node->next = head;
			head->back = node;
			node->back = NULL;
			head = node;
		}
	}

	int get(int key){	
		if(hashTable.find(key) != hashTable.end()){
			UpdateOrder(hashTable[key]);
			return hashTable[key]->val;
		}else{
			return -1;
		}
	}
	
	void put(int key, int value){
		if(curCap < Cap){
			if(hashTable.find(key) == hashTable.end()){
				ListNode *node = new ListNode(key, value);
				if(!head){
					head = node;
					tail = node;
				}else{
					node->next = head;
					head->back = node;
					head = node;
				}
				hashTable[key] = node;
				curCap++;
			}else{
				UpdateOrder(hashTable[key]);
				hashTable[key]->val = value;
			}
		}else{
			if(hashTable.find(key) == hashTable.end()){
				if(head == tail){
					hashTable.erase(tail->key);
					ListNode *node = new ListNode(key, value);
					head = node;
					tail = node;
					hashTable[key] = node;
				}else{
					tail->back->next = tail->next;
					hashTable.erase(tail->key);
					tail = tail->back;
					ListNode *node = new ListNode(key, value);
					node->next = head;
					head->back = node;
					head = node;
					hashTable[key] = node;
				}
			}else{
				UpdateOrder(hashTable[key]);
				hashTable[key]->val = value;
			}
		}
	}

	void OutputList(){
		ListNode *tmp = head;
		while(tmp){
			cout << tmp->val << " ";
			tmp = tmp->next;
		}
		cout << endl << "head: " << head->val << " tail: " << tail->val << endl;
	}

private:
	int Cap, curCap;
	unordered_map<int, ListNode*> hashTable;
	ListNode *head, *tail;
};

int main(){
	int capacity;
	cin >> capacity;
	cin.ignore();
	LRUCache *obj = new LRUCache(capacity);
	while(1){
		string cmd;
		getline(cin, cmd);
		cmd.insert(10, " ");
		stringstream ss(cmd);
		if(cmd[6] == 'p'){
			string trash;
			ss >> trash;
			int key, val;
			ss >> key;
			ss >> trash;
			ss >> val;
			obj->put(key, val);
			obj->OutputList();
		}else if(cmd[6] == 'g'){
			string trash;
			ss >> trash;
			int key;
			ss >> key;
			cout << obj->get(key) << endl;
			obj->OutputList();
		}
		
	}
	return 0;
}
