#include "quick_find_uf.h"
#include <stdio.h>
#include <time.h>

#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
    char *file = "tinyUF.txt";
    if (argc >= 2) file = argv[1];

    std::ifstream ifs(file);

    if (ifs.is_open()) {
        int total;

        ifs >> total;
        std::cout << "total:" << total << std::endl;

        QuickFindUF uf(total);

        time_t a = time(NULL);
        while (!ifs.eof()) {
            int a;
            int b;
            ifs >> a;
            ifs >> b;

            uf.Connect(a, b);
        }

        time_t d = time(NULL) - a;

        std::cout << "uf count:" << uf.Count() << std::endl;
        std::cout << "union time : " << d << std::endl;
    }

    ifs.close();
    return 0;
}
