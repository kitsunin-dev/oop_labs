#include <iostream>
#include <cmath>

#include "matrix.h"

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::ios;

TMatrix::TMatrix()
{
    n = 0;
    elements = nullptr;
}

TMatrix::TMatrix(int n, number**& arr)
{
    this->n = n;
    elements = arr;
}

TMatrix::TMatrix(const TMatrix& other)
{
    n = other.n;

    number** newArr = new number * [n];
    for (int i = 0; i < n; i++)
    {
        newArr[i] = new number[n];
        for (int j = 0; j < n; j++)
            newArr[i][j] = other.elements[i][j];
    }
    elements = newArr;
}


TMatrix::~TMatrix()
{
    if (elements) {
        for (int i = 0; i < n; i++)
            delete[] elements[i];
        delete[] elements;
    }
}

void GetMatr(number **mas, number **p, int i, int j, int m)
{
    int ki, kj, di, dj;
    di = 0;
    for (ki = 0; ki < m - 1; ki++)
    {
        if (ki == i)
            di = 1;
        dj = 0;
        for (kj = 0; kj < m - 1; kj++)
        {
            if (kj == j)
                dj = 1;
            p[ki][kj] = mas[ki + di][kj + dj];
        }
    }
}

number helpD(number** mas, int m)
{
    int i, k, n;
    number d;
    number **p;

    p = new number*[m];
    for (i = 0; i < m; i++)
        p[i] = new number[m];

    d = 0;
    k = 1;
    n = m - 1;

    if (m < 1)
        cout << "Finding determinant is impossible!" << endl;
    if (m == 1)
    {
        d = mas[0][0];
        return(d);
    }
    if (m == 2)
    {
        d = mas[0][0] * mas[1][1] - (mas[1][0] * mas[0][1]);
        return(d);
    }
    if (m > 2)
    {
        for (i = 0; i < m; i++)
        {
            GetMatr(mas, p, i, 0, m);
            d = d + k * mas[i][0] * helpD(p, n);
            k = -k;
        }
    }

    return(d);
}

number TMatrix::findDet()
{
    int i, k, n;
    number d;
    number **p;

    p = new number*[this->n];
    for (i = 0; i < this->n; i++)
        p[i] = new number[this->n];

    d = 0;
    k = 1;
    n = this->n - 1;

    if (this->n < 1)
        cout << "Finding determinant is impossible!" << endl;
    if (this->n == 1)
    {
        d = this->elements[0][0];
        return(d);
    }
    if (this->n == 2)
    {
        d = this->elements[0][0] * this->elements[1][1] - (this->elements[1][0] * this->elements[0][1]);
        return(d);
    }
    if (this->n > 2)
    {
        for (i = 0; i < this->n; i++)
        {
            GetMatr(this->elements, p, i, 0, this->n);
            d = d + k * this->elements[i][0] * helpD(p, n);
            k = -k;
        }
    }

    return(d);
}

void TMatrix::transpose()
{
    for (int i = 0; i < this->n; i++)
        for (int j = i; j < this->n; j++)
            if (i != j)
                std::swap(this->elements[i][j], this->elements[j][i]);

    cout << "Matrix transposed! Press 5 to print it.\n" << endl;
}

void swapRows(number** arr, int row1, int row2, int col)
{
    for (int i = 0; i < col; i++)
    {
        number temp = arr[row1][i];
        arr[row1][i] = arr[row2][i];
        arr[row2][i] = temp;
    }
}

int TMatrix::findRank()
{
    int rank = this->n;

    number** copy = new number*[this->n];
    for (int i = 0; i < this->n; i++)
        copy[i] = new double[this->n];

    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->n; j++)
            copy[i][j] = this->elements[i][j];

    for (int row = 0; row < rank; row++)
    {
        if (copy[row][row] != 0)
        {
            for (int col = 0; col < this->n; col++)
            {
                if (col != row)
                {
                    number mult = copy[col][row] / copy[row][row];
                    for (int i = 0; i < rank; i++)
                        copy[col][i] -= mult * copy[row][i];
                }
            }
        }
        else
        {
            bool reduce = true;

            for (int i = row + 1; i < this->n;  i++)
            {
                if (copy[i][row])
                {
                    swapRows(copy, row, i, rank);
                    reduce = false;
                    break;
                }
            }
            if (reduce)
            {
                rank--;
                for (int i = 0; i < this->n; i ++)
                    copy[i][row] = copy[i][rank];
            }

            row--;
        }

    }
    return rank;
}

ostream& operator<< (ostream& os, const TMatrix& m)
{
    for (int i = 0; i < m.n; i++)
    {
        cout << "[" << i + 1 << "] row: ";
        for (int j = 0; j < m.n; j++)
        {
            cout.setf(ios::left);
            cout.width(6);
            cout << m.elements[i][j] << " ";
        }
        cout << endl;
    }

    return os;
}

void TMatrix::toDefaultMatrix()
{
    if (elements) {
        for (int i = 0; i < n; i++)
            delete[] elements[i];
        delete[] elements;
    }

    n = 2;

    number** defaultArr = new number * [2];
    defaultArr[0] = new number[2]{ 1, 0 };
    defaultArr[1] = new number[2]{ 0, 1 };
    elements = defaultArr;
}
