#include <stdlib.h>
#include "../include/Warships.h"
#include "stdio.h"
#include "string.h"

_Bool initialize_warship(Warship* warship_to_initialize, _Bool to_search) {
    if(warship_to_initialize == NULL) return 0;

    printf("Enter the name of the warship: ");
    if(fgets(warship_to_initialize->name, SIZE_OF_NAME, stdin) == NULL) {
        return 0;
    }
    warship_to_initialize->name[strcspn(warship_to_initialize->name, "\n")] = 0;
    if(to_search == 0 && strlen(warship_to_initialize->name) == 0) {
        return 0;
    }

    printf("Enter the shipyard: ");
    if(fgets(warship_to_initialize->shipyard, SIZE_OF_NAME, stdin) == NULL) {
        return 0;
    }
    warship_to_initialize->shipyard[strcspn(warship_to_initialize->shipyard, "\n")] = 0;
    if(to_search == 0 && strlen(warship_to_initialize->shipyard) == 0) {
        return 0;
    }

    printf("Enter the year of descending: ");
    if(scanf("%d", &warship_to_initialize->year_of_descent) == 0) {
        return 0;
    }
    if(to_search == 0 && warship_to_initialize->year_of_descent == 0) {
        return 0;
    }

    printf("Enter the number of crewmates: ");
    if(scanf("%d", &warship_to_initialize->number_of_crewmates) == 0) {
        return 0;
    }
    if(to_search == 0 && warship_to_initialize->number_of_crewmates == 0) {
        return 0;
    }
    getchar();

    printf("Enter the condition: ");
    if(fgets(warship_to_initialize->condition, SIZE_OF_NAME, stdin) == NULL) {
        return 0;
    }
    warship_to_initialize->condition[strcspn(warship_to_initialize->condition, "\n")] = 0;
    if(to_search == 0 && strlen(warship_to_initialize->condition) == 0) {
        return 0;
    }

    for(size_t i = 0; i<NUMBER_OF_BATTLES; ++i) {
        printf("Enter the name of %zu%s", i, " battle: ");
        if(fgets(warship_to_initialize->battles[i], SIZE_OF_NAME, stdin) == NULL) {
            return 0;
        }
        warship_to_initialize->battles[i][strcspn(warship_to_initialize->battles[i], "\n")] = 0;
        if(to_search == 0 && strlen(warship_to_initialize->battles[i]) == 0) {
            return 0;
        }
    }

    return 1;
}

_Bool fill_array_of_warships(Warship* array_of_warships, size_t size_of_array) {
    if(array_of_warships == NULL || size_of_array < 2) {
        return 0;
    }
    for(size_t i = 0; i<size_of_array; ++i) {
        printf("\n======================================\n");
        printf("Initialization of %zu%s", i, " warship\n");
        printf("======================================\n");
        if(initialize_warship(&array_of_warships[i], 0) == 0) {
            return 0;
        }
    }
    return 1;
}

void print_list_of_warships(List *list_of_warships, const Warship* array_of_warships, size_t size_of_array) {
    if(list_of_warships == NULL || array_of_warships == NULL || size_of_array < 2) {
        return;
    }
    Node *node_temp_warship = list_of_warships->head;
    if(node_temp_warship == NULL) {
        printf("No warships found\n");
        return;
    }
    while (node_temp_warship != NULL) {
        if(node_temp_warship->value < 0 || node_temp_warship->value >= size_of_array) {
            printf("Incorrect list of warships\n");
            return;
        }
        Warship temp_warship = array_of_warships[node_temp_warship->value];
        printf("%s%c", "_______________________________", '\n');
        printf("Name: \t\t\t\t %s%c", temp_warship.name, '\n');
        printf("Shipyard: \t\t\t %s%c", temp_warship.shipyard, '\n');
        printf("Year of descent: \t\t %d%c", temp_warship.year_of_descent, '\n');
        printf("Number of crew members: \t %d%c", temp_warship.number_of_crewmates, '\n');
        printf("Condition: \t\t\t %s%c", temp_warship.condition, '\n');
        printf("Battles: %c", '\n');
        for(size_t j = 0; j<NUMBER_OF_BATTLES; ++j)
            printf("\t\t%s\n", temp_warship.battles[j]);
        printf("%s%c", "_______________________________", '\n');
        node_temp_warship = node_temp_warship->next;
    }
}

_Bool compare_two_warships(Warship first_warship, Warship second_warship) {
    if(strlen(first_warship.name) != 0 && strcmp(first_warship.name, second_warship.name) != 0) {
        return 0;
    }
    if(strlen(first_warship.shipyard) != 0 && strcmp(first_warship.shipyard, second_warship.shipyard) != 0) {
        return 0;
    }
    if(first_warship.year_of_descent != 0 && first_warship.year_of_descent != second_warship.year_of_descent) {
        return 0;
    }
    if(first_warship.number_of_crewmates != 0 && first_warship.number_of_crewmates != second_warship.number_of_crewmates) {
        return 0;
    }
    if(strlen(first_warship.condition) != 0 && strcmp(first_warship.condition, second_warship.condition) != 0) {
        return 0;
    }
    //Сравнение названий боёв.
    for(size_t i = 0; i<NUMBER_OF_BATTLES; ++i) {
        if(strlen(first_warship.battles[i]) != 0 && strcmp(first_warship.battles[i], second_warship.battles[i]) != 0) {
            return 0;
        }
    }
    return 1;
}

List search_warships(const Warship* warship_to_compare_with, const Warship* array_of_warships, size_t size_of_array) {

    List list_of_found_warships;
    list_of_found_warships.head = NULL;

    if(warship_to_compare_with == NULL || array_of_warships == NULL || size_of_array < 2) {
        return list_of_found_warships;
    }

    for(size_t i = 0; i<size_of_array; ++i) {
        push_front(&list_of_found_warships, i);
    }

    Node *node_temp_warship = list_of_found_warships.head;
    Node *next_temp_node = list_of_found_warships.head;

    while(node_temp_warship != NULL) {
        next_temp_node = node_temp_warship->next;
        if(compare_two_warships(*warship_to_compare_with, array_of_warships[node_temp_warship->value]) == 0) {
            delete_node(&list_of_found_warships, node_temp_warship);
        }
        node_temp_warship = next_temp_node;
    }

    return list_of_found_warships;
}