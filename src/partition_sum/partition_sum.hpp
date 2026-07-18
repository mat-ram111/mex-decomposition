#pragma once

#include <bits/stdc++.h>
#include "../solution.hpp"
#include "../mex_treap.hpp"

#define MOD 1'000'000'007

using namespace std;

class partition_sum : public solution {
public:
    int linear(const vector<int>& arr) override {
        int n = (int) arr.size();
        vector<long long> dp(n + 1); dp[0] = 0;
        vector<long long> pfx(n + 1); pfx[0] = 0; if (n) pfx[1] = 1; 
        for (int i = 1; i < n; i++) pfx[i + 1] = 2*pfx[i] % MOD;
    
        mex_treap mt(n);
        for (int i = 0; i < n; i++) {
            dp[i + 1] = dp[i];
    
            auto [del, rep] = mt.adv(i, arr[i]);
            if (del) dp[i + 1] = (dp[i + 1] + MOD - (pfx[(*del).L] + MOD - pfx[(*del).l]) % MOD * (*del).mex % MOD) % MOD;
            for (boundary bd : rep) dp[i + 1] = (dp[i + 1] + (pfx[bd.L] + MOD - pfx[bd.l]) % MOD * bd.mex % MOD) % MOD;
            dp[i + 1] = (dp[i + 1] + dp[i]) % MOD;
        }
    
        return static_cast<int>(dp[n]);
    };

    int quadratic(const vector<int>& arr) override {
        int n = (int) arr.size();
        vector<long long> dp(n + 1, 0LL);
        vector<long long> cnt(n + 1); cnt[0] = 1; if (n) cnt[1] = 1;
        for (int i = 1; i < n; i++) cnt[i + 1] = 2*cnt[i] % MOD;
        vector<bool> seen(n);
    
        for (int i = 0; i < n; i++) {
            fill(seen.begin(), seen.end(), false);
            int mex = 0;
            for (int j = i; j >= 0; j--) {
                if (0 <= arr[j] && arr[j] < n) seen[arr[j]] = true;
                while (mex < n && seen[mex]) mex++;
                dp[i + 1] = (dp[i + 1] + dp[j] + mex*cnt[j] % MOD) % MOD;
            }
        }
    
        return static_cast<int>(dp[n]);
    };
};