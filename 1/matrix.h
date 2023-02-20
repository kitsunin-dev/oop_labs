#ifndef TMATRIX_H
#define TMATRIX_H

#include <iostream>

#include "number.h"

class TMatrix
{
private:
    int n = 0;
    number** elements = nullptr;
public:
    TMatrix();
    TMatrix(int, number**&);
    TMatrix(const TMatrix&);
    ~TMatrix();
    number findDet();
    int findRank();
    void transpose();
    friend std::ostream& operator<< (std::ostream&, const TMatrix&);
    void toDefaultMatrix();
};

#endif // TMATRIX_H
