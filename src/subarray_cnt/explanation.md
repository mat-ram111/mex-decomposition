# Quadratic Solution

For each $i \in [0, n)$, find the MEX of all suffixes ending at $i$ and increment the component corresponding to the current mex. In code, this looks like:
```c++
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
```

# Linear Solution

With the MEX decomposition returned by the `mex_treap`, for each of the boundaries `bd` add `(bd.L - bd.l) * (bd.R - bd.r)` to `ans[bd.mex]`. Since we ignore subarrays with MEX equal to 0 in the decomposition, take a running count of all the subarrays we have added. Then at the end, subtract it from $\frac{n(n+1)}{2}$. This will be the number of subarrays with MEX equal to 0.

In code, this looks like:
```c++
mex_treap mt(n); for (int i = 0; i < n; i++) mt.adv(i, arr[i]);
long long cnt = 0LL;
for (boundary& bd : mt.get_decomp()) {
    ans[bd.mex] += (long long) (bd.l - bd.L) * (bd.R - bd.r);
    cnt += (bd.l - bd.L) * (bd.R - bd.r);
}
ans[0] = (long long) n * (n + 1) / 2 - cnt;

return ans;
```