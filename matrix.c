#include <stdint.h>
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


    for (unsigned int i = iref; i < size; i++) {
        for (unsigned int j = iref; j < size; j++) {
            if (matrix[i][j] > max)
                return ((uint64_t) i << 32 | j);
        }
    }

    return ((uint64_t) iref << 32 | iref);
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

            double coef = matrix[j][i] / matrix[i][i];

            // Calculate the whole line
            for (unsigned int k = i + 1; k < size; k++) {
                matrix[j][k] -= coef * matrix[i][k];
            }

            // Fill the lower
            matrix[j][i] = coef;
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


void print_matrix(double ** matrix, unsigned int dim)
{
    for (unsigned int i = 0; i < dim; i++) {
        for (unsigned int j = 0; j < dim; j++)
            printf("%.2f\t", matrix[i][j] == 0 ? 0 : matrix[i][j]);
            // 0 because sometimes it prints out -0


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

        for (startingpos; startingpos < max; startingpos += stride) {
            result += matrix[startingpos] * matrix[startingpos];
	}

        return sqrt(result);
}

double scalar_product_cols(double * matrix, unsigned int m, unsigned int n, unsigned int i, unsigned int j)
{
	double result = 0.0;
	
	for (unsigned int k = 0; k < m * n; k++)
		result += matrix[k * n + i] * matrix[k * n + j];

	return result;
}


void gram_schmidt(double * matrix, unsigned int m, unsigned int n, double * q, double * r)
{
	/*
	 * Calculates a QR decomposition of the matrix using Gram-Schmidt's method. m lines, n cols
	 */

	r[0] = norm(matrix, 0, m * n, n);

	// q_1 = a_1/r_1,1
	for (unsigned int i = 0; i < m * n; i += n)
		q[i] = matrix[i] / r[0];

	for (unsigned int j = 2; j < n; j++) {
		// q_j = a_j
		for (unsigned int k = 0; k < m * n; k += n)
			q[j * n + k] = matrix[j * n + k];

		for (unsigned int i = 0; i < j - 1; i++) {
			// r_i,j = q_i^star * q_j
			r[i * n + j] = scalar_product_cols(matrix, m, n, i, j);

			// q_j = q_j - r_i,j * q_i
			for (unsigned int k = 0; k < m * n; k += n)
				q[k * n + j] -= r[i * n + j] * q[k * n + i];
		}

		r[j * n + j] = norm(matrix, j, n * m, n);

		for (unsigned k = 0; k < n * m; k += n)
			q[k * n + j] /= r[j * n + j];	
	}
}
