#pragma once
#include <iostream>
#include <random>
#include <functional>
#include <algorithm>
#include <iterator>
#include <functional>
#include <utility>
#include <array>

// https://codereview.stackexchange.com/questions/109260/seed-stdmt19937-from-stdrandom-device
namespace Random {
    namespace {
        std::mt19937 randomGenerator;
        bool initialized = false;

        void init() {
            std::array<unsigned, std::mt19937::state_size> random_data;
            std::random_device source;
            std::generate(random_data.begin(), random_data.end(), std::ref(source));
            std::seed_seq seeds(random_data.begin(), random_data.end());
            randomGenerator.seed(seeds);
            initialized = true;
        }
    }

    template <typename type>
    type getInt(type low, type high) {
        if (!initialized) init();
        std::uniform_int_distribution<type> distribution(low, high);
        return distribution(randomGenerator);
    }

    template <typename type>
    type getReal(type low, type high) {
        if (!initialized) init();
        std::uniform_real_distribution<type> distribution(low, high);
        return distribution(randomGenerator);
    }
};  
