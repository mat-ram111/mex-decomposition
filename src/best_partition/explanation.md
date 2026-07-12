# DP Idea

Let `dp[i]` be the maximum score over all partitions of `arr[:i]`. Then, with the base case `dp[0] = 0`, we have the recurrence relation 
    $$\text{dp}[i] = \underset{0 \leq j < i}{\max}(\text{dp}[j] + \operatorname{mex}(\text{arr}[j:i])).$$
Since we can find the MEX of all suffixes of `arr[i]` in linear time for a given $i$, we can straightforwardly implement this formula for a quadratic solution. This looks like: 
```c++
vector<int> dp(n + 1); dp[0] = 0;
vector<bool> seen(n);

for (int i = 0; i < n; i++) {
    fill(seen.begin(), seen.end(), false);

    int mex = 0;
    for (int j = i; j >= 0; j--) {
        if (0 <= arr[j] && arr[j] < n) seen[arr[j]] = true;
        while (mex < n && seen[mex]) mex++;
        dp[i + 1] = max(dp[i + 1], dp[j] + mex);
    }
}

return dp[n];
```

# Linear Optimization

We use the same dp idea as the quadratic solution. At an index $i$, consider the set of suffixes `arr[j:i]` for $j \in [0, i)$. As $j$ decreases, and the suffixes expand leftwards, the MEX's of these suffixes is nondecreasing. We can visualize this as staircase increasing towards the left. Remember that the MEX is the *minimum* excluded integer of an array; therefore, a new element can only grow the MEX of an array if it is equal to the array's current MEX. This means that the only suffixes `arr[j : i]` whose MEX's change from the corresponding suffixes `arr[j : i-1]` are those whose MEX equals `arr[i]`.

Therefore, for an `arr[i]`, we are only interested in one band $j_1, j_1+1, ...,j_2$ such that `mex(arr[j_1 : i]) == mex(arr[j_1+1 : i]) == ... == mex(arr[j_2 : i])`. In the dp formula, $\text{dp}[i] = \underset{0 \leq j < i}{\max}(\text{dp}[j] + \operatorname{mex}(\text{arr}[j:i]))$, all of the terms with $j \not \in [j_1,j_2]$ are unchanged from $\text{dp}[i - 1]$, so we can rewrite it as 
    $$\text{dp}[i] = \max(\text{dp}[i - 1], \underset{j_1\leq j\leq j_2}{\max}(\text{dp}[j] + \operatorname{mex}(\text{arr}[j:i]))).$$

But then we must answer the question of what actually happens to the $[j_1,j_2]$ band. As described in the `explanation.md` of the `mex_treap`, this section of the MEX staircase may be refined into smaller segments according to its "monotonic stack" as encoded in the `mex_treap`, and the section with mex equal to `mex(arr[j_1-1 : i])` will be brought forward. For each of these new segments, and the one brought forward, we will take its rightmost index $j$ because `dp` is nondecreasing, and check `dp[j] + mex(arr[j:i])` against our running max for `dp[i]`.

While the logic in `mex_treap` is fairly complicated, its interface makes things fairly simple:
```c++
vector<int> dp(n + 1); dp[0] = 0;
mex_treap mt(n);
for (int i = 0; i < n; i++) {
    dp[i + 1] = dp[i];
    for (boundary* bd : mt.adv(i, arr[i])) dp[i + 1] = max(dp[i + 1], dp[bd->l - 1] + bd->mex);
}
return dp[n];
```

Again, the complexity of this approach was explained in the writeup for the data structure itself, but the brief explanation is that we process each index exactly once as an $i$, and *at most twice* as a $j$. This is because we only process an element as a $j$ once it becomes the MEX of a suffix, and then again once its value has been found again at the right. Once this happens, it is no longer the most recent occurrence of a value and we no longer care about it at all.