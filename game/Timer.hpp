template <class Precision>
class Timer {

    using clock = std::chrono::high_resolution_clock;

public:

    Timer():
        t0_ { clock::now() }
    { }

    ~Timer() = default;
    Timer(const Timer &) = default;
    Timer & operator=(const Timer &) = default;

    void reset() {
        t0_ = clock::now();
    }

    typename Precision::rep elapsed() {
        auto t1 = clock::now();
        auto duration = std::chrono::duration_cast<Precision>(t1 - t0_);

        return duration.count();
    }

private:

    clock::time_point t0_;

};
