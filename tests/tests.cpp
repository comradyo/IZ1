#include "gtest/gtest.h"

extern "C" {
    #include "../include/Warships.h"
}

const Warship warships[NUMBER_OF_WARSHIPS] = {
        0, "Nikolay II", "Murmansk", 2005, 50, "Decommissioned", {"War for Belarus", "War for Japan", "War for Uganda"},
        1, "Comrade Xi", "Bohay", 1990, 13, "On combat duty", {"War for China", "War for Afghanistan", "War for USSR"},
        2, "Donald Trump", "Bayliner", 2018, 50, "On combat duty", {"War for USSR", "War for Russia", "War for China"},
        3, "Aleksandr III", "Severodvinsk", 1990, 26, "Decommissioned", {"War for USSR", "War for Russia", "War for USA"},
        4, "Ivan Grozny", "Severodvinsk", 1950, 13, "On combat duty", {"War for China", "War for Japan", "War for USSR"},
        5, "Yastreb", "Murmansk", 2005, 50, "On combat duty", {"War for Belarus", "War for Ukraine", "War for Russia"},
        6, "Tuang", "Peking", 2005, 48, "On combat duty", {"War for Earth", "War for England", "War for China"},
        7, "Chan", "Bohay", 2018, 13, "Decommissioned", {"War for Belarus", "War for Russia", "War for Uganda"},
        8, "Powerbank", "New-York", 1990, 48, "On combat duty", {"War for Russia", "War for England", "War for USA"},
        9, "Molnia", "Severodvinsk", 2005, 26, "Decommissioned", {"War for Earth", "War for England", "War for China"}
};

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
    Warship parameters = {0, "", "", 0, 0, "", {"", "", ""}};
    List correct_list;
    correct_list.head = NULL;
    for(int i = 0; i<NUMBER_OF_WARSHIPS; ++i)
        push_front(&correct_list, i);

    List tested_list = search_warships(&parameters, warships, NUMBER_OF_WARSHIPS);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_one_parameter_1) {
    Warship parameters = {0, "Chan", "", 0, 0, "", {"", "", ""}};
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 7);

    List tested_list = search_warships(&parameters, warships, NUMBER_OF_WARSHIPS);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_one_parameter_2) {
    Warship parameters = {0, "", "Severodvinsk", 0, 0, "", {"", "", ""}};
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 3);
    push_front(&correct_list, 4);
    push_front(&correct_list, 9);

    List tested_list = search_warships(&parameters, warships, NUMBER_OF_WARSHIPS);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_several_parameters_1) {
    Warship parameters = {0, "", "", 2005, 0, "On combat duty", {"", "", ""}};
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 5);
    push_front(&correct_list, 6);

    List tested_list = search_warships(&parameters, warships, NUMBER_OF_WARSHIPS);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_several_parameters_2) {
    Warship parameters = {0, "", "", 1990, 0, "", {"", "War for Russia", ""}};
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 3);

    List tested_list = search_warships(&parameters, warships, NUMBER_OF_WARSHIPS);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_all_parameters_1) {
    Warship parameters = {0, "Nikolay II", "Murmansk", 2005, 50, "Decommissioned", {"War for Belarus", "War for Japan", "War for Uganda"}};
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 0);

    List tested_list = search_warships(&parameters, warships, NUMBER_OF_WARSHIPS);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, test_with_all_parameters_2) {
    Warship parameters = {0, "Chan", "Bohay", 2018, 13, "Decommissioned", {"War for Belarus", "War for Russia", "War for Uganda"}};
    List correct_list;
    correct_list.head = NULL;
    push_front(&correct_list, 7);

    List tested_list = search_warships(&parameters, warships, NUMBER_OF_WARSHIPS);

    ASSERT_TRUE(lists_are_equal(&correct_list, &tested_list));
    clear_list(&correct_list);
    clear_list(&tested_list);
}

TEST(warship_searching, comparing_warships_1) {
    Warship ws1 = {7, "Chan", "Bohay", 2018, 13, "Decommissioned", {"War for Belarus", "War for Russia", "War for Uganda"}};
    Warship ws2 = {7, "Chan", "Bohay", 2018, 13, "Decommissioned", {"War for Belarus", "War for Russia", "War for Uganda"}};
    ASSERT_TRUE(compare_two_warships(ws1, ws2));
}

TEST(warship_searching, compare_warships_2) {
    Warship ws1 = {7, "Chan", "Bohay", 2018, 13, "Decommissioned", {"War for Belarus", "War for Russia", "War for Uganda"}};
    Warship ws2 = {2, "Donald Trump", "Bayliner", 2018, 50, "On combat duty", {"War for USSR", "War for Russia", "War for China"}};
    ASSERT_FALSE(compare_two_warships(ws1, ws2));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}