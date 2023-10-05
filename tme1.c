#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #define N 2000
//
//
// double m2[N][N] = {
//     { 10,  7,  8,  7 },
//     {  7,  5,  6,  5 },
//     {  8,  6, 10,  9 },
//     {  7,  5,  9, 10 }
// };
//
//
// void triangulate_u(double ** matrix, unsigned int size)
// {
//     for (unsigned int i = 0; i < size - 1; i++) {
//         for (unsigned int j = i + 1; j < size; j++) {
//             double coef = matrix[j][i] / matrix[i][i];
//
//             for (unsigned int k = i; k < size; k++) {
//                 matrix[j][k] -= coef * matrix[i][k];
//             }
//         }
//     }
// }
//
// void triangulate_l_normalized(double ** matrix, unsigned int size)
// {
//     for (unsigned int i = 0; i < size - 1; i++) {
//         for (unsigned int j = i + 1; j < size; j++) {
//             double coef = matrix[j][i] / matrix[i][i];
//
//             for (unsigned int k = i; k < size; k++) {
//                 matrix[j][k] -= coef * matrix[i][k];
//             }
//         }
//     }
// }
//
//
// void free_matrix(double ** matrix)
// {
//     for (unsigned int i = 0; i < N; i++)
//         free(matrix[i]);
//
//     free(matrix);
// }
//
// void print_matrix(double ** matrix, unsigned int dim)
// {
//     for (unsigned int i = 0; i < dim; i++) {
//         for (unsigned int j = 0; j < dim; j++)
//             printf("%.2f\t", matrix[i][j]);
//
//
//         printf("\n");
//     }
// }
//
//
// double ** allocate_matrix(unsigned int dim)
// {
//     double ** matrix = (double **) malloc(dim * sizeof(double *));
//
//     for (unsigned int i = 0; i < dim; i++)
//         matrix[i] = (double *) malloc(dim * sizeof(double));
//
//     return matrix;
// }
//
//
// void init_matrix(double ** matrix, unsigned int dim)
// {
//     for (unsigned int i = 0; i < dim; i++)
//         for (unsigned int j = 0; j < dim; j++)
//             matrix[i][j] = rand() % 10 - 5;
// }
