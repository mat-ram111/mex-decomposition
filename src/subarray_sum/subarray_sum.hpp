#pragma once

#include <bits/stdc++.h>
#include "../solution.hpp"
#include "../mex_treap.hpp"

#define MOD 1'000'000'007

using namespace std;

class subarray_sum : public solution {
public:
    int linear(const vector<int>& arr) override {
        int n = (int) arr.size();

        mex_treap mt(n);
        for (int i = 0; i < n; i++) mt.adv(i, arr[i]);

        long long ans = 0LL;
        for (boundary& bd : mt.get_decomp()) ans = (ans + (long long) bd.mex * (bd.L - bd.l) % MOD * (bd.R - bd.r) % MOD) % MOD;
        return static_cast<int>(ans);
    };

    int quadratic(const vector<int>& arr) override {
        int n = (int) arr.size();
        vector<bool> seen(n);
        
        long long ans = 0LL;
        for (int i = 0; i < n; i++) {
            fill(seen.begin(), seen.end(), false);
            int mex = 0;
            for (int j = i; j >= 0; j--) {
                if (0 <= arr[j] && arr[j] < n) seen[arr[j]] = true;
                while (mex < n && seen[mex]) mex++;
                ans = (ans + mex) % MOD;
            }
        }

        return static_cast<int>(ans);
    }
};