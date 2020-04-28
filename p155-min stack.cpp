/*
	Main idea:
		When we pop out the current minimum, we should update our minimum to the popped stack
		That is, the minimum from 0 to top-1, let's say it's at position i
		If next time, i is popped out, we should update the minimum to [0, i-1]
		Therefore, we need to save the second smallest value under every position of the minimum
		Use another stack to push the new minimum when it is pushed into the original stack
		So we will have the second smallest one for each minimum value on top of it

	Time complexity: O(1)
*/
#include <iostream>
#include <sstream>
#include <string>
#include <stack>
using namespace std;

class MinStack{
public:
	MinStack(){}
	void push(int x){
		ctn.push(x);
		if(mini.empty() || x <= getMin())
			mini.push(x);
	}

	void pop(){
		if(ctn.top() == mini.top())
			mini.pop();
		ctn.pop();
	}

	int top(){
		return ctn.top();
	}

	int getMin(){
		return mini.top();	
	}

private:
	stack<int> ctn;
	stack<int> mini;
};

int main(){
	MinStack *obj = new MinStack;
	while(1){
		string cmd;
		cin >> cmd;
		if(cmd[10] == 'u'){
			cmd.insert(14, " ");
			stringstream ss;
			ss << cmd;
			string trash;
			int value;
			ss >> trash;
			ss >> value;
			obj->push(value);
		}else if(cmd[9] == 'p' && cmd[10] == 'o'){
			obj->pop();
		}else if(cmd[9] == 't' && cmd[10] == 'o'){
			cout << obj->top() << endl;
		}else if(cmd[9] == 'g'){
			cout << obj->getMin() << endl;
		}
	}
}
