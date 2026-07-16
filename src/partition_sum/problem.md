# Problem

Given an array `arr` of integers, define a *partition* of `arr` as a way to break it up into continguous subarrays such that each of its elements belongs to exactly one subarray. If the *score* of a partition is the sum of the MEX (minimum excluded integer) of its subarrays, return the sum of the scores of all partitions of `arr` taken modulo $10^9+7$.

# Example

`arr = [0, 3, 0, 1, 0, 1, 5, 4, 2, 0]`.  
Then the sum over all partitions of `arr` is 2364.