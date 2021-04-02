#ifndef IZ2_FUNCTIONS_H
#define IZ2_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    size_t number_of_vectors;
    size_t number_of_coordinates;
    float **vectors;
} array_of_vectors;

//Генерация объекта структуры array_of_vectors
array_of_vectors *generate_array_of_vectors(size_t num_of_vecs, size_t num_of_coords);

//Подсчёт нормы двух векторов
float calculate_norm(const float *vec_1, const float *vec_2, size_t num_of_coords);

//Освобождение памяти объекта структуры array_of_vectors
void free_array_of_vectors(array_of_vectors *arr_of_vecs);

//Генерация текстового файла с данными о векторе указанной размерности
_Bool generate_file_with_vector(const char *name, size_t num_of_coords);

//Извлечение вектора заданной размерности из файла
//float *extract_vector_from_file(FILE *file, size_t num_of_coords);

//Генерация файла с данными об объекте структуры array_of_vectors
_Bool generate_file_with_array(const char *name, size_t num_of_vectors, size_t num_of_coords);

//Извлечение объекта структуры array_of_vectors из файла
array_of_vectors *extract_vectors_from_file(FILE *file);

//Извлечение объекта структуры array_of_vectors из файла
array_of_vectors *extract_array_from_file(const char *filename);

float *extract_vector_from_file(const char *filename, size_t num_of_coords);

#endif //IZ2_FUNCTIONS_H
