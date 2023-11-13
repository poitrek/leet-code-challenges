#include <chrono>
using namespace std::chrono;


class Timer {
    static high_resolution_clock::time_point _start;
public:
    static void start() {
        _start = high_resolution_clock::now();
    }
    static double get_seconds() {
        return duration_cast<duration<double>>(high_resolution_clock::now() - _start).count();
    }
};

high_resolution_clock::time_point Timer::_start;
