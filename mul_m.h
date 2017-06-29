//
// Created by Antonio Maksimovich on 30.06.2017.
//

#ifndef MATRIX_MUL_M_H
#define MATRIX_MUL_M_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0


// generate matrix
// n - dimension
// min - value in matrix
// max - value in matrix
double** generate_m(int n, int min, int max);

//print matrix
void print_m(double **a, int n);

//check equivalence
int is_equal_m(double **a, double **b, int n);

//delete matrix from memory
void delete_m(double **a, int n);

//Multiplication of two matrices without multithreading
double** no_thread_mul_m(double **a, double **b, int n);

//Multiplication of two matrices with multithreading
double** thread_mul_m(double **a, double **b, int n, int thcount);




#endif //MATRIX_MUL_M_H
