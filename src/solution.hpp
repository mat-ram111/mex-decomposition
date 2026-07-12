#pragma once
#include <bits/stdc++.h>
using namespace std;

class solution {
public:
    virtual int linear(const vector<int>&) = 0;
    virtual int quadratic(const vector<int>&) = 0;
    virtual ~solution() = default;
};