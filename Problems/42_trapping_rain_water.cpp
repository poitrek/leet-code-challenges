#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;


/**
 * @brief Two pointers technique
 * Time: O(N) (Beats 100%)
 *  Space: O(1)
 */
class Solution2 {
public:
	int trap(vector<int>& height) {
		/// LM - Left Max, RM - Right Max
		int LM_pos = 0;
		int RM_pos = height.size() - 1;
		int LM = height[LM_pos];
		int RM = height[RM_pos];
		int water = 0;
		int I_pos;
		bool from_left = (LM < RM);
		I_pos = from_left ? LM_pos : RM_pos;
		while (LM_pos != RM_pos) {
			if (from_left) {
				I_pos++;
				if (I_pos == RM_pos)
					break;
				if (height[I_pos] > LM) {
					LM_pos = I_pos;
					LM = height[I_pos];
					if (LM > RM) {
						from_left = false;
						I_pos = RM_pos;
					}
				}
				else {
					water += LM - height[I_pos];
				}
			}
			else {
				I_pos--;
				if (I_pos == LM_pos)
					break;
				if (height[I_pos] > RM) {
					RM_pos = I_pos;
					RM = height[I_pos];
					if (RM > LM) {
						from_left = true;
						I_pos = LM_pos;
					}
				}
				else {
					water += RM - height[I_pos];
				}
			}
		}
		return water;
	}
};


/**
 * @brief Solution with a stack
 * Time: probably O(N^2)
 * Space: O(N)
 */
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
	vector<int> v {0, 1, 10, 7, 13, 5, 5, 19, 7, 1, 20, 4, 5, 12, 6, 3, 9, 15, 20, 17, 16, 10, 11, 9, 13, 5, 1, 6};
	// vector<int> v {0, 6, 2, 4, 5, 3, 1, 7, 0};
	cout << Solution2().trap(v) << endl;
	return 0;
}
