//
// Created by comradyo on 01.04.2021.
//

#ifndef IZ2_PARALLEL_H
#define IZ2_PARALLEL_H
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include "functions.h"

//Структура, хранящая ID вектора и значение нормы от него и другого вектора
//Необходима для mmap в реализации под процессы.
typedef struct {
    size_t vector_id;
    float norm;
} norm_and_vector_id;

_Bool sequential_searching_by_process(const float *vec_to_compare, const array_of_vectors *arr_of_vecs, size_t from_id,
                                      size_t to_id, norm_and_vector_id *_region);

_Bool get_number_of_processes(size_t number_of_vectors, size_t *value_to_return);

_Bool
search_with_processes(const float *vec_to_compare, const array_of_vectors *arr_of_vecs, norm_and_vector_id *region,
                      size_t *id_to_return);

//Функция для параллельного поиска с помощью нескольких процессов
_Bool parallel_searching(const float *vec_to_compare, const array_of_vectors *arr_of_vecs, size_t *id_to_return);

#endif //IZ2_PARALLEL_H
