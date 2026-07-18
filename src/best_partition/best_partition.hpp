#pragma once

#include <bits/stdc++.h>
#include "../solution.hpp"
#include "../mex_treap.hpp"

using namespace std;

class best_partition : public solution {
public:
    int linear(const vector<int>& arr) override {
        int n = (int) arr.size();
        vector<int> dp(n + 1); dp[0] = 0;

        mex_treap mt(n);
        for (int i = 0; i < n; i++) {
            dp[i + 1] = dp[i];
            for (boundary bd : mt.adv(i, arr[i]).second) dp[i + 1] = max(dp[i + 1], dp[bd.L - 1] + bd.mex);
        }

        return dp[n];
    };

    int quadratic(const vector<int>& arr) override {
        int n = (int) arr.size();
        vector<int> dp(n + 1); dp[0] = 0;
        vector<bool> seen(n);

        for (int i = 0; i < n; i++) {
            dp[i + 1] = dp[i];
            
            fill(seen.begin(), seen.end(), false);
            int mex = 0;
            for (int j = i; j >= 0; j--) {
                if (0 <= arr[j] && arr[j] < n) seen[arr[j]] = true;
                while (mex < n && seen[mex]) mex++;
                dp[i + 1] = max(dp[i + 1], dp[j] + mex);
            }
        }

        return dp[n];
    };
};