#ifndef UNION_FIND_H__
#define UNION_FIND_H__

#include <vector>

class UnionFind {
public:
    UnionFind(int n);

    int Find(int i);
    void Connect(int i, int j);

    bool IsConnected(int i, int j);
    int groups() const {return groups_;}

private:
    std::vector<int> root_;
    std::vector<int> rank_;

    int groups_;
};

#endif //UNION_FIND_H__
