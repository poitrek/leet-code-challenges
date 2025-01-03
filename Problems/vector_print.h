#include <vector>
#include <ostream>

template<typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& v) {
    o << "[";
    for (const auto &item : v) {
        o << item << " ";
    }
    o << "]";
    return o;
}
