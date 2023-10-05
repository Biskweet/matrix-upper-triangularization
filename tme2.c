// #include "imports.h"
// #include "matrix.h"
//
// #define N 4
//
// double mref[N][N] =
// {
//     {  4, 4, 8 },
//     {  2, 2, 7 },
//     {  1, 3, 6 },
// };
// {
//     { 2,  3,  1,  5 },
//     { 6,  9,  5, 19 },
//     { 2, 19, 10, 23 },
//     { 8, 44, 20, 76 }
// };


// int main(int argc, char * argv[])
// {
//     srand(time(NULL));
//
//     double ** matrix = allocate_matrix(N);
//
//     copy_matrix(matrix, (double **) mref, N);
//
//     printf("-----------------------------\n");
//
//     print_matrix(matrix, N);
//
//     printf("-----------------------------\n");
//
//     clock_t before = clock();
//     unsigned int * permutation = plu(matrix, N);
//     clock_t after = clock();
//
//     printf("Duration: %f\n", (double) (after - before) / CLOCKS_PER_SEC);
//
//     printf("-----------------------------\n");
//
//     print_matrix(matrix, N);
//
//     printf("-----------------------------\n");
//
//     printf("Permutation array: [ ");
//     for (unsigned int i = 0; i < N; i++)
//         printf("%u ", permutation[i]);
//     printf("]\n");
//
//     free_matrix(matrix, N);
//     free(permutation);
//
//     return 0;
// }
