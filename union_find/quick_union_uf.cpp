#include "quick_union_uf.h"

QuickUnionUF::QuickUnionUF(int n) {
    p_ = new int[n];

    for (int i = 0; i < n; i++) {
        p_[i] = i;
    }

    count_ = n;
    total_ = n;
}

QuickUnionUF::~QuickUnionUF() {
    if (p_) {
        delete[] p_;
    }
}

void QuickUnionUF::Connect(int p, int q) {
    if (IsConnected(p, q)) return;

    p = Find(p);
    q = Find(q);

    p_[p] = q;
    count_--;
}

int QuickUnionUF::Find(int p) {
    while (p != p_[p]) p = p_[p];
    return p;
}

bool QuickUnionUF::IsConnected(int p, int q) {
    p = Find(p);
    q = Find(q);

    return p == q;
}

int QuickUnionUF::Count() { return count_; }
