#pragma once

#include <bits/stdc++.h>
using namespace std;

string print_vector(vector<int>& v) {
    string ret = "[";
    for (int i = 0; i < (int) v.size() - 1; i++) ret += v[i] + ", ";
    if (!v.empty()) ret += v.back();
    return ret + "]\n";
}

class test_suite {
private:
    mt19937 gen;
    using generator = function<vector<int>(int, int)>;
public:
    vector<pair<string, generator>> generators;

    test_suite(uint32_t seed) : gen(seed) {
        generators = {
            {"rand_ints",       [this](int n, int){ return rand_ints(n); }},
            {"asc_regions",     [this](int n, int k){ return asc_regions(n, k); }},
            {"desc_regions",    [this](int n, int k){ return desc_regions(n, k); }},
            {"perm_regions",    [this](int n, int k){ return perm_regions(n, k); }},
            {"asc_interwoven",  [this](int n, int){ return asc_interwoven(n, /*k=*/2); }}, // fix arity as needed
            {"desc_interwoven", [this](int n, int){ return desc_interwoven(n, /*k=*/2); }},
        };
    };

    vector<int> rand_ints(int n, int _ = -1) {
        uniform_int_distribution<int> dist(0, 10);
        vector<int> arr(n); for (int i = 0; i < n; i++) arr[i] = dist(gen);
        return arr;
    }

    vector<int> asc_regions(int n, int k) {
        vector<int> arr(n);
        int f = n / k, c = (n + k - 1) / k, mod = n % k;
        for (int sz = 0, rg = 0; sz < n; sz += rg) {
            rg = (mod-- > 0 ? c : f);
            iota(arr.begin() + sz, arr.begin() + sz + rg, 0);
        }
        return arr;
    };

    vector<int> desc_regions(int n, int k) {
        vector<int> arr(n);
        int f = n / k, c = (n + k - 1) / k, mod = n % k;
        for (int sz = 0, rg = 0; sz < n; sz += rg) {
            rg = (mod-- > 0 ? c : f);
            iota(arr.begin() + sz, arr.begin() + sz + rg, 0);
            reverse(arr.begin() + sz, arr.begin() + sz + rg);
        }
        return arr;
    };

    vector<int> perm_regions(int n, int k) {
        vector<int> arr(n);
        int f = n / k, c = (n + k - 1) / k, mod = n % k;
        for (int sz = 0, rg = 0; sz < n; sz += rg) {
            rg = (mod-- > 0 ? c : f);
            iota(arr.begin() + sz, arr.begin() + sz + rg, 0);
            shuffle(arr.begin() + sz, arr.begin() + sz + rg, gen);
        }
        return arr;
    };

    vector<int> asc_interwoven(int n, int k) {
        vector<int> arr(n);
        int val = 0;
        for (int m = 0; m < k; m++) for (int i = m; i < n; i += k) arr[i] = val++;
        return arr;
    };

    vector<int> desc_interwoven(int n, int k) {
        vector<int> arr(n);
        int val = 0;
        for (int m = 0; m < k; m++) for (int i = m; i < n; i += k) arr[i] = val++;
        reverse(arr.begin(), arr.end());
        return arr;
    };
};