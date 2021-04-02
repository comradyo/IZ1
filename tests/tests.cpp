#include "gtest/gtest.h"

extern "C" {
#include "sequential.h"
#include "functions.h"
#include "parallel.h"
}

const char *test_vector_5 = "../tests/test_vector_5.txt";
const char *test_vector_20 = "../tests/test_vector_20.txt";
const char *test_vector_100 = "../tests/test_vector_100.txt";

const char *test_array_5000_5 = "../tests/test_array_5000_5.txt";
const char *test_array_10000_20 = "../tests/test_array_10000_20.txt";
const char *test_array_50000_100 = "../tests/test_array_50000_100.txt";

const char *test_vector_generated_file = "../tests/test_vector_generated_file.txt";
const char *test_array_generated_file = "../tests/test_array_generated_file.txt";

TEST(calculating_norm, test_1) {

    size_t num_of_coords = 4;

    const float vector_1[] = {10.f, 15.f, 13.2f, 17.6f};
    const float vector_2[] = {1.f, 0.f, 23.8f, 14.654f};

    float result = calculate_norm(vector_1, vector_2, num_of_coords);

    EXPECT_NEAR(427.039, result, 0.001);
}

TEST(calculating_norm, test_2) {

    size_t num_of_coords = 4;

    const float vector_1[] = {0.f, 1.f, 0.f, 1.f};
    const float vector_2[] = {1.f, 0.f, 1.f, 0.f};

    float result = calculate_norm(vector_1, vector_2, num_of_coords);

    EXPECT_NEAR(4, result, 0.001);
}

TEST(sequential_search, test_1) {

    float vector[] = {72.f, 85.f};
    array_of_vectors *arr = generate_array_of_vectors(5, 2);
    arr->vectors[0][0] = 84.929016;
    arr->vectors[0][1] = 80.385117;
    arr->vectors[1][0] = 72.363838;
    arr->vectors[1][1] = 83.619415;
    arr->vectors[2][0] = 25.058443;
    arr->vectors[2][1] = 32.260742;
    arr->vectors[3][0] = 3.723581;
    arr->vectors[3][1] = 4.359436;
    arr->vectors[4][0] = 82.481308;
    arr->vectors[4][1] = 32.260742;

    size_t id_to_return = 0;
    sequential_searching(vector, arr, &id_to_return);
    ASSERT_EQ(id_to_return, 1);
    free_array_of_vectors(arr);
}

TEST(sequential_search, test_2) {

    float vector[] = {82.1f, 32.05f};
    array_of_vectors *arr = generate_array_of_vectors(5, 2);
    arr->vectors[0][0] = 84.929016;
    arr->vectors[0][1] = 80.385117;
    arr->vectors[1][0] = 72.363838;
    arr->vectors[1][1] = 83.619415;
    arr->vectors[2][0] = 25.058443;
    arr->vectors[2][1] = 32.260742;
    arr->vectors[3][0] = 3.723581;
    arr->vectors[3][1] = 4.359436;
    arr->vectors[4][0] = 82.481308;
    arr->vectors[4][1] = 32.260742;

    size_t id_to_return = 0;
    sequential_searching(vector, arr, &id_to_return);
    ASSERT_EQ(id_to_return, 4);

    free_array_of_vectors(arr);
}

TEST(sequential_search, test_3) {

    float *vector = extract_vector_from_file(test_vector_5, 5);
    array_of_vectors *arr = extract_array_from_file(test_array_5000_5);

    size_t id_to_return = 0;
    sequential_searching(vector, arr, &id_to_return);
    ASSERT_EQ(id_to_return, 3802);

    free(vector);
    free_array_of_vectors(arr);
}

TEST(sequential_search, test_4) {
    float *vector = extract_vector_from_file(test_vector_20, 20);
    array_of_vectors *arr = extract_array_from_file(test_array_10000_20);

    size_t id_to_return = 0;
    sequential_searching(vector, arr, &id_to_return);
    ASSERT_EQ(id_to_return, 3205);

    free(vector);
    free_array_of_vectors(arr);
}

TEST(parallel_search, test_1) {

    float vector[] = {72.f, 85.f};
    array_of_vectors *arr = generate_array_of_vectors(5, 2);
    arr->vectors[0][0] = 84.929016;
    arr->vectors[0][1] = 80.385117;
    arr->vectors[1][0] = 72.363838;
    arr->vectors[1][1] = 83.619415;
    arr->vectors[2][0] = 25.058443;
    arr->vectors[2][1] = 32.260742;
    arr->vectors[3][0] = 3.723581;
    arr->vectors[3][1] = 4.359436;
    arr->vectors[4][0] = 82.481308;
    arr->vectors[4][1] = 32.260742;

    size_t id_to_return = 0;
    parallel_searching(vector, arr, &id_to_return);
    ASSERT_EQ(id_to_return, 1);

    free_array_of_vectors(arr);
}

TEST(parallel_search, test_2) {

    float vector[] = {82.1f, 32.05f};
    array_of_vectors *arr = generate_array_of_vectors(5, 2);
    arr->vectors[0][0] = 84.929016;
    arr->vectors[0][1] = 80.385117;
    arr->vectors[1][0] = 72.363838;
    arr->vectors[1][1] = 83.619415;
    arr->vectors[2][0] = 25.058443;
    arr->vectors[2][1] = 32.260742;
    arr->vectors[3][0] = 3.723581;
    arr->vectors[3][1] = 4.359436;
    arr->vectors[4][0] = 82.481308;
    arr->vectors[4][1] = 32.260742;

    size_t id_to_return = 0;
    parallel_searching(vector, arr, &id_to_return);
    ASSERT_EQ(id_to_return, 4);

    free_array_of_vectors(arr);
}

TEST(parallel_search, test_3) {

    float *vector = extract_vector_from_file(test_vector_5, 5);
    array_of_vectors *arr = extract_array_from_file(test_array_5000_5);

    size_t id_to_return = 0;
    parallel_searching(vector, arr, &id_to_return);
    ASSERT_EQ(id_to_return, 3802);

    free(vector);
    free_array_of_vectors(arr);
}

TEST(parallel_search, test_4) {
    float *vector = extract_vector_from_file(test_vector_20, 20);
    array_of_vectors *arr = extract_array_from_file(test_array_10000_20);

    size_t id_to_return = 0;
    parallel_searching(vector, arr, &id_to_return);
    ASSERT_EQ(id_to_return, 3205);

    free(vector);
    free_array_of_vectors(arr);
}

TEST(seq_and_par_eq, test_1) {
    float *vector = extract_vector_from_file(test_vector_5, 5);
    array_of_vectors *arr = extract_array_from_file(test_array_5000_5);

    size_t id_seq = 0;
    size_t id_par = 0;

    sequential_searching(vector, arr, &id_seq);
    parallel_searching(vector, arr, &id_par);

    ASSERT_EQ(id_seq, id_par);

    free(vector);
    free_array_of_vectors(arr);
}

TEST(seq_and_par_eq, test_2) {
    size_t num_of_coords = 30;
    size_t num_of_vectors = 1000;

    generate_file_with_vector(test_vector_generated_file, num_of_coords);
    generate_file_with_array(test_array_generated_file, num_of_vectors, num_of_coords);

    float *vector = extract_vector_from_file(test_vector_generated_file, num_of_coords);
    array_of_vectors *arr = extract_array_from_file(test_array_generated_file);

    size_t id_seq = 0;
    size_t id_par = 0;

    sequential_searching(vector, arr, &id_seq);
    parallel_searching(vector, arr, &id_par);

    ASSERT_EQ(id_seq, id_par);

    free(vector);
    free_array_of_vectors(arr);
}

TEST(seq_and_par_eq, test_3) {
    size_t num_of_coords = 1000;
    size_t num_of_vectors = 1000;

    generate_file_with_vector(test_vector_generated_file, num_of_coords);
    generate_file_with_array(test_array_generated_file, num_of_vectors, num_of_coords);

    float *vector = extract_vector_from_file(test_vector_generated_file, num_of_coords);
    array_of_vectors *arr = extract_array_from_file(test_array_generated_file);

    size_t id_seq = 0;
    size_t id_par = 0;

    sequential_searching(vector, arr, &id_seq);
    parallel_searching(vector, arr, &id_par);

    ASSERT_EQ(id_seq, id_par);

    free(vector);
    free_array_of_vectors(arr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}