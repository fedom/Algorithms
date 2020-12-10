#include "weighted_quick_union_uf.h"

WeightedQuickUnionUF::WeightedQuickUnionUF(int n) {
    p_ = new int[n];
    size_ = new int[n];

    for (int i = 0; i < n; i++) {
        p_[i] = i;
        size_[i] = 1;
    }

    count_ = n;
    total_ = n;
}

WeightedQuickUnionUF::~WeightedQuickUnionUF() {
    if (p_) {
        delete[] p_;
    }
    if (size_) {
        delete[] size_;
    }
}

void WeightedQuickUnionUF::Connect(int p, int q) {
    if (IsConnected(p, q)) return;

    p = Find(p);
    q = Find(q);

    if (size_[p] < size_[q]) {
        p_[p] = p_[q];
        size_[q] = size_[p] + size_[q];
    } else {
        p_[q] = p_[p];
        size_[p] = size_[p] + size_[q];
    }

    count_--;
}

int WeightedQuickUnionUF::Find(int p) {
    while (p != p_[p]) {
        p = p_[p];
    }
    return p;
}

bool WeightedQuickUnionUF::IsConnected(int p, int q) {
    p = Find(p);
    q = Find(q);

    return p == q;
}

int WeightedQuickUnionUF::Count() { return count_; }
