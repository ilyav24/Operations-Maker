#include <chrono>

template <class DT = std::chrono::microseconds, class ClockT = std::chrono::steady_clock>

class Timer
{
    using timep_t = typename ClockT::time_point;
    timep_t _start = ClockT::now(), _end = {};

public:
    void tick()
    {
        _end = timep_t{};
        _start = ClockT::now();
    }

    void tock() { _end = ClockT::now(); }

    template <class T = DT>
    auto duration() const
    {
        // gsl_Expects(_end != timep_t{} && "toc before reporting");
        return (_end - _start);
    }
};