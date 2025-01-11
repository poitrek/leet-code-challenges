#include <iostream>
#include <string>

using namespace std;


class Solution {
public:
    string intToRoman(int num) {
        std::string unit[] = { "", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };
		std::string dozen[] = { "", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC" };
		std::string hundred[] = { "", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM" };
		std::string thousand[] = { "", "M", "MM", "MMM" };
		std::string result = "";
		/// Add units
		result = unit[num % 10] + result;
		num /= 10;
		result = dozen[num % 10] + result;
		num /= 10;
		result = hundred[num % 10] + result;
		num /= 10;
		result = thousand[num % 10] + result;
		return result;
    }
};

int main() {

	return 0;
}
