#pragma once

#include <bits/stdc++.h>
#include "../solution.hpp"
#include "../mex_treap.hpp"

using namespace std;

class subarray_cnt {
public:
    vector<long long> linear(const vector<int>& arr) {
        int n = (int) arr.size();
        vector<long long> ans(n + 1, 0LL);
        
        mex_treap mt(n); for (int i = 0; i < n; i++) mt.adv(i, arr[i]);
        long long cnt = 0LL;
        for (boundary& bd : mt.get_decomp()) {
            ans[bd.mex] += (long long) (bd.L - bd.l) * (bd.R - bd.r);
            cnt += (bd.L - bd.l) * (bd.R - bd.r);
        }
        ans[0] = (long long) n * (n + 1) / 2 - cnt;
        
        return ans;
    };

    vector<long long> quadratic(const vector<int>& arr) {
        int n = (int) arr.size();
        vector<long long> ans(n + 1, 0LL);
        vector<bool> seen(n);

        for (int i = 0; i < n; i++) {
            fill(seen.begin(), seen.end(), false);

            int mex = 0;
            for (int j = i; j >= 0; j--) {
                if (0 <= arr[j] && arr[j] < n) seen[arr[j]] = true;
                while (mex < n && seen[mex]) mex++;
                ans[mex]++;
            }
        }

        return ans;
    };
};