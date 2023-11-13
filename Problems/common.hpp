#include<fstream>
#include<vector>
#include<iostream>

template<typename T>
void read(std::vector<T> &v) {
    int size;
    std::cin >> size;
    v.insert(v.begin(), size, 0);
    for (int i = 0; i < size; i++)
        std::cin >> v[i];
}
template<typename T>
void read2d(std::vector<std::vector<T>> &v) {
    int n_rows, n_columns;
    std::cin >> n_rows >> n_columns;
    v.insert(v.begin(), n_rows, std::vector<T>(n_columns, 0));
    for (int i = 0; i < n_rows; i++)
        for (int j = 0; j < n_columns; j++)
            std::cin >> v[i][j];
}

template<typename T1, typename T2>
std::ostream& operator << (std::ostream& ost, const std::pair<T1, T2> p) {
    ost << "(" << p.first << ", " << p.second << ")";
    return ost;
}

template<typename T>
std::ostream& operator << (std::ostream& ost, const std::vector<T> v) {
    ost << "{ ";
	for (T e : v) ost << e << " ";
	ost << "}" << std::endl;
    return ost;
}