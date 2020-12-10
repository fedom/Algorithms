#include "weighted_quick_union_compressed_path_uf.h"

WeightedQuickUnionCompPathUF::WeightedQuickUnionCompPathUF(int n) {
    p_ = new int[n];
    size_ = new int[n];

    for (int i = 0; i < n; i++) {
        p_[i] = i;
        size_[i] = 1;
    }

    count_ = n;
    total_ = n;
}

WeightedQuickUnionCompPathUF::~WeightedQuickUnionCompPathUF() {
    if (p_) {
        delete[] p_;
    }
    if (size_) {
        delete[] size_;
    }
}

void WeightedQuickUnionCompPathUF::Connect(int p, int q) {
    if (IsConnected(p, q)) return;

    int p_root = Find(p);
    int q_root = Find(q);

    if (size_[p_root] < size_[q_root]) {
        p_[p_root] = p_[q_root];
        size_[q_root] = size_[p_root] + size_[q_root];
        while (p != p_root) {
            int tmp = p_[p];
            size_[p_[p]] -= size_[p];
            p_[p] = q_root;

            p = tmp;
        }

    } else {
        p_[q_root] = p_[p_root];
        size_[p_root] = size_[p_root] + size_[q_root];

        while (q != q_root) {
            int tmp = p_[q];
            size_[p_[q]] -= size_[q];
            p_[q] = p_root;
            q = tmp;
        }
    }

    count_--;
}

int WeightedQuickUnionCompPathUF::Find(int p) {
    while (p != p_[p]) p = p_[p];
    return p;
}

bool WeightedQuickUnionCompPathUF::IsConnected(int p, int q) {
    p = Find(p);
    q = Find(q);

    return p == q;
}

int WeightedQuickUnionCompPathUF::Count() { return count_; }
