//
// Created by comradyo on 01.04.2021.
//

#include "../include/parallel.h"

_Bool sequential_searching_by_process(const float *vec_to_compare, const array_of_vectors *arr_of_vecs, size_t from_id,
                                      size_t to_id, norm_and_vector_id *_region) {
    if (vec_to_compare == NULL || arr_of_vecs == NULL || _region == NULL) {
        return 0;
    }
    if (arr_of_vecs->vectors == NULL) {
        return 0;
    }
    for (size_t i = from_id; i < to_id; ++i) {
        float temp_norm = calculate_norm(vec_to_compare, arr_of_vecs->vectors[i],
                                         arr_of_vecs->number_of_coordinates);
        if (temp_norm < 0) {
            return 0;
        }
        if (temp_norm < _region->norm) {
            _region->norm = temp_norm;
            _region->vector_id = i;
        }
    }
    return 1;
}

_Bool get_number_of_processes(size_t number_of_vectors, size_t *value_to_return) {
    *value_to_return = sysconf(_SC_NPROCESSORS_ONLN);
    if (value_to_return == 0) {
        return 0;
    }
    if (*value_to_return > number_of_vectors) {
        *value_to_return = number_of_vectors;
    }
    return 1;
}

_Bool
search_with_processes(const float *vec_to_compare, const array_of_vectors *arr_of_vecs, norm_and_vector_id *region,
                      size_t *id_to_return) {

    if (vec_to_compare == NULL || arr_of_vecs == NULL || id_to_return == NULL) {
        return 0;
    }
    if (arr_of_vecs->vectors == NULL) {
        return 0;
    }

    //Массив ID процессоров
    //Нужен для того, чтобы процесс-родитель убедился в том, что процессы-потомки завершились
    size_t num_of_processes = 0;
    if (get_number_of_processes(arr_of_vecs->number_of_vectors, &num_of_processes) == 0) {
        return 0;
    }

    int *processes = (int *) malloc(sizeof(int) * num_of_processes);
    if (processes == NULL) {
        return 0;
    }
    for (size_t i = 0; i < num_of_processes; ++i) {
        processes[i] = 0;
    }

    //В случае, если количество векторов не делится нацело на количество процессов, мы процессом-родителем считаем минимальную норму
    //для векторов с номерами [0, количество_векторов % количество_процессов).
    size_t end_for_parent_process = arr_of_vecs->number_of_vectors % num_of_processes;
    //Размер сегмента, с которым будет работать каждый дочерних из процессов.
    size_t size_of_segment_for_process = arr_of_vecs->number_of_vectors / num_of_processes;

    //Поиск минимальной нормы родительским процессом на интервале [0, end_for_parent_process).
    if (end_for_parent_process > 0) {
        if (sequential_searching_by_process(vec_to_compare, arr_of_vecs, 0,
                                            end_for_parent_process, region) == 0) {
            return 0;
        }
    }

    size_t id_to_start = 0;

    int pid = 1;
    for (size_t i = 0; i < num_of_processes; ++i) {
        if (pid > 0) {
            pid = fork();
            if (pid == -1) {
                return 0;
            }
            //С какого номера будет работать очередной процесс в массиве arr_of_vecs.
            id_to_start = end_for_parent_process + i * size_of_segment_for_process;
            if (pid > 0) {
                processes[i] = pid;
            }
        }
        if (pid == 0) {
            if (sequential_searching_by_process(vec_to_compare, arr_of_vecs, id_to_start,
                                                id_to_start + size_of_segment_for_process, region) == 0) {
                return 0;
            }
            exit(0);
        }
    }

    //Ожидание процессом-родителем завершения дочерних процессов.
    for (size_t i = 0; i < num_of_processes; ++i) {
        while (processes[i] != waitpid(processes[i], NULL, 0)) {}
    }

    *id_to_return = region->vector_id;
    return 1;
}

//Функция для параллельного поиска с помощью нескольких процессов
_Bool parallel_searching(const float *vec_to_compare, const array_of_vectors *arr_of_vecs, size_t *id_to_return) {

    if (vec_to_compare == NULL || arr_of_vecs == NULL || id_to_return == NULL) {
        return 0;
    }
    if (arr_of_vecs->vectors == NULL) {
        return 0;
    }

    norm_and_vector_id *region = mmap(NULL, sizeof(norm_and_vector_id), PROT_READ | PROT_WRITE,
                                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (region == MAP_FAILED) {
        return 0;
    }

    //Начальное заполнение region
    region->vector_id = 0;
    region->norm = calculate_norm(vec_to_compare, arr_of_vecs->vectors[0], arr_of_vecs->number_of_coordinates);

    if (search_with_processes(vec_to_compare, arr_of_vecs, region, id_to_return) == 0) {
        if (munmap(region, sizeof(size_t)) != 0) {
            return 0;
        }
    }

    if (munmap(region, sizeof(size_t)) != 0) {
        return 0;
    }

    return 1;
}