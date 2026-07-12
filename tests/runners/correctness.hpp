#pragma once

#include <bits/stdc++.h>
#include "../../src/solution.hpp"
#include "../test_suite.hpp"

#define QMAX 1000

using namespace std;

void correctness(ofstream& os, solution& sol, int T, uint32_t seed) {
    test_suite ts(seed);
    mt19937 g(seed);
    os << "CORRECTNESS TESTS:" << endl;
    for (auto [label, gen] : ts.generators) {
        os << label << ": ";
        uniform_int_distribution<int> sz(0, QMAX);
        for (int t = 0; t < T; t++) {
            int n = uniform_int_distribution(0, t % QMAX + 1)(g), 
                k = n ? uniform_int_distribution<int>(1, 2*t < T ? 1 : n)(g) : 0;
            vector<int> arr = gen(n, k);
            if (sol.linear(arr) != sol.quadratic(arr)) {
                os << "WRONG ANSWER FROM " << print_vector(arr) << endl;
                return;
            }
        }
        os << "All " << T << " tests passed" << endl;
    }
    os << endl;
}