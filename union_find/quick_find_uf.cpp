#include "quick_find_uf.h"

QuickFindUF::QuickFindUF(int n) {
    p_ = new int[n];

    for (int i = 0; i < n; i++) {
        p_[i] = i;
    }

    total_ = n;
    count_ = n;
}

QuickFindUF::~QuickFindUF() {
    if (p_) {
        delete[] p_;
    }
}

void QuickFindUF::Connect(int p, int q) {
    if (IsConnected(p, q)) return;

    int tmp_p_comp = p_[p];

    for (int i = 0; i < total_; i++) {
        if (p_[i] == tmp_p_comp) {
            p_[i] = p_[q];
        }
    }

    count_--;
}

int QuickFindUF::Find(int p) { return p_[p]; }

bool QuickFindUF::IsConnected(int p, int q) { return p_[p] == p_[q]; }

int QuickFindUF::Count() { return count_; }
