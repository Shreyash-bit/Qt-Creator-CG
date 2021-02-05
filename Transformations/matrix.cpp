#include "matrix.h"

matrix::matrix()
{

}

matrix matrix::operator*(matrix obj)
{
    matrix product;
    for(int i=0; i<20; i++)
        for(int j=0; j<3; j++)
            for(int k=0; k<3; k++)
                product.m1[i][j] += (m1[i][k] * obj.m2[k][j]);
    return product;
}
