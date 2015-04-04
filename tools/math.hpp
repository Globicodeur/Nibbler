#pragma once

template <class T>
T negativeMod(const T & t, const T & mod) {
    return t < 0 ? t + mod : t % mod;
}
