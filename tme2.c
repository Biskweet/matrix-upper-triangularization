#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 4

double mref[N][N] =
// {
//     {  4, 4, 8 },
//     {  2, 2, 7 },
//     {  1, 3, 6 },
// };
{
    { 2,  3,  1, 5  },
    { 6,  9,  5, 19 },
    { 2, 19, 10, 23 },
    { 8, 44, 20, 76 }
};


void add_coef_to_lower(double coef, double ** lower, unsigned int i, unsigned int j)
{
    lower[i][j] = coef;
}


void invert_lines_and_propagate(unsigned int * permutation, double ** matrix, unsigned int i, unsigned int size)
{
    for (unsigned int j = i + 1; j < size; j++) {
        if (matrix[j][i] != 0) {
            // Swap the lines
            for (unsigned int k = 0; k < size; k++) {
                matrix[i][k] = matrix[i][k] + matrix[j][k];
                matrix[j][k] = matrix[i][k] - matrix[j][k];
                matrix[i][k] = matrix[i][k] - matrix[j][k];
            }

            // Swapping cases in the permutation array
            permutation[i] = permutation[i] ^ permutation[j];
            permutation[j] = permutation[i] ^ permutation[j];
            permutation[i] = permutation[i] ^ permutation[j];

            return;
        }
    }

    // No suitable replacement was found: throw error
    printf("Can't solve!\n");
    exit(1);
}


void lu(double ** matrix, unsigned int size)
{
    // For each line
    for (unsigned int i = 0; i < size - 1; i++) {

        // For each line j under i
        for (unsigned int j = i + 1; j < size; j++) {
            double coef = matrix[j][i] / matrix[i][i];

            // Calculate the whole line
            for (unsigned int k = i + 1; k < size; k++) {
                matrix[j][k] -= coef * matrix[i][k];
            }

            // Fill the lower
            add_coef_to_lower(coef, matrix, j, i);
        }
    }
}


unsigned int * plu(double ** matrix, unsigned int size)
{
    // `permutation[i] = j` means the i-th 1 is on the j-th column
    unsigned int * permutation = (unsigned int *) malloc(sizeof(unsigned int) * size);
    for (unsigned int i = 0; i < size; i++)
        permutation[i] = i;

    // For each line
    for (unsigned int i = 0; i < size - 1; i++) {

        // For each line underneath
        for (unsigned int j = i + 1; j < size; j++) {
            if (matrix[i][i] == 0)
                invert_lines_and_propagate(permutation, matrix, i, size);

            double coef = matrix[j][i] / matrix[i][i];

            // Calculate the whole line
            for (unsigned int k = i + 1; k < size; k++) {
                matrix[j][k] -= coef * matrix[i][k];
            }

            // Fill the lower
            add_coef_to_lower(coef, matrix, j, i);
        }
    }

    return permutation;
}


double ** create_matrix(unsigned int dim)
{
    double ** matrix = (double **) malloc(dim * sizeof(double *));

    for (unsigned int i = 0; i < dim; i++)
        matrix[i] = (double *) malloc(dim * sizeof(double));

    return matrix;
}


void copy_matrix(double ** matrix, unsigned int dim)
{
    for (unsigned int i = 0; i < dim; i++)
        for (unsigned int j = 0; j < dim; j++)
            matrix[i][j] = mref[i][j];
}


void print_matrix(double ** matrix, unsigned int dim)
{
    for (unsigned int i = 0; i < dim; i++) {
        for (unsigned int j = 0; j < dim; j++)
            printf("%.2f\t", matrix[i][j]);


        printf("\n");
    }
}


void free_matrix(double ** matrix, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++)
        free(matrix[i]);
    
    free(matrix);
}


int main(int argc, char * argv[])
{
    srand(time(NULL));

    unsigned int size = N;

    double ** matrix = create_matrix(size);

    copy_matrix(matrix, size);

    printf("-----------------------------\n");

    print_matrix(matrix, size);

    printf("-----------------------------\n");

    clock_t before = clock();
    unsigned int * permutation = plu(matrix, size);
    clock_t after = clock();

    printf("Duration: %f\n", (double) (after - before) / CLOCKS_PER_SEC);

    printf("-----------------------------\n");

    print_matrix(matrix, N);

    printf("-----------------------------\n");

    printf("Permutation array: [ ");
    for (unsigned int i = 0; i < size; i++)
        printf("%u ", permutation[i]);
    printf("]\n");

    free_matrix(matrix, size);
    free(permutation);

    return 0;
}
