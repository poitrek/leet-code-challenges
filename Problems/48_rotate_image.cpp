#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int N = matrix.size();
        int n_rings(std::ceil(0.5 * N));
        for (int ring_no = 0; ring_no < n_rings; ring_no++) {
            for (int offset = 0; offset < N - 1 - 2 * ring_no; offset++) {
                int *top = &matrix[ring_no][ring_no + offset];
                int *left = &matrix[N - 1 - ring_no - offset][ring_no];
                int *bottom = &matrix[N - 1 - ring_no][N - 1 - ring_no - offset];
                int *right = &matrix[ring_no + offset][N - 1 - ring_no];
                int top_val = *top;
                *top = *left;
                *left = *bottom;
                *bottom = *right;
                *right = top_val;
            }
        }
    }
	/// Slightly different alternative, differently defined offset
	void rotate2(vector<vector<int>>& matrix) {
        int N = matrix.size();
        int n_rings(std::ceil(0.5 * N));
        for (int ring_no = 0; ring_no < n_rings; ring_no++) {
            for (int offset = ring_no; offset < N - 1 - ring_no; offset++) {
                int *top = &matrix[ring_no][offset];
                int *left = &matrix[N - 1 - offset][ring_no];
                int *bottom = &matrix[N - 1 - ring_no][N - 1 - offset];
                int *right = &matrix[offset][N - 1 - ring_no];
                int top_val = *top;
                *top = *left;
                *left = *bottom;
                *bottom = *right;
                *right = top_val;
            }
        }
    }

};

int main() {

	return 0;
}
