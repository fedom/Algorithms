#ifndef QUICK_UNION_UF_H_
#define QUICK_UNION_UF_H_

class QuickUnionUF {
public:
    QuickUnionUF(int n);
    ~QuickUnionUF();

    void Connect(int p, int q);

    bool IsConnected(int p, int q);
    int Find(int p);
    int Count();

private:
    QuickUnionUF(const QuickUnionUF &) = delete;
    QuickUnionUF(const QuickUnionUF &&) = delete;
    QuickUnionUF &operator=(const QuickUnionUF &) = delete;
    QuickUnionUF &operator=(const QuickUnionUF &&) = delete;

    int count_;
    int total_;
    int *p_;
};

#endif  // QUICK_UNION_UF_H_
