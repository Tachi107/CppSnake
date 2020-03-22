#pragma once
#include <random>
#include <functional>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <array>

// https://codereview.stackexchange.com/questions/109260/seed-stdmt19937-from-stdrandom-device
class Random {
private:
public:
    template <typename type>
    static type getInt(type low, type high) {
        std::array<unsigned, std::mt19937::state_size> random_data;
        std::random_device source;
        std::generate(random_data.begin(), random_data.end(), std::ref(source));
        std::seed_seq semi(random_data.begin(), random_data.end());
        std::mt19937 randomGenerator(semi);
        std::uniform_int_distribution<type> distribution(low, high);
        return distribution(randomGenerator);
    }

    template <typename type>
    static type getReal(type low, type high) {
        unsigned random_data[std::mt19937::state_size];
        std::random_device source;
        std::generate(std::begin(random_data), std::end(random_data), std::ref(source));
        std::seed_seq semi(std::begin(random_data), std::end(random_data));
        std::mt19937 randomGenerator(semi);
        std::uniform_real_distribution<type> distribution(low, high);
        return distribution(randomGenerator);
    }
};
