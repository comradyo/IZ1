#include "functions.h"

//Сгенерировать объект структуры массива векторов
array_of_vectors *generate_array_of_vectors(size_t num_of_vecs, size_t num_of_coords) {
    array_of_vectors *arr_of_vcs = (array_of_vectors *) malloc(sizeof(array_of_vectors));
    if (arr_of_vcs == NULL) {
        printf("ERROR: memory error, can't create the object of array_of_vectors\n");
        return NULL;
    }
    arr_of_vcs->vectors = (float **) malloc(sizeof(float *) * num_of_vecs);
    if (arr_of_vcs->vectors == NULL) {
        printf("ERROR: memory error, can't create the array in the object array_of_vectors\n");
        free(arr_of_vcs);
        arr_of_vcs = NULL;
        return NULL;
    }
    for (size_t i = 0; i < num_of_vecs; ++i) {
        arr_of_vcs->vectors[i] = (float *) malloc(sizeof(float *) * num_of_coords);
        if (arr_of_vcs->vectors[i] == NULL) {
            printf("ERROR: memory error, can't create the single vector in the array in the object array_of_vectors\n");
            for (int j = 0; j < i; ++j) {
                free(arr_of_vcs->vectors[j]);
                arr_of_vcs->vectors[j] = NULL;
            }
            free(arr_of_vcs->vectors);
            arr_of_vcs->vectors = NULL;
            return NULL;
        }
    }
    arr_of_vcs->number_of_vectors = num_of_vecs;
    arr_of_vcs->number_of_coordinates = num_of_coords;
    return arr_of_vcs;
}

//Подсчёт нормы
float calculate_norm(const float *vec_1, const float *vec_2, size_t num_of_coords) {
    if (vec_1 == NULL || vec_2 == NULL) {
        printf("ERROR: can't calculate norm, some of the input vectors are NULL\n");
        return -1.0f;
    }
    float _norm = 0.0f;
    for (size_t i = 0; i < num_of_coords; ++i) {
        _norm += (vec_1[i] - vec_2[i]) * (vec_1[i] - vec_2[i]);
    }
    return _norm;
}

//Очистка структуры массива векторов
void free_array_of_vectors(array_of_vectors *arr_of_vecs) {
    if (arr_of_vecs == NULL) {
        return;
    }
    if (arr_of_vecs->vectors == NULL) {
        free(arr_of_vecs);
        arr_of_vecs = NULL;
        return;
    }
    for (size_t i = 0; i < arr_of_vecs->number_of_vectors; ++i) {
        free(arr_of_vecs->vectors[i]);
        arr_of_vecs->vectors[i] = NULL;
    }
    free(arr_of_vecs->vectors);
    arr_of_vecs->vectors = NULL;
    free(arr_of_vecs);
    arr_of_vecs = NULL;
}

//Генерация файла с вектором заданной размерности
_Bool generate_file_with_vector(const char *name, size_t num_of_coords) {
    if (name == NULL) {
        printf("ERROR: name of the generated file is empty\n");
        return 0;
    }
    FILE *file = fopen(name, "w+");
    if (file == NULL) {
        printf("ERROR: can't generate file %s\n", name);
        return 0;
    }
    for (size_t j = 0; j < num_of_coords; ++j) {
        if (fprintf(file, "%f ", ((float) rand()) / (float) (RAND_MAX) * 100) < 0) {
            printf("ERROR: can't input float in file %s\n", name);
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

//Генерация файла с данными об объекте структуры массива векторов
_Bool generate_file_with_array(const char *name, size_t num_of_vectors, size_t num_of_coords) {
    if (name == NULL) {
        printf("ERROR: name of the generated file is empty\n");
        return 0;
    }
    FILE *file = fopen(name, "w+");
    if (file == NULL) {
        printf("ERROR: can't generate file %s\n", name);
        return 0;
    }
    if (fprintf(file, "%zu %zu\n", num_of_vectors, num_of_coords) < 0) {
        printf("ERROR: can't input float in file %s\n", name);
        fclose(file);
        return 0;
    }
    for (size_t i = 0; i < num_of_vectors; ++i) {
        for (size_t j = 0; j < num_of_coords; ++j) {
            if (fprintf(file, "%f ", ((float) rand()) / (float) (RAND_MAX) * 100) < 0) {
                printf("ERROR: can't input float in file %s\n", name);
                fclose(file);
                return 0;
            }
        }
        if (fprintf(file, "\n") < 0) {
            printf("ERROR: can't input the symbol in file %s\n", name);
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

//Извлечения вектора из файла
float *extract_vector_from_file(const char *filename, size_t num_of_coords) {
    if (filename == NULL) {
        printf("ERROR: name of the file is empty\n");
        return NULL;
    }
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("ERROR: can't open file %s\n", filename);
        return NULL;
    }

    float *vector = (float *) malloc(sizeof(float) * num_of_coords);
    if (vector == NULL) {
        printf("ERROR: malloc vector\n");
        fclose(file);
        return NULL;
    }

    for (size_t j = 0; j < num_of_coords; ++j) {
        if (fscanf(file, "%f", &vector[j]) != 1) {
            printf("ERROR: can't read float from file %s\n", filename);
            fclose(file);
            free(vector);
            return NULL;
        }
    }

    fclose(file);
    return vector;
}

//Извлечение объекта структуры массива векторов из файла
array_of_vectors *extract_array_from_file(const char *filename) {
    if (filename == NULL) {
        printf("ERROR: name of the file is empty\n");
        return NULL;
    }

    size_t num_of_vecs = 0;
    size_t num_of_coords = 0;

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("ERROR: can't open file %s\n", filename);
        return NULL;
    }

    if (fscanf(file, "%zu%zu", &num_of_vecs, &num_of_coords) != 2) {
        fclose(file);
        return NULL;
    }

    array_of_vectors *arr_of_vcs = generate_array_of_vectors(num_of_vecs, num_of_coords);
    if (arr_of_vcs == NULL) {
        fclose(file);
        return NULL;
    }
    if (arr_of_vcs->vectors == NULL) {
        fclose(file);
        free(arr_of_vcs);
        arr_of_vcs = NULL;
        return NULL;
    }

    for (size_t i = 0; i < arr_of_vcs->number_of_vectors; ++i) {
        for (size_t j = 0; j < arr_of_vcs->number_of_coordinates; ++j) {
            if (fscanf(file, "%f", &arr_of_vcs->vectors[i][j]) != 1) {
                printf("ERROR: can't read float from file %s\n", filename);
                fclose(file);
                free_array_of_vectors(arr_of_vcs);
                arr_of_vcs = NULL;
                return NULL;
            }
        }
    }

    fclose(file);
    return arr_of_vcs;
}