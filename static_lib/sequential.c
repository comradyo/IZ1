//
// Created by comradyo on 01.04.2021.
//

#include "../static_lib/sequential.h"

_Bool sequential_searching(const float *vec_to_compare, const array_of_vectors *arr_of_vecs,
                           size_t *id_vec_to_return) {
    if (vec_to_compare == NULL || arr_of_vecs == NULL) {
        return 0;
    }
    if (arr_of_vecs->vectors == NULL) {
        return 0;
    }
    *id_vec_to_return = 0;
    float norm = calculate_norm(vec_to_compare, arr_of_vecs->vectors[0], arr_of_vecs->number_of_coordinates);
    if (norm < 0) {
        return 0;
    }
    for (size_t i = 1; i < arr_of_vecs->number_of_vectors; ++i) {
        float temp_norm = calculate_norm(vec_to_compare, arr_of_vecs->vectors[i], arr_of_vecs->number_of_coordinates);
        if (temp_norm < 0) {
            return 0;
        }
        if (temp_norm < norm) {
            norm = temp_norm;
            *id_vec_to_return = i;
        }
    }
    return 1;
}