#ifndef WEIGHTED_QUICK_UNION_COMPRESSED_PATH_UF_H_
#define WEIGHTED_QUICK_UNION_COMPRESSED_PATH_UF_H_

class WeightedQuickUnionCompPathUF {

public:
	WeightedQuickUnionCompPathUF(int n);
	~WeightedQuickUnionCompPathUF();

	void Connect(int p, int q);

	int Find(int p);
	bool IsConnected(int p, int q);
	int Count();
	
private:

	int count_;
	int total_;
	int *p_;
	int *size_;
};

#endif//WEIGHTED_QUICK_UNION_COMPRESSED_PATH_UF_H_
