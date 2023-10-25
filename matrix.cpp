#include "matrix.hpp"

Matrix::Matrix(unsigned int dim) {
    this->dim = dim;

    this->m = new double*[dim];
    for (unsigned int i; i < dim; i++)
        this->m[i] = new double[dim];
}

Matrix::initRandom
