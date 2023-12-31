#include "imports.h"
#include "matrix.h"

void lu(double ** matrix, unsigned int size)
{
    // For each line
    for (unsigned int i = 0; i < size - 1; i++) {

        // For each line underneath
        for (unsigned int j = i + 1; j < size; j++) {
            double coef = matrix[j][i] / matrix[i][i];

            // Calculate the whole line
            for (unsigned int k = i + 1; k < size; k++) {
                matrix[j][k] -= coef * matrix[i][k];
            }

            // Fill the lower
            matrix[j][i] = coef;
        }
    }
}


unsigned int * plu(double ** matrix, unsigned int size)
{
    // `permutation[i] = j` means the i-th 1 is on the j-th column
    unsigned int * permutation = (unsigned int *) malloc(sizeof(unsigned int) * size);
    for (unsigned int i = 0; i < size; i++)
        permutation[i] = i;

    char solved;

    // For each line
    for (unsigned int i = 0; i < size - 1; i++) {

        // For each line underneath
        for (unsigned int j = i + 1; j < size; j++) {
            if (matrix[i][i] == 0) {
                solved = invert_lines(permutation, matrix, i, size);
                if (solved == 0)
                    return NULL;
            }

            double coef = matrix[j][i] / matrix[i][i];

            // Calculate the whole line
            for (unsigned int k = i + 1; k < size; k++) {
                matrix[j][k] -= coef * matrix[i][k];
            }

            // Fill the lower
            matrix[j][i] = coef;
        }
    }

    return permutation;
}


uint64_t get_biggest_pivot(double ** matrix, unsigned int iref, unsigned int size)
{
    double max = matrix[iref][iref];
    // printf("here\n");
    for (unsigned int i = iref; i < size; i++) {
        for (unsigned int j = iref; j < size; j++) {
            if (matrix[i][j] > max) {
                // printf("Sending pivots i=%d, j=%d\n", i, j);
                return (uint64_t) i << 32 | j;
            }
        }
    }

    // printf("Sending pivots i=%d, j=%d\n", iref, iref);
    return (uint64_t) iref << 32 | iref;
}


unsigned int * pluq(double ** matrix, unsigned int size)
{
    // `permutation[i] = j` means the i-th 1 is on the j-th column
    // `permutation[size + i] = j` means the i-th 1 is on the j-th line
    // unsigned int * permutation   = (unsigned int *) malloc(sizeof(unsigned int) * size);
    // unsigned int * permutation_q = (unsigned int *) malloc(sizeof(unsigned int) * size);
    // for (unsigned int i = 0; i < size; i++) {
    //     permutation_q[i] = i;
    //     permutation[i] = i;
    // }

    // unsigned int ** permutations = (unsigned int **) malloc(sizeof(unsigned int *) * 2);
    // permutations[0] = permutation;
    // permutations[1] = permutation_q;

    unsigned int * permutations = (unsigned int *) malloc(sizeof(unsigned int) * 2 * size);
    for (unsigned int i = 0; i < 2 * size; i++)
        permutations[i] = i % size;

    // Boolean value for checking if the matrix is solvable
    char solved;

    unsigned int temp_pivot;
    for (unsigned int i = 0; i < size; i++) {
        uint64_t pivots = get_biggest_pivot(matrix, i, size);

        // Unmasking pivots
        uint32_t i_pivot = pivots >> 32;
        uint32_t j_pivot = pivots;
        printf("Found pivots i=%d, j=%d\n", i_pivot, j_pivot);

        // if (i_pivot != i || j_pivot != i) {
        //     temp_pivot = permutations[0][i];
        //     permutations[0][i] = permutations[0][i_pivot];
        //     permutations[0][i_pivot] = temp_pivot;

        //     temp_pivot = permutations[1][i];
        //     permutations[1][i] = permutations[1][j_pivot];
        //     permutations[1][j_pivot] = temp_pivot;
        // }

        if (i_pivot != i || j_pivot != i) {
            temp_pivot = permutations[i];
            permutations[i] = permutations[i_pivot];
            permutations[i_pivot] = temp_pivot;

            temp_pivot = permutations[size + i];
            permutations[size + i] = permutations[size + j_pivot];
            permutations[size + j_pivot] = temp_pivot;
        }
    }

    // For each line
    for (unsigned int i = 0; i < size - 1; i++) {

        // For each line underneath
        for (unsigned int j = i + 1; j < size; j++) {
            if (matrix[i][i] == 0) {
                solved = invert_lines(permutations, matrix, i, size);
                if (solved == 0)
                    return NULL;
            }

            // double coef = matrix[j][i] / matrix[i][i];
            //
            // // Calculate the whole line
            // for (unsigned int k = i + 1; k < size; k++) {
            //     matrix[j][k] -= coef * matrix[i][k];
            // }
            //
            // // Fill the lower
            // matrix[j][i] = coef;
        }
    }

    return permutations;
}


char invert_lines(unsigned int * permutation, double ** matrix, unsigned int i, unsigned int size)
{
    for (unsigned int j = i + 1; j < size; j++) {
        if (matrix[j][i] != 0) {
            // Invert the matrix lines
            double * ith_ptr = matrix[i];
            matrix[i] = matrix[j];
            matrix[j] = ith_ptr;
            // for (unsigned int k = 0; k < size; k++) {
            //     matrix[i][k] = matrix[i][k] + matrix[j][k];
            //     matrix[j][k] = matrix[i][k] - matrix[j][k];
            //     matrix[i][k] = matrix[i][k] - matrix[j][k];
            // }

            // Swapping cases in the permutation array
            permutation[i] = permutation[i] ^ permutation[j];
            permutation[j] = permutation[i] ^ permutation[j];
            permutation[i] = permutation[i] ^ permutation[j];

            return 1;
        }
    }

    // No suitable replacement was found, return false
    printf("Can't solve!\n");
    return 0;
}


double ** allocate_matrix(unsigned int dim)
{
    double ** matrix = (double **) malloc(dim * sizeof(double *));

    for (unsigned int i = 0; i < dim; i++)
        matrix[i] = (double *) malloc(dim * sizeof(double));

    return matrix;
}


extern inline void copy_matrix(double ** matrix, double ** mref, unsigned int dim)
{
    for (unsigned int i = 0; i < dim; i++)
        for (unsigned int j = 0; j < dim; j++)
            matrix[i][j] = mref[i][j];
}


void print_matrix(double * matrix, unsigned int m, unsigned int n, enum OPERATION operation)
{
    for (unsigned int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < n; j++) {
            if (operation == PLUQ)
                printf("%.2e\t", matrix[i * n + j] == 0 ? 0 : matrix[i * n + j]);  // 0 because sometimes it prints out -0
            else
                printf("%.2f\t", matrix[i * n + j] == 0 ? 0 : matrix[i * n + j]);
        }

        printf("\n");
    }
}


void free_matrix(double ** matrix, unsigned int dim)
{
    for (unsigned int i = 0; i < dim; i++)
        free(matrix[i]);

    free(matrix);
}


void init_random_matrix(double ** matrix, unsigned int dim)
{
    srand(time(NULL));

    for (unsigned int i = 0; i < dim; i++)
        for (unsigned int j = 0; j < dim; j++)
            matrix[i][j] = rand() % 10 - 5;
}


double norm(double * matrix, unsigned int startingpos, unsigned int max, unsigned int stride)
{
    /*
     * Calculates the Euclidean norm of a row/line of the matrix (depending on the stride)
     */

    double result = 0.0;

    while (startingpos < max) {
        result += matrix[startingpos] * matrix[startingpos];
        startingpos += stride;
    }

    return sqrt(result);
}


double scalar_product_cols(double * matrix, unsigned int m, unsigned int n, unsigned int i, unsigned int j)
{
    double result = 0.0;

    for (unsigned int k = 0; k < m; k++)
        result += matrix[k * n + i] * matrix[k * n + j];

    return result;
}


void gram_schmidt(double * matrix, unsigned int m, unsigned int n, double * q, double * r)
{
    /*
     * Calculates a QR decomposition of the matrix using Gram-Schmidt's method.
     * m is the number of lines, n of columns
     */

    r[0] = norm(matrix, 0, m * n, n);

    // q_1 = a_1/r_1,1
    for (unsigned int k = 0; k < m; k++)
        q[k * m] = matrix[k * n] / r[0];

    for (unsigned int j = 1; j < n; j++) {
        // q_j = a_j
        for (unsigned int k = 0; k < m; k++)
            q[k * m + j] = matrix[k * n + j];

        for (unsigned int i = 0; i < j; i++) {
            // r_i,j = q_i^star * q_j
            r[i * n + j] = scalar_product_cols(q, m, m, i, j);

            // q_j = q_j - r_i,j * q_i
            for (unsigned int k = 0; k < m; k++)
                q[k * m + j] -= r[i * n + j] * q[k * m + i];
        }

        r[j * n + j] = norm(q, j, m * m, m);

        for (unsigned k = 0; k < m; k++)
            q[k * m + j] /= r[j * n + j];
    }
}

void gram_schmidt_opti(double * matrix, unsigned int m, unsigned int n, double * q, double * r)
{
    /*
     * Calculates a QR decomposition of the matrix using Gram-Schmidt's method.
     * m is the number of lines, n of columns
     */

    register unsigned int i, j, k = 0, a = m * n;
    register double b = 0.0;

    while (k < a) {
        // Calculating norm
        b += matrix[k] * matrix[k];  // Here, k stands for startingpoint, otherwise it's use as an loop variable
        k += n;
    }

    b = sqrt(b);
    a = m * m;

    r[0] = b;

    for (k = 0; k < m; k++)
        q[k * m] = matrix[k * n] / b;

    for (j = 1; j < n; j++) {
        for (k = 0; k < m; k++)
            q[k * m + j] = matrix[k * n + j];

        for (i = 0; i < j; i++) {
            b = 0.0;
            for (k = 0; k < m; k++)
                b += q[k * m + i] * q[k * m + j];

            r[i * n + j] = b;

            for (k = 0; k < m; k++)
                q[k * m + j] -= r[i * n + j] * q[k * m + i];
        }

        b = 0.0;
        for (k = j; k < a; k += m)
            b += q[k] * q[k];

        b = sqrt(b);

        r[j * n + j] = b;

        for (k = 0; k < m; k++)
            q[k * m + j] /= b;
    }
}
