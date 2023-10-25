/*
 * Sorbonne Université  --  PPAR
 * Computing the Mandelbrot set, sequential version
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>               /* compile with -lm */
#include <time.h>


void f(unsigned int count)
{
    register unsigned int m = 4;
    register unsigned int n = 5;
    register unsigned int k;
    register unsigned int i;
    clock_t begin = clock();
    do {

        for (k = 0; k < m; k++)
            i = k * m + k * n;

    } while (count);
    clock_t end = clock();
    printf("multiplication %d : %lf\n", i, (double) (end - begin) / CLOCKS_PER_SEC);
}

void g(unsigned int count)
{

    register unsigned int m = 4;
    register unsigned int mm = m * m;
    register unsigned int n = 5;
    register unsigned int k, l;
    register unsigned int i;

    clock_t begin = clock();

    do {

        for (k = l = 0; k < mm; k++) {
            i = k + l;

            k += m;
            l += n;
        }

    } while (count);

    clock_t end = clock();
    printf("additions %d : %lf\n", i, (double) (end - begin) / CLOCKS_PER_SEC);
}


int main()
{
        unsigned long long q = pow(2, 63);
        f(q);
        g(q);

        return 0;
}