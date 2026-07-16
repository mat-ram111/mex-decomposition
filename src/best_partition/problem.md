# Problem

Given an array `arr` of integers, define a *partition* of `arr` as a way to break it up into continguous subarrays such that each of its elements belongs to exactly one subarray. If the *score* of a partition is the sum of the MEX (minimum excluded integer) of its subarrays, return the maximum score over all partitions of `arr`.

# Example

`arr = [0, 3, 0, 1, 0, 1, 5, 4, 2, 0]`
Then the optimal way to partition the array is as `[0 | 3, 0, 1, 0, 1, 5, 4, 2 | 0]`. The first and last subarrays have MEX 1, and the middle subarray has MEX 6. This yields a score of 8, and it can be shown that no score greater than 8 is possible