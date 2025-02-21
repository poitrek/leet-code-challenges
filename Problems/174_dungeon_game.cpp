#include <algorithm>
#include <vector>

using namespace std;

/**
 * Beats 100% on time, 75.45% on memory
 * Time complexity: O(N*M), Space complexity: O(M)
 * (N - board height (dungeon.size()),
 * M - board width (dungeon[0].size()))
 * 
 * Idea: using Dynamic Programming, calculate minimal starting health for optimal path that starts
 * in specific cells, iterating Bottom -> Top and Right -> Left (from the "end")
 */
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {\
        int M = dungeon[0].size();
        vector<int> bestStartingHp(M, INT_MAX);
		bestStartingHp[M-1] = 1;
		for (auto row = dungeon.rbegin(); row != dungeon.rend(); ++row) {
			vector<int> newBestStartingHp(M+1, INT_MAX);
			for (int i = M - 1; i >= 0; i--) {
				newBestStartingHp[i] = max(1, min(bestStartingHp[i], newBestStartingHp[i+1]) - (*row)[i]);
			}
			bestStartingHp = std::move(newBestStartingHp);
		}
		return bestStartingHp.front();
    }
};

/**
 * Same as first, but optimized space - using only one vector bestStartingHp
 * Beats 100% time, 92.06% on memory
 */
class Solution2 {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int M = dungeon[0].size();
        vector<int> bestStartingHp(M+1, INT_MAX);
		bestStartingHp[M-1] = 1;
		for (auto row = dungeon.rbegin(); row != dungeon.rend(); ++row) {
			for (int i = M - 1; i >= 0; i--) {
				bestStartingHp[i] = max(1, min(bestStartingHp[i], bestStartingHp[i+1]) - (*row)[i]);
			}
		}
		return bestStartingHp.front();
    }
};

int main() {
	return 0;
}
