# Quadratic Solution

Once again, recall that we can find the MEX's of all suffixes `arr[j:i]` in linear time for a given $i$. This leads to the following very simple quadratic solution.
```c++
long long ans = 0LL;

vector<bool> seen(n);
for (int i = 0; i < n; i++) {
    fill(seen.begin(), seen.end(), false);

    int mex = 0;
    for (int j = i; j >= 0; j--) {
        if (0 <= arr[j] && arr[j] < n) seen[arr[j]] = true;
        while (mex < n && seen[mex]) mex++;
        ans = (ans + mex) % MOD;
    }
}

return ans;
```

# Linear Optimization

One of the key functionalities of the `mex_treap` is that it can completely decompose the array into linearly many "boundaries" of the form $[l, L) \times [r, R)$ with mex $m$ such that $\text{mex}(\text{arr}[j:i + 1]) = m$ for all $(j,i)$ s.t. $j \in [l, L), i \in [r, R)$. Note that we *do not* store the boundaries for subarrays whose MEX is zero because they do not affect our answer. However, for all $(j, i)$ s.t. $0 \leq j \leq i < n$ and $\text{mex}(\text{arr}[j:i+1]) > 0$, there exists exactly one boundary that contains it. This is true by construction: we iterate through every index $i$ with the `mex_treap`, and at each $i$, every index $j$ belongs to exactly one of the boundaries we are currently seeking a right endpoint for. Because the right endpoints do not overlap, regardless of their actual placement this invariant ensures membership for each $(i, j)$ in exactly one boundary. 

For each of these boundaries, there are $(L - l) \cdot (R - r)$ subarrays with both endpoints within the two intervals, so it contributes $(L - l) \cdot (R - r)$ subarrays with MEX equal to $m$. If we call the set of all these boundaries $D$, then our answer is 
    $$\underset{b \in D}{\sum}((b_L-b_l)\cdot(b_R-b_r)\cdot b_m)$$

The `mex_treap` interface makes this very easy. In code, we have:
```c++
mex_treap mt(n); for (int i = 0; i < n; i++) mt.adv(i, arr[i]);

long long ans = 0;
for (boundary& bd : mt.get_decomp()) ans = (ans + (long long) (bd.L - bd.l) * (bd.R - bd.r) % MOD * bd.mex % MOD) % MOD;
return ans;
```

Assuming that the technique correctly produces $D$, note that $D$ (called `mex_treap.decomp` in the code) is produced as a side effect of the iteration process. Therefore, if we accept (as proven in the writeup for `mex_treap` itself) that this iteration process is linear, it follows that $D$ must have a linear size.