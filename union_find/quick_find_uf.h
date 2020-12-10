#ifndef QUICK_FIND_UF_H_
#define QUICK_FIND_UF_H_

class QuickFindUF {
public:
    QuickFindUF(int n);
    ~QuickFindUF();

    void Connect(int p, int q);

    bool IsConnected(int p, int q);
    int Find(int p);
    int Count();

private:
    QuickFindUF(const QuickFindUF &) = delete;
    QuickFindUF(const QuickFindUF &&) = delete;
    QuickFindUF &operator=(const QuickFindUF &) = delete;
    QuickFindUF &operator=(const QuickFindUF &&) = delete;

    int count_;
    int total_;
    int *p_;
};

#endif  // QUICK_FIND_UF_H_
