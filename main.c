//
// Created by Antonio Maksimovich on 30.06.2017.
//

#include <time.h>
#include "mul_m.h"

int main()
{
    //example
    //int c1=clock();
    //int c2=clock();
    //printf("time without threads: %.3f\n", (double)(c2-c1)/ CLOCKS_PER_SEC);

    int n = 700;
    int min = 1;
    int max = 100;
    int th = 8;

    double **a = generate_m(n, min, max);
    double **b = generate_m(n, min, max);

    double **res1;
    double **res2;

    int c1 = clock();
    res1 = thread_mul_m(a, b, n, th);
    int c2 = clock();
    printf("time with threads: %.3f\n", (double)(c2-c1)/ CLOCKS_PER_SEC);

    c1 = clock();
    res2 = no_thread_mul_m(a, b, n);
    c2 = clock();
    printf("time without threads: %.3f\n", (double)(c2-c1)/ CLOCKS_PER_SEC);

    printf("%d", is_equal_m(res1, res2, n));

    delete_m(a, n);
    delete_m(b, n);
    delete_m(res1, n);
    delete_m(res2, n);
}