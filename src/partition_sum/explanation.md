# DP Idea

Let `dp[i]` be the sum of the scores of all partitions of `arr[:i]`, and let `cnt[i]` be the number of ways to partition `arr[:i]`. Then, we have the formula:
    $$\text{dp}[i] = \underset{j = 0}{\overset{i - 1}{\sum}}(\text{dp}[j] + \text{cnt}[j]\cdot\operatorname{mex}(\text{arr}[j:i])).$$
This is because the suffix `arr[j:i]` will be appended to all partitions of `arr[:j]` so that they together extend to index $i$, and so for each of the `cnt[j]` partitions making up `dp[j]`, it contributes `mex(arr[j:i])`. Note that we can rewrite the formula as $\text{dp}[i] = \underset{j = 0}{\overset{i - 1}{\sum}}\text{dp}[j] + \underset{j = 0}{\overset{i - 1}{\sum}}(\text{cnt}[j]\cdot\operatorname{mex}(\text{arr}[j:i]))$, so `dp[i]` will by default contain the prefix sum $\underset{j = 0}{\overset{i - 1}{\sum}}\text{dp}[j]$. Therefore we can essentially ignore that part of the formula, and focus on the $\underset{j = 0}{\overset{i - 1}{\sum}}(\text{cnt}[j]\cdot\operatorname{mex}(\text{arr}[j:i]))$ sum. 

`cnt[j]` is very easy to calculate; when partitioning `arr[:j]`, we can choose either to draw or not to draw a divider in the $j - 1$ spaces between the $j$ elements, leading to $2^{j - 1}$ possible partitions. The only exception is for the empty array when $j = 0$, which there is one trivial way to partition.

Once again, since we can find the MEX of all suffixes of `arr[:i]` in linear time for a given $i$, we have the following quadratic solution:
```c++
vector<long long> dp(n + 1, 0LL);
vector<long long> cnt(n); cnt[0] = cnt[1] = 1;
for (int i = 1; i < n - 1; i++) cnt[i + 1] = 2*cnt[i] % MOD;

vector<bool> seen(n);
for (int i = 0; i < n; i++) {
    fill(seen.begin(), seen.end(), false);

    int mex = 0;
    for (int j = i; j >= 0; j--) {
        if (0 <= arr[j] && arr[j] < n) seen[arr[j]] = true;
        while (mex < n && seen[mex]) mex++;
        dp[i + 1] = (dp[i + 1] + mex*cnt[j] % MOD) % MOD;
    }
}

return dp[n];
```

# Linear Optimization

At a given $i$, it once again makes sense to group suffixes with equal MEX together. If $\operatorname{mex}(\text{arr[j:i]})$ is the same for all $j \in [j_l, j_r)$, then we can evaluate $\underset{j=j_l}{\overset{j_r - 1}{\sum}}\text{cnt}[j]\cdot\operatorname{mex}(\text{arr}[j:i])$ in constant time using prefix counts. If $\text{pfx}[i] := \underset{j=0}{\overset{i - 1}{\sum}}\text{cnt}[j]$, then $\underset{j=j_l}{\overset{j_r - 1}{\sum}}\text{cnt}[j]\cdot\operatorname{mex}(\text{arr}[j:i])=(\text{pfx}[j_r]-\text{pfx}[j_l])\cdot\operatorname{mex}(\text{arr}[j_l:i])$.

As a side note, the prefix sums of `cnt` are more elegant than `cnt` itself; since the sum of the first $i$ powers of $2$ (beginning with $2^0$) is $2^i - 1$, and the elements of `cnt` starting from index $1$ are simply the powers of $2$, adding on the base case `cnt[0] = 1` eliminates this $-1$. Thus, $\text{pfx}[i] = 2^{i - 1}$ for all $i > 0$, and $\text{pfx}[0] = 0$.

Now, at index $i$, our default assumption is that the terms making up the sum `dp[i]` are the same as those making up `dp[i - 1]`. So, we begin by setting `dp[i] = dp[i - 1]`. The only term we must update comes from the section of the suffix MEX staircase with MEX equal to $\text{arr}[i]$. If this section is $[j_l, j_r)$, then we will first subtract $(\text{pfx}[j_r] - \text{pfx}[j_l])\cdot\text{arr}[i]$. Now, for each of the new segments $[j_l', j_r')$ with MEX $m$ that $[j_l, j_r)$ splits into, we will add $(\text{pfx}[j'_r] - \text{pfx}[j'_l])\cdot m$. Finally, we add on `dp[i - 1]` to `dp[i]` once again to keep the prefix sum propagating upward.

The `mex_treap` interface makes this process very simple; it looks like:
```c++
vector<long long> dp(n + 1); dp[0] = 0;
vector<long long> pfx(n + 1); pfx[0] = 0; pfx[1] = 1;
for (int i = 1; i < n; i++) pfx[i + 1] = 2*pfx[i] % MOD;

mex_treap mt(n);
for (int i = 0; i < n; i++) {
    dp[i + 1] = dp[i];
    auto [del, rep] = mt.adv(i, arr[i]);
    if (del) dp[i + 1] = (dp[i + 1] + MOD - (pfx[del->l] + MOD - pfx[del->L]) % MOD * del->mex % MOD) % MOD;
    for (boundary* bd : rep) dp[i + 1] = (dp[i + 1] + (pfx[bd->l] + MOD - pfx[bd->L]) % MOD * bd->mex % MOD) % MOD;
    dp[i + 1] = (dp[i + 1] + dp[i]) % MOD;
}

return dp[n];
```

The work done here is linear according to the same logic as the best_partition problem.