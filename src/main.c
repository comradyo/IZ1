#include <malloc.h>
#include <time.h>
#include <string.h>

#include "functions.h"
#include "parallel.h"
#include "sequential.h"

void print_vectors(const array_of_vectors *arr_of_vecs) {
    if (arr_of_vecs == NULL) {
        return;
    }
    for (size_t i = 0; i < arr_of_vecs->number_of_vectors; ++i) {
        printf("vector %zu%s", i, " :\n");
        for (size_t j = 0; j < arr_of_vecs->number_of_coordinates; ++j) {
            printf("%f\t", arr_of_vecs->vectors[i][j]);
        }
        printf("\n");
    }
}

#define MAX_SIZE_OF_FILE_NAME 100

int main(int argc, char *argv[]) {

    srand(time(NULL));

    if (argc != 3) {
        printf("ERROR: no arguments\n");
        return 0;
    }

    char arr_file_name[MAX_SIZE_OF_FILE_NAME];
    if (strcpy(arr_file_name, argv[1]) == NULL) {
        printf("ERROR: can't strcpy to arr_file_name\n");
        return 0;
    }
    char vec_file_name[MAX_SIZE_OF_FILE_NAME];
    if (strcpy(vec_file_name, argv[2]) == NULL) {
        printf("ERROR: can't strcpy to vec_file_name\n");
        return 0;
    }
    size_t num_of_vecs = 0;
    size_t num_of_coords = 0;

    array_of_vectors *arr_of_vecs = extract_array_from_file(arr_file_name);
    if (arr_of_vecs == NULL) {
        printf("ERROR: can't extract array of vectors from %s\n", arr_file_name);
        return 0;
    }
    num_of_vecs = arr_of_vecs->number_of_vectors;
    num_of_coords = arr_of_vecs->number_of_coordinates;

    float *vector = extract_vector_from_file(vec_file_name, num_of_coords);
    if (vector == NULL) {
        printf("ERROR: can't extract vector from %s\n", vec_file_name);
        free_array_of_vectors(arr_of_vecs);
        return 0;
    }

    clock_t tic = clock();
    clock_t toc = clock();

    tic = clock();
    size_t id_of_found_vec_seq = 0;
    if (sequential_searching(vector, arr_of_vecs, &id_of_found_vec_seq) == 0) {
        printf("ERROR: unable to get id with sequential searching\n");
        free(vector);
        free_array_of_vectors(arr_of_vecs);
        return 0;
    }
    toc = clock();
    double time_posl = (double) (toc - tic) / 10000;

    printf("id of found vector with sequential searching = %zu \nTime of sequential searching = %f\n\n",
           id_of_found_vec_seq, time_posl);

    tic = clock();
    size_t id_of_found_vec_par = 0;
    if (parallel_searching(vector, arr_of_vecs, &id_of_found_vec_par) == 0) {
        printf("ERROR: unable to get id with parallel_searching\n");
        free(vector);
        free_array_of_vectors(arr_of_vecs);
        return 0;
    }
    toc = clock();
    double time_parallel = (double) (toc - tic) / 10000;

    printf("id of found vector with parallel searching = %zu \nTime of parallel searching = %f\n\n",
           id_of_found_vec_par, time_parallel);

    free(vector);
    free_array_of_vectors(arr_of_vecs);

    if (id_of_found_vec_par == id_of_found_vec_seq) {
        printf("Results of the both types os searching are equal!\n");
        return 1;
    } else {
        printf("Results are not equal!\n");
        return -1;
    }
    return 0;
}
