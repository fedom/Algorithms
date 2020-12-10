#ifndef WEIGHTED_QUICK_UNION_UF_H_
#define WEIGHTED_QUICK_UNION_UF_H_

class WeightedQuickUnionUF {
public:
    WeightedQuickUnionUF(int n);
    ~WeightedQuickUnionUF();

    void Connect(int p, int q);

    bool IsConnected(int p, int q);
    int Find(int p);
    int Count();

private:
    int count_;
    int total_;
    int *p_;
    int *size_;
};

#endif  // WEIGHTED_QUICK_UNION_UF_H_
