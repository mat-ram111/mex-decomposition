#pragma once

#include <bits/stdc++.h>
using namespace std;

struct boundary {
    int l, L, r, R;
    int mex;

    boundary(int _l, int _L, int _r, int _R, int _mex) :
        l(_l), L(_L),
        r(_r), R(_R),
        mex(_mex)
    {};

    boundary() {};

    friend ostream& operator<<(ostream &os, const boundary &b) {
        return os << "[" << b.L << ", " << b.l << ") x [" << b.r << ", " << b.R << ") - " << b.mex;
    };
};

struct treap_node; using treap_node_ptr = treap_node*;
struct treap_node {
    int idx, val;
    treap_node_ptr p = nullptr, l = nullptr, r = nullptr;
    boundary* bound = nullptr;
    bool left = false, del = false;

    treap_node(int _idx, int _val) :
        idx(_idx), val(_val)
    {};

    void left_rotate() {
        treap_node_ptr y = this->r;

        this->r = y->l;
        if (y->l) y->l->p = this;
        y->p = this->p;

        (this == this->p->l ? this->p->l : this->p->r) = y;
        y->l = this;
        this->p = y;
    };

    void right_rotate() {
        treap_node_ptr y = this->l;

        this->l = y->r;
        if (y->r) y->r->p = this;
        y->p = this->p;

        (this == this->p->l ? this->p->l : this->p->r) = y;
        y->r = this;
        this->p = y;
    };

    treap_node_ptr remove() {
        treap_node_ptr c = (this->l ? this->l : this->r);
        (this == this->p->l ? this->p->l : this->p->r) = c;
        if (c) c->p = this->p;

        delete this;
        return nullptr;
    };
};

class mex_treap {
private:
    int n;
    treap_node_ptr root, right;
    vector<treap_node_ptr> val_to_node;
    vector<treap_node_ptr> stack;
    vector<boundary> decomp;

    treap_node_ptr get(treap_node_ptr x) {
        if (!x || (!x->del)) return x;

        stack.push_back(x);
        while (!stack.empty()) {
            x = stack.back(); stack.pop_back();
            
            bool push_l = (x->l && x->l->del), push_r = (x->r && x->r->del);
            if (push_l || push_r) {
                stack.push_back(x);
                if (push_r) stack.push_back(x->r);
                if (push_l) stack.push_back(x->l);
            }
            else {
                if (!(x->l || x->r)) x = x->remove();
                else {
                    if (!x->l || (x->r && x->r->val <= x->l->val)) x->left_rotate();
                    else x->right_rotate();
                    treap_node_ptr p = x->p;
                    if (!(x->l && x->r)) x->remove();
                    x = p;
                }
            }
        }

        return x;
    };

    void app(int idx, int val) {
        treap_node_ptr
            x = new treap_node(idx, val),
            u = this->right->p,
            v = this->right;
        
        while (!(v = get(v)) || x->val < v->val) u = (v = u)->p;

        x->l = v->r;
        if (v->r) v->r->p = x;
        v->r = x;
        x->p = v;

        this->right = x;
        val_to_node[val] = x;
        x->left = (v == this->root);
    };

public:
    mex_treap(int _n) :
        n(_n),
        val_to_node(_n + 1, nullptr) {
            stack.reserve(2*n + 5);
            decomp.reserve(2*n + 5);
            this->right = this->root = new treap_node(-1, INT_MIN);
            for (int i = 0; i <= n; i++) app(-1, i);
    };

    pair<boundary*, vector<boundary*>> adv(int idx, int val) {
        this->root->idx++;
    
        pair<boundary*, vector<boundary*>> ret = {nullptr, {}};
        if (!(0 <= val && val < n)) return ret;

        treap_node_ptr x = val_to_node[val]; x->del = true; 

        if (this->right == x) this->right = (x->l ? x->l : x->p);
        if (x->left) {
            x->left = false;
            if (x->bound) {
                x->bound->R = idx; ret.first = x->bound;
            }
            while (get(x->r) && (!x->l || x->r->val <= x->l->val)) {
                treap_node_ptr y = x->r; x->left_rotate();
                y->left = true;
                decomp.push_back(boundary(y->idx + 1, y->p->idx + 1, idx, n, y->val));
                ret.second.push_back(y->bound = &decomp.back());
            }
            if (x->l) {
                x->l->bound->R = idx;
                decomp.push_back(boundary(x->l->idx + 1, x->p->idx + 1, idx, n, x->l->val));
                ret.second.push_back(new boundary(x->l->bound->L, x->p->idx + 1, idx, n, x->l->val)); //fix this, causes memory leak currently
                x->l->bound = &decomp.back();
            }
            get(x);
        }

        app(idx, val);
        return ret;
    };

    vector<boundary>& get_decomp() {
        return this->decomp;
    }

    ~mex_treap() {
        stack.push_back(this->root);
        while (!stack.empty()) {
            treap_node_ptr x = stack.back(); stack.pop_back();
            if (x->l) stack.push_back(x->l);
            if (x->r) stack.push_back(x->r);
            delete x;
        }
    }
};