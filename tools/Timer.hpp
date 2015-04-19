#include <chrono>

template <class Precision>
class Timer {

    using clock = std::chrono::high_resolution_clock;

public:

    Timer(void):
        t0_ { clock::now() }
    { }

    // 42 norme
    ~Timer(void) = default;
    Timer(const Timer &) = default;
    Timer & operator=(const Timer &) = default;
    //

    void reset(void) {
        t0_ = clock::now();
    }

    typename Precision::rep elapsed(void) {
        auto t1 = clock::now();
        auto duration = std::chrono::duration_cast<Precision>(t1 - t0_);

        return duration.count();
    }

private:

    clock::time_point t0_;

};
