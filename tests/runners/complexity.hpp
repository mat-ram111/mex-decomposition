#pragma once

#include <bits/stdc++.h>
#include "../../src/solution.hpp"
#include "../test_suite.hpp"

#define LMAX 8'000'000
#define LMIN 100'000

using namespace std;

void complexity(std::ofstream& os, solution& sol, uint32_t seed) {
    constexpr int W_GEN = 18, W_K = 6, W_N = 8, W_ANS = 12, W_TIME = 12, W_RATIO = 8;

    test_suite ts(seed);
    std::mt19937 g(seed);

    auto hline = [&os](char l, char m, char r) {
        os << l << std::string(W_GEN,  '-') << m
                << std::string(W_K,    '-') << m
                << std::string(W_N,    '-') << m
                << std::string(W_ANS,  '-') << m
                << std::string(W_TIME, '-') << m
                << std::string(W_RATIO,'-') << r << "\n";
    };

    auto row = [&os](const std::string& gen, const std::string& k,
                     const std::string& n, const std::string& ans,
                     const std::string& time, const std::string& ratio) {
        os << '|' << std::setw(W_GEN)   << std::left  << gen
           << '|' << std::setw(W_K)     << std::right << k
           << '|' << std::setw(W_N)     << n
           << '|' << std::setw(W_ANS)   << ans
           << '|' << std::setw(W_TIME)  << time
           << '|' << std::setw(W_RATIO) << ratio << "|\n";
    };

    auto fmt = [](double v) {
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(2) << v;
        return ss.str();
    };

    os << "COMPLEXITY TESTS\n";
    hline('+', '+', '+');
    row("generator", "k", "n", "ans", "time", "ratio");
    hline('+', '+', '+');

    for (auto& [label, gen] : ts.generators) {
        int k = std::uniform_int_distribution<int>(1, 10)(g);
        double prev_ms = 0.0;
        bool first = true;

        for (int n = LMIN; n <= LMAX; n <<= 1) {
            std::vector<int> arr = gen(n, k);

            auto start = std::chrono::steady_clock::now();
            int  ans   = sol.linear(arr);
            auto end   = std::chrono::steady_clock::now();
            double cur_ms = std::chrono::duration<double>(end - start).count();

            row(first ? label : "",
                first ? std::to_string(k) : "",   // k shown once per block, like the label
                std::to_string(n),
                std::to_string(ans),
                fmt(cur_ms),
                prev_ms ? fmt(cur_ms / prev_ms) : "--");

            prev_ms = cur_ms;
            first = false;
        }
        hline('+', '+', '+');
    }
}