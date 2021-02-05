#ifndef MATRIX_H
#define MATRIX_H


class matrix
{
public:
    matrix();
    int m1[20][3] = {{0}};
    double m2[3][3] = {{0.0}};
    matrix operator *(matrix);
};

#endif // MATRIX_H
