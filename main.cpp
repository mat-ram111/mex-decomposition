#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>

#include "src/solution.hpp"
#include "src/best_partition/best_partition.hpp"
#include "src/subarray_sum/subarray_sum.hpp"
#include "src/partition_sum/partition_sum.hpp"
#include "src/subarray_cnt/subarray_cnt.hpp"

#include "tests/runners/correctness.hpp"
#include "tests/runners/complexity.hpp"

int main(int argc, char** argv) {
    if (argc <= 2) {
        cerr << "Usage: ./main <Testcases per correctness regime> <random seed>" << endl;
        return 1;
    }

    subarray_cnt sc;
    for (long long x : (sc.linear({0, 3, 0, 1, 0, 1, 5, 4, 2, 0}))) cout << x << " "; cout << endl;
    for (long long x : (sc.quadratic({0, 3, 0, 1, 0, 1, 5, 4, 2, 0}))) cout << x << " "; cout << endl;


    int T = stoi(argv[1]);
    int seed = stoi(argv[2]);
    ofstream os("output.txt");
    cout << T << " " << seed << endl;

    if (!os.is_open()) {
        cerr << "Couldn't create file" << endl;
        return 1;
    }

    os << "PROBLEM 1: BEST PARTITION" << endl << endl;
    best_partition bp;
    correctness(os, bp, T, seed);
    os << endl;
    complexity(os, bp, 2);
    os << endl;

    os << "PROBLEM 2: ALL SUBARRAYS SUM" << endl << endl;
    subarray_sum ss;
    correctness(os, ss, T, seed);
    os << endl;
    complexity(os, ss, 2);
    os << endl;

    os << "PROBLEM 3: ALL PARTITIONS SUM" << endl << endl;
    partition_sum ps;
    correctness(os, ps, T, seed);
    os << endl;
    complexity(os, ps, 2);
    os << endl;

}