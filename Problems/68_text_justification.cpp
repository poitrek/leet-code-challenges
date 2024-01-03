#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:	
	// Justifies a single line of given words and width. Assumes that the words can be fitted into the line
	string justifyLine(vector<string> &words, size_t pos_first, size_t pos_last, int lineWidth) {
		int n_word_letters = accumulate(words.begin() + pos_first, words.begin() + pos_last, 0, [](int sum, const string &s) {
			return sum + s.size();
		});
		int n_space_chars = lineWidth - n_word_letters;
		int n_spaces = pos_last - pos_first - 1;
		int space_width = n_space_chars / n_spaces;
		int remainder = n_space_chars % n_spaces;
		ostringstream oss;
		for (int i = 0; i < remainder; i++)
			oss << words[pos_first + i] << string(space_width + 1, ' ');
		oss << words[pos_first + remainder];
		for (int i = remainder + 1; i < n_spaces + 1; i++)
			oss << string(space_width, ' ') << words[pos_first + i];
		return oss.str();
	}

	string joinSpaces(const vector<string>& words, size_t pos_first, size_t pos_last, int lineWidth) {
		ostringstream oss;
		for (int i = pos_first; i < pos_last - 1; i++)
			oss << words[i] << " ";
		oss << words[pos_last - 1];
		string spaceFill(lineWidth - oss.str().size(), ' ');
		oss << spaceFill;
		return oss.str();
	}

    vector<string> fullJustify(vector<string>& words, int maxWidth) {
		vector<string> lines;
		size_t line_first_pos = 0;
		int line_size = -1;
		for (size_t cur_pos = 0; cur_pos < words.size(); cur_pos++) {
			line_size += words[cur_pos].size() + 1;
			if (line_size > maxWidth) {
				if (int n_words = cur_pos - line_first_pos; n_words > 1)
					lines.push_back(justifyLine(words, line_first_pos, cur_pos, maxWidth));
				else
					lines.push_back(joinSpaces(words, line_first_pos, cur_pos, maxWidth));
				line_first_pos = cur_pos;
				line_size = words[cur_pos].size();
			}
		}
		// the last line
		lines.push_back(joinSpaces(words, line_first_pos, words.size(), maxWidth));
		return lines;
    }

};

void test_join_spaces() {
	assert(Solution().joinSpaces({"abc", "de", "f"}, 0, 3, 10) == "abc de f  ");
}

int main() {
	test_join_spaces();
	// vector<string> ws1 = { "This", "is", "an", "example", "of", "text", "justification." };
	vector<string> ws1 = { "This", "is", "an", "example", "of", "text", "justification.", "The", 
	"thrill", "of", "gambling", "has", "existed", "in", "the", "entire", "history", "of", "mankind." };
	// cout << Solution().justifyLine(ws1, 0, 3, 0) << endl;
	auto lines1 = Solution().fullJustify(ws1, 30);
	for (auto line : lines1)
		cout << line << endl;
	// size_t n_word_letters = accumulate(ws1.begin() + 0, ws1.begin() + 2, 0, [](int sum, const string &s) {
	// 	return sum + s.size();
	// });
	// cout << n_word_letters << endl;
	return 0;
}
