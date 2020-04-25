/*
	first, copy the normal linked list (next pointer), and build hash table with [original address, new copy address]
	then we finish the random pointers of copy list by the hash table

	Time complexity: O(n)
*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        map<Node*,Node*> idx;
        Node *itr = head;
        Node *ans = NULL, *tail = NULL;
        while(itr){
            if(!ans){
                ans = new Node(itr->val);
                tail = ans;
            }else{
                tail->next = new Node(itr->val);
                tail = tail->next;
            }
            Node *tmp = tail;
            idx[itr] = tmp;
            itr = itr->next;
        }
        itr = head;
        tail = ans;
        while(itr){
            if(itr->random){
                tail->random = idx[itr->random];
            }
            itr = itr->next;
            tail = tail->next;
        }
        return ans;
    }
};
