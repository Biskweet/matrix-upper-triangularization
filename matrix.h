#include "imports.h"

enum OPERATION {
    LU,
    PLU,
    PLUQ
};

void lu(double ** matrix, unsigned int size);

char invert_lines(unsigned int * permutation, double ** matrix, unsigned int i, unsigned int size);

unsigned int * plu(double ** matrix, unsigned int size);

unsigned int * pluq(double ** matrix, unsigned int size);

double ** allocate_matrix(unsigned int dim);

void print_matrix(double ** matrix, unsigned int dim, enum OPERATION operation);

void free_matrix(double ** matrix, unsigned int dim);

void init_random_matrix(double ** matrix, unsigned int dim);

uint64_t get_biggest_pivot(double ** matrix, unsigned int iref, unsigned int size);

void gram_schmidt(double * matrix, unsigned n, unsigned m, double * q, double * r);
