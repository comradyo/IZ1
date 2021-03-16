#include "gtest/gtest.h"

extern "C" {
    #include "Warships.h"
}

TEST(list_testing, test_1) {
    List lst_1;
    lst_1.head = NULL;

    List lst_2;
    lst_2.head = NULL;

    ASSERT_TRUE(lists_are_equal(&lst_1, &lst_2));

    clear_list(&lst_1);
    clear_list(&lst_2);
}

TEST(list_testing, test_2) {
    List lst_1;
    lst_1.head = NULL;

    List lst_2;
    lst_2.head = NULL;
    push_front(&lst_2, 10);

    ASSERT_FALSE(lists_are_equal(&lst_1, &lst_2));

    clear_list(&lst_1);
    clear_list(&lst_2);
}

TEST(list_testing, test_3) {
    List lst_1;
    lst_1.head = NULL;
    push_front(&lst_1, 1);
    push_front(&lst_1, 2);
    push_front(&lst_1, 3);
    push_front(&lst_1, 4);

    List lst_2;
    lst_2.head = NULL;
    push_front(&lst_2, 1);
    push_front(&lst_2, 2);
    push_front(&lst_2, 3);
    push_front(&lst_2, 4);

    ASSERT_TRUE(lists_are_equal(&lst_1, &lst_2));

    clear_list(&lst_1);
    clear_list(&lst_2);
}

TEST(list_testing, test_4) {
    List lst_1;
    lst_1.head = NULL;
    push_front(&lst_1, 1);
    push_front(&lst_1, 2);
    push_front(&lst_1, 1);
    push_front(&lst_1, 1);
    push_front(&lst_1, 1);

    List lst_2;
    lst_2.head = NULL;
    push_front(&lst_2, 1);
    push_front(&lst_2, 1);
    push_front(&lst_2, 1);
    push_front(&lst_2, 1);
    push_front(&lst_2, 1);

    ASSERT_FALSE(lists_are_equal(&lst_1, &lst_2));

    clear_list(&lst_1);
    clear_list(&lst_2);
}

TEST(list_testing, test_5) {
    List lst_1;
    lst_1.head = NULL;
    push_front(&lst_1, 1);
    push_front(&lst_1, 2);
    push_front(&lst_1, 3);
    push_front(&lst_1, 4);
    push_front(&lst_1, 5);

    List lst_2;
    lst_2.head = NULL;
    push_front(&lst_2, 1);
    push_front(&lst_2, 2);
    push_front(&lst_2, 3);
    push_front(&lst_2, 4);

    ASSERT_FALSE(lists_are_equal(&lst_1, &lst_2));

    clear_list(&lst_1);
    clear_list(&lst_2);
}

TEST(list_testing, test_6) {
    List lst_1;
    lst_1.head = NULL;
    push_front(&lst_1, 1);
    push_front(&lst_1, 2);
    push_front(&lst_1, 3);
    push_front(&lst_1, 4);

    List lst_2;
    lst_2.head = NULL;
    push_front(&lst_2, 1);
    push_front(&lst_2, 2);
    push_front(&lst_2, 3);
    push_front(&lst_2, 4);
    push_front(&lst_2, 5);

    ASSERT_FALSE(lists_are_equal(&lst_1, &lst_2));

    clear_list(&lst_1);
    clear_list(&lst_2);
}

TEST(warship_searching, test_with_no_parameters) {
    char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME] = {
            "", "", "", "", "", ""
    };
    List correct_list;
    correct_list.head = NULL;
    for(int i = 0; i<NUMBER_OF_WARSHIPS; ++i)
        push_front(&correct_list, i);

    List tested_list = warship_search(parameters);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_one_parameter_1) {
    char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME] = {
            "Nikolay II", "", "", "", "", ""
    };
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 0);

    List tested_list = warship_search(parameters);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_one_parameter_2) {
    char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME] = {
            "", "Severodvinsk", "", "", "", ""
    };
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 3);
    push_front(&correct_list, 4);
    push_front(&correct_list, 9);

    List tested_list = warship_search(parameters);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_one_parameter_3) {
    char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME] = {
            "", "", "2005", "", "", ""
    };
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 0);
    push_front(&correct_list, 5);
    push_front(&correct_list, 6);
    push_front(&correct_list, 9);

    List tested_list = warship_search(parameters);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_one_parameter_4) {
    char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME] = {
            "", "", "", "26", "", ""
    };
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 3);
    push_front(&correct_list, 9);

    List tested_list = warship_search(parameters);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_one_parameter_5) {
    char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME] = {
            "", "", "", "", "War for USSR", ""
    };
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 1);
    push_front(&correct_list, 2);
    push_front(&correct_list, 3);
    push_front(&correct_list, 4);

    List tested_list = warship_search(parameters);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_one_parameter_6) {
    char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME] = {
            "", "", "", "", "", "On combat duty"
    };
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 1);
    push_front(&correct_list, 2);
    push_front(&correct_list, 4);
    push_front(&correct_list, 5);
    push_front(&correct_list, 6);
    push_front(&correct_list, 8);

    List tested_list = warship_search(parameters);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_several_parameters_1) {
    char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME] = {
            "", "", "2005", "", "", "On combat duty"
    };
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 5);
    push_front(&correct_list, 6);

    List tested_list = warship_search(parameters);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_several_parameters_2) {
    char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME] = {
            "", "", "1990", "", "War for Russia", ""
    };
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 3);
    push_front(&correct_list, 8);

    List tested_list = warship_search(parameters);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_several_parameters_3) {
    char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME] = {
            "", "Bohay", "", "13", "", ""
    };
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 1);
    push_front(&correct_list, 7);

    List tested_list = warship_search(parameters);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_all_parameters_1) {
    char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME] = {
            "Yastreb", "Murmansk", "2005", "50", "War for Belarus", "On combat duty"
    };
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 5);

    List tested_list = warship_search(parameters);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_all_parameters_2) {
    char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME] = {
            "Powerbank", "New-York", "1990", "48", "War for USA", "On combat duty"
    };
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 8);

    List tested_list = warship_search(parameters);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, incorrect_input_1) {
    char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME] = {
            "Comrade Xi", "Bohay", "hello", "13", "War for China", "On combat duty"
    };
    ASSERT_EQ(read_parameters(parameters), -1);
}

TEST(warship_searching, incorrect_input_2) {
    char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME] = {
            "Molnia", "Severodvinsk", "2005", "bye", "War for Earth", "Decommissioned"
    };
    ASSERT_EQ(read_parameters(parameters), -1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}