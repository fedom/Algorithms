#include "union_find.h"


UnionFind::UnionFind(int n) : root_(n), rank_(n, 1), groups_(n) {
    for (int i = 0; i < n; i++) {
        root_[i] = i;
    }
}

int UnionFind::Find(int i) {
    if (i == root_[i]) {
        return i;
    }

    // recursion call to compress path
    return root_[i] = Find(root_[i]);
}

void UnionFind::Connect(int i, int j) {
    int m = Find(i);
    int n = Find(j);

    if (m == n)
        return;

    if (rank_[m] < rank_[n]) {
        root_[m] = n; 
    } else if (rank_[m] > rank_[n]) {
        root_[n] = m;
    } else {
        root_[m] = n;
        rank_[n]++;
    }
}

bool UnionFind::IsConnected(int i, int j) {
    return Find(i) == Find(j);
}

