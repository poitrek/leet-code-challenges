#include <iostream>
#include <queue>

using namespace std;

class MyStack {
    queue<int> q;
public:
    MyStack() {}
    
    void push(int x) {
		int s = q.size();
        q.push(x);
		for (int _ = 0; _ < s; _++) {
			q.push(q.front());
			q.pop();
		}
    }
    
    int pop() {
        int x = q.front();
		q.pop();
		return x;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

int main(){

	return 0;
}
