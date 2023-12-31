#include "imports.h"
#include "matrix.h"

#define N 3

double mref[N][N] =
// {
//     {  4, 4, 8 },
//     {  2, 2, 7 },
//     {  1, 3, 6 },
// };
{
    {     1, 2e20,  2e40 },
    {     2, 2e40, 2e108 },
    {  2e30, 2e54,  2e10 },
};


// void save_durations_to_file(char * filename, const clock_t * durations, unsigned int size)
// {
//     FILE * file = fopen(filename, "w");
//
//     for (unsigned int i = 0; i < size; i++)
//         fprintf(file, "%d %lf\n", i, (double) durations[i] / (CLOCKS_PER_SEC));
//
//     fclose(file);
// }
//
// clock_t run_calculations(enum OPERATION operation, unsigned int dim, char init_random, double ** ref_matrix, char should_print)
// {
//     double ** matrix = allocate_matrix(dim);
//     if (init_random)
//         init_random_matrix(matrix, dim);
//
//     else {
//         for (unsigned int i = 0; i < dim; i++)
//             for (unsigned int j = 0; j < dim; j++)
//                 matrix[i][j] = ref_matrix[i][j];
//     }
//
//     if (should_print) {
//         printf("-----------------------------\n");
//         print_matrix(matrix, dim, operation);
//         printf("-----------------------------\n");
//     }
//
//     clock_t before;
//     clock_t after;
//     // unsigned int *  permutation_plu  = NULL;
//     // unsigned int ** permutation_pluq = NULL;
//     unsigned int * permutations = NULL;
//     if (operation == LU) {
//         lu(matrix, dim);
//     } else if (operation == PLU) {
//         before = clock();
//         permutations = plu(matrix, dim);
//         after = clock();
//     } else if (operation == PLUQ) {
//         before = clock();
//         permutations = pluq(matrix, dim);
//         after = clock();
//     }
//
//     if (should_print) {
//         print_matrix(matrix, N, operation);
//
//         printf("-----------------------------\n");
//
//         printf("Permutation array P: [ ");
//         for (unsigned int i = 0; i < dim; i++)
//             printf("%u ", permutations[i]);
//         printf("]\n");
//
//         printf("-----------------------------\n");
//
//         printf("Permutation array Q: [ ");
//         for (unsigned int i = dim; i < 2 * dim; i++)
//             printf("%u ", permutations[i]);
//         printf("]\n");
//
//         printf("-----------------------------\n");
//
//         printf("%s Duration: %f seconds\n", operation == LU ? "LU" : (operation == PLU ? "PLU" : "PLUQ"), (double) (after - before) / CLOCKS_PER_SEC);
//     }
//
//
//     free_matrix(matrix, dim);
//     if (permutations != NULL) {
//         // free(permutations[0]);
//         // free(permutations[1]);
//         free(permutations);
//     }
//
//     return (after - before);
// }

int main()
{
    // if (argc == 1) {
    //     printf("Wrong format: use ./main [UPPER_BOUND]\n");
    //     exit(1);
    // }

    /* unsigned int dim = N;

    double ** m2 = (double **) malloc(sizeof(double *) * dim);
    for (int i = 0; i < dim; i++) {
        m2[i] = malloc(sizeof(double) * dim);
        for (int j = 0; j < dim; j++)
            m2[i][j] = mref[i][j];
    }

    run_calculations(PLUQ, dim, 0, m2, 1); */

    unsigned int m = 3;
    unsigned int n = 2;

    double * matrix = malloc(sizeof(double) * m * n);
    double * q = malloc(sizeof(double) * m * m);
    double * r = malloc(sizeof(double) * m * n);

    matrix[0] = 3; matrix[1] = -3;
    matrix[2] = 4; matrix[3] = -4;
    matrix[4] = 0; matrix[5] = 40;

    clock_t begin = clock();
    for (unsigned int i = 0; i < 1000000000; i++)
        gram_schmidt(matrix, m, n, q, r);
    clock_t end = clock();

    // printf("----------- Matrix A:\n");
    // print_matrix(matrix, m, n, OTHER_OPERATION);
    //
    // printf("----------- Matrix Q:\n");
    // print_matrix(q, m, m, OTHER_OPERATION);
    //
    // printf("----------- Matrix R:\n");
    // print_matrix(r, m, n, OTHER_OPERATION);

    printf("---------------------\n");
    printf("Time elapsed: %lf seconds\n", (double) (end - begin) / CLOCKS_PER_SEC);

    begin = clock();
    for (unsigned int i = 0; i < 1000000000; i++)
        gram_schmidt_opti(matrix, m, n, q, r);
    end = clock();

    // printf("----------- Matrix A:\n");
    // print_matrix(matrix, m, n, OTHER_OPERATION);
    //
    // printf("----------- Matrix Q:\n");
    // print_matrix(q, m, m, OTHER_OPERATION);
    //
    // printf("----------- Matrix R:\n");
    // print_matrix(r, m, n, OTHER_OPERATION);

    printf("---------------------\n");
    printf("Time elapsed: %lf seconds\n", (double) (end - begin) / CLOCKS_PER_SEC);

    // run_calculations(PLU, dim, 0, m2, 1);

    // unsigned int UPPER_BOUND = atoi(argv[1]);
    // clock_t * all_durations = (clock_t *) malloc(sizeof(clock_t) * UPPER_BOUND);

    // for (unsigned int dim = 1; dim <= UPPER_BOUND; dim++) {
    //     if (dim % 25 == 0)
    //         printf("Calculating instance %u/%u\n", dim, UPPER_BOUND);

    //     clock_t duration = run_calculations(PLU, dim, 1, NULL, 0);
    //     all_durations[dim - 1] = duration;
    // }

    // save_durations_to_file("benchmarks.txt", all_durations, UPPER_BOUND);

    // free(all_durations);

    return 0;
}
