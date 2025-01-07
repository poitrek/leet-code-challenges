#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
	struct Step {
		int height;
		int length;
		Step(int height_, int length_) : height(height_), length(length_) {}
	};

    int trap(vector<int>& height) {
        stack<Step> st;
		// Guard step - avoid checking if the stack is empty
		st.push({0, 1});
		int sum = 0;
		for (int h : height) {
			if (h == st.top().height) {
				st.top().length++;
				continue;
			}
			if (h < st.top().height) {
				st.push({h, 1});
				continue;
			}
			// h > st.top().height
			while (h > st.top().height) {
				if (st.size() == 1) {
					st.pop();
					st.push({h, 1});
					break;
				}
				Step valley = st.top();
				st.pop();
				int min_edge = min(st.top().height, h);
				int diff = min_edge - valley.height;
				sum += valley.length * diff;
				if (h > st.top().height)
					st.top().length += valley.length;
				else if (h == st.top().height)
					st.top().length += valley.length + 1;
				else
					st.push({h, valley.length + 1});
			}
		}
		return sum;
    }
};

int main() {

	return 0;
}
