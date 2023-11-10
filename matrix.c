#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h> /* for ENOSYS */

int matrix_allocate(matrix_t *m, int rows, int columns) {
     if (m == NULL) {
        return 1; // Invalid matrix.
    }

    /* Set rows and columns */
    m->rows = rows;
    m->columns = columns;

    /* Memory allocation */
    m->content = (int **)malloc(rows * sizeof(int *));
    if (m->content == NULL) {
        return 2; // Failed to allocate memory.
    }

    for (int i = 0; i < rows; i++) {
        m->content[i] = (int *)malloc(columns * sizeof(int));
        if (m->content[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(m->content[j]);
            }
            free(m->content);
            return 2; // Failed to allocate memory.
        }
    }

    return 0; // Memory allocation successful.
}
void matrix_free(matrix_t *m) {


    if(m!= NULL){
        if(m-> content != NULL){
            for (int i = 0; i< m->rows; i++){
                free(m->content[i]);   
            }
            free(m->content);
            m->content = NULL;
        }
    }
    m->rows = 0;
    m->columns = 0;

}

void matrix_init_n(matrix_t *m, int n) {


    if (m-> content != NULL){
        for (int i = 0; i < m->rows; i++) {
            for (int j = 0; j < m->columns; j++) {
            m->content[i][j] = n;
        }
    }

    }

}

void matrix_init_zeros(matrix_t *m) {
    if (m-> content != NULL){
        for (int i = 0; i < m->rows; i++) {
            for (int j = 0; j < m->columns; j++) {
            m->content[i][j] = 0;
        }
    }

    }
}

int matrix_init_identity(matrix_t *m){
    if (m == NULL || m->content == NULL || m->rows != m->columns) {
        return 1; 
    }
    for (int i = 0; i < m->rows; i++) {
            for (int j = 0; j < m->columns; j++) {
            if (i == j){
                m->content[i][j] = 1;
            }
            else{
                m->content[i][j] = 0;
            }
            
        }
    }
    return 0;
}
void matrix_init_rand(matrix_t *m, int val_min, int val_max) {


    if (m-> content != NULL){
        for (int i = 0; i < m->rows; i++) {
            for (int j = 0; j < m->columns; j++) {
            int randnum = rand() % (val_max + 1 - val_min) + val_min;
            m->content[i][j] = randnum;
        }
    }

    }
}

int matrix_equal(matrix_t *m1, matrix_t *m2) {
    if (m1 == NULL || m2 == NULL || m1->rows != m2->rows || m1->columns != m2->columns) {
        return 0; 
    }


    for (int i = 0; i < m1->rows; i++) {
            for (int j = 0; j < m1->columns; j++) {
            if (m1->content[i][j] != m2->content[i][j]){
                return 0;
                }
            }

        }



    return 1;
}

int matrix_sum(matrix_t *m1, matrix_t *m2, matrix_t *result) {
    if (m1 == NULL || m2 == NULL || result == NULL ||
        m1->rows != m2->rows || m1->columns != m2->columns) {
        return 1; 
    }

    int rows = m1->rows;
    int columns = m1->columns;

    int resultCode = matrix_allocate(result, rows, columns);
    
    if (resultCode != 0) {
        return resultCode; 
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result->content[i][j] = m1->content[i][j] + m2->content[i][j];
        }
    }

    return 0;
}

int matrix_scalar_product(matrix_t *m, int scalar, matrix_t *result) {
    if (m && m->content){
        if(matrix_allocate(result,m->rows,m->columns) != 0){
            return -1;
        }
        for(int i=0; i< m->rows; i++){
            for(int j = 0; j< m->columns; j++){
                result->content[i][j] = m->content[i][j] * scalar;
            }

        }
        return 0;
    }
    return -1;
 
}


int matrix_transposition(matrix_t *m, matrix_t *result) {
    if (m == NULL || m->content == NULL || m->rows <= 0 || m->columns <= 0 || result == NULL) {
        return 1;
    }

    int rows = m->columns;
    int columns = m->rows;

    int result_code = matrix_allocate(result, rows, columns);

    if (result_code != 0) {
        return result_code; 
    }

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            result->content[j][i] = m->content[i][j];
        }
    }

    return 0; // Return 0 for success
}

int matrix_product(matrix_t *m1, matrix_t *m2, matrix_t *result) {
    if (m1 == NULL || m2 == NULL || result == NULL || m1->columns != m2->rows) {
        return 1; 
    }
    int rows = m1->rows;
    int columns = m2->columns;

    int result_code = matrix_allocate(result, rows, columns);

    if (result_code != 0) {
        return result_code; 
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result->content[i][j] = 0;
            for (int k = 0; k < m1->columns; k++) {
                result->content[i][j] += m1->content[i][k] * m2->content[k][j];
            }
        }
    }

    return 0;
    
}

int matrix_dump_file(matrix_t *m, char *output_file) {
    FILE *file = fopen(output_file, "w");

    if (file == NULL) {
        // Failed to open the file
        return -1;
    }

    // Iterate through the matrix rows and write them to the file
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            // Write each element, separated by spaces
            fprintf(file, "%d", m->content[i][j]);

            // Add a space unless it's the last element in the row
            if (j < m->columns - 1) {
                fprintf(file, " ");
            }
        }

        // Add a newline to separate rows
        fprintf(file, "\n");
    }

    // Close the file
    fclose(file);

    return 0;
}


int matrix_allocate_and_init_file(matrix_t *m, char *input_file) {
    FILE *file = fopen(input_file, "r");

    if (file == NULL) {
        return -1; // Failed to open the file.
    }

    // FIND COLUMNS AND ROWS IN MATRIX IN FILE
    int rows = 0, columns = 0;
    char line[1024];

    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, " "); // Split the line by space

        int current_columns = 0;

        while (token != NULL) {
            current_columns++;
            token = strtok(NULL, " ");
        }

        if (columns == 0) {
            columns = current_columns;
        } else if (current_columns != columns) {
            fclose(file);
            return 1; // Inconsistent number of columns in the matrix.
        }

        rows++;
    }

    fclose(file);

    // ALLOCATE TO MATRIX
    int resultCode = matrix_allocate(m, rows, columns);

    if (resultCode != 0) {
        return resultCode; // Memory allocation failed.
    }

    // READ VALUES FROM FILE AND INITIALIZE THE MATRIX
    file = fopen(input_file, "r");

    if (file == NULL) {
        return -1; // Failed to open the file.
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (fscanf(file, "%d", &m->content[i][j]) != 1) {
                fclose(file);
                return 1; // Failed to read a value from the file.
            }
        }
    }

    fclose(file);

    return 0; // Successfully allocated and initialized the matrix.
}

int main(){
    return 0;
}
    
