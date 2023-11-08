#include "matrix.h"
#include <stdlib.h>
#include <errno.h> /* for ENOSYS */

int matrix_allocate(matrix_t *m, int rows, int columns) {
    /*Set rows and columns*/
    m->rows = rows;
    m->columns = columns;

    /*MEMORY ALLOCATION*/
    m->content = (int **)malloc(rows*sizeof(int *));
    if(m->content == NULL){
        return 2;
    }

    for (int i = 0; i< rows; i++){
        m->content[i] = (int *)malloc(columns * sizeof(int));
        if(m->content[i] == NULL){
            for(int j = 0; j < i; j++){
                free(m->content[j]);
            }
            free(m->content);

            return 2;
        }
    }

    return 0;
}

void matrix_free(matrix_t *m) {
    /* implement the function here ... */
}

void matrix_init_n(matrix_t *m, int n) {
    /* implement the function here ... */
}

void matrix_init_zeros(matrix_t *m) {
    /* implement the function here ... */
}

int matrix_init_identity(matrix_t *m){
    /* implement the function here ... */
    return -ENOSYS;
}
void matrix_init_rand(matrix_t *m, int val_min, int val_max) {
    /* implement the function here ... */
}

int matrix_equal(matrix_t *m1, matrix_t *m2) {
    /* implement the function here ... */
    return -ENOSYS;
}

int matrix_sum(matrix_t *m1, matrix_t *m2, matrix_t *result) {
    /* implement the function here ... */
    return -ENOSYS;
}

int matrix_scalar_product(matrix_t *m, int scalar, matrix_t *result) {
    /* implement the function here ... */
    return -ENOSYS;
}

int matrix_transposition(matrix_t *m, matrix_t *result) {
    /* implement the function here ... */
    return -ENOSYS;
}

int matrix_product(matrix_t *m1, matrix_t *m2, matrix_t *result) {
    /* implement the function here ... */
    return -ENOSYS;
}

int matrix_dump_file(matrix_t *m, char *output_file) {
    /* implement the function here ... */
    return -ENOSYS;
}

int matrix_allocate_and_init_file(matrix_t *m, char *input_file) {
    /* implement the function here ... */
    return -ENOSYS;
}