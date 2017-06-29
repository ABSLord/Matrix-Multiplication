//
// Created by Antonio Maksimovich on 30.06.2017.
//

#include "mul_m.h"


double** generate_m(int n, int min, int max)
{
    double **m = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++)
    {
        m[i] = (double*)malloc(n * sizeof(double));
    }
    srand((unsigned) time(NULL));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            m[i][j] = (double)(rand() % max + min);
        }
    return m;
}

void print_m(double **a, int n)
{
    printf("matrix: \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%.0f ", a[i][j]);
        printf("\n");
    }
}

int is_equal_m(double **a, double **b, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if(a[i][j] != b[i][j])
                return FALSE;
        }
    return TRUE;
}

void delete_m(double **a, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(a[i]);
    }
    free(a);
}

double** no_thread_mul_m(double **a, double **b, int n)
{
    double **c = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++)
    {
        c[i] = (double*)malloc(n * sizeof(double));
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            c[i][j] = 0;
            for(int k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    return c;
}

typedef struct
{
    int rows;
    int cols;
    int from;
    int to;
    double **a;
    double **b;
    double **c;
} argMatrix;

void * thread_func(void *arg)
{
    argMatrix par = * (argMatrix *) arg;
    int i, j, row_index;
    for (row_index = par.from; row_index < par.to; row_index++)
    {
        for (i = 0; i < par.rows; i++)
        {
            par.c[row_index][i] = 0;
            for (j = 0; j < par.cols; j++)
            {
                par.c[row_index][i] += par.a[row_index][j] * par.b[j][i];
            }
        }
    }
    return NULL;
}

double** thread_mul_m(double **a, double **b, int n, int thcount) {
    double **c = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++)
    {
        c[i] = (double*)malloc(n * sizeof(double));
    }
    int add = 0;
    if(n <= thcount)
    {
        add = 1;
        thcount = n;
    }
    else
    {
        add = n / thcount;
    }
    pthread_t th[thcount];
    argMatrix par[thcount];
    int start=0;
    int end=0;
    int result;
    int status;
    int status_addr;
    for(int i = 0; i < thcount; i++)
    {
        start = end;
        if(i == thcount - 1)
        {
            end = n;
        }
        else
        {
            end += add;
        }
        par[i].rows = n;
        par[i].cols = n;
        par[i].a = a;
        par[i].b = b;
        par[i].c = c;
        par[i].from = start;
        par[i].to = end;
        result = pthread_create(&th[i], NULL, thread_func, &par[i]);
        if (result != 0)
        {
            perror("Creating thread error");
            return NULL;
        }

    }
    for(int i = 0; i < thcount; i++)
    {
        status = pthread_join(th[i], (void**)&status_addr);
        if (status != 0)
        {
            printf("main error: can't join thread, status = %d\n", status);
            return NULL;
        }
    }
    return c;
}
