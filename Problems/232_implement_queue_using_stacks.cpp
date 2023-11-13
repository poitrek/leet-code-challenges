#include <iostream>
#include <stack>
using namespace std;

class MyQueue {
    stack<int> in;
    stack<int> out;
	
	void flip_stack() {
		while(!in.empty()) {
			out.push(in.top());
			in.pop();
		}
	}
public:
    MyQueue() {}
    
    void push(int x) {
        in.push(x);
    }
    
    int pop() {
        if (out.empty()) 
			flip_stack();
		int popout = out.top();
		out.pop();
		return popout;
    }
    
    int peek() {
		if (out.empty())
			flip_stack();
        return out.top();
    }
    
    bool empty() {
        return in.empty() && out.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

int main(){

	return 0;
}
