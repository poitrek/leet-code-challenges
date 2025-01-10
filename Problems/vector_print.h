#include <ostream>
#include <set>
#include <unordered_set>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& v) {
    o << "[";
    for (const auto &item : v) {
        o << item << " ";
    }
    o << "]";
    return o;
}

// #include <type_traits>
// template <typename T>
// concept Iterable = requires(T t) {
//     { t.begin() } -> std::same_as<typename T::iterator>;
//     { t.end() } -> std::same_as<typename T::iterator>;
// };

template<typename ContainerType>
std::ostream& printContainer(std::ostream& o, const ContainerType& c) {
    o << "{";
    for (const auto &item : c) {
        o << item << " ";
    }
    o << "}";
    return o;    
}

template<typename T>
std::ostream& operator<<(std::ostream& o, const std::unordered_set<T>& us) {
    return printContainer(o, us);
}

template<typename T>
std::ostream& operator<<(std::ostream& o, const std::set<T>& us) {
    return printContainer(o, us);
}

