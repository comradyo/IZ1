#include <stdlib.h>
#include "../include/Warships.h"
#include "stdio.h"
#include "string.h"

//Массив названий параметров, нужен для процедуры вывода параметров корабля.
const char *names_of_parameters[NUMBER_OF_PARAMETERS] = {
        "name of warship", "name of shipyard", "year of descent", "number of crew members", "name of the battle",
        "condition"
};

//Массив кораблей.
const Warship warships[NUMBER_OF_WARSHIPS] = {
        0, "Nikolay II", "Murmansk", "2005", "50", {"War for Belarus", "War for Japan", "War for Uganda"},
        "Decommissioned",
        1, "Comrade Xi", "Bohay", "1990", "13", {"War for China", "War for Afghanistan", "War for USSR"},
        "On combat duty",
        2, "Donald Trump", "Bayliner", "2018", "50", {"War for USSR", "War for Russia", "War for China"},
        "On combat duty",
        3, "Aleksandr III", "Severodvinsk", "1990", "26", {"War for USSR", "War for Russia", "War for USA"},
        "Decommissioned",
        4, "Ivan Grozny", "Severodvinsk", "1950", "13", {"War for China", "War for Japan", "War for USSR"},
        "On combat duty",
        5, "Yastreb", "Murmansk", "2005", "50", {"War for Belarus", "War for Ukraine", "War for Russia"},
        "On combat duty",
        6, "Tuang", "Peking", "2005", "48", {"War for Earth", "War for England", "War for China"},
        "On combat duty",
        7, "Chan", "Bohay", "2018", "13", {"War for Belarus", "War for Russia", "War for Uganda"},
        "Decommissioned",
        8, "Powerbank", "New-York", "1990", "48", {"War for Russia", "War for England", "War for USA"},
        "On combat duty",
        9, "Molnia", "Severodvinsk", "2005", "26", {"War for Earth", "War for England", "War for China"},
        "Decommissioned",
};

void print_info_about_battles(int warship_id) {
    for (size_t i = 0; i < NUMBER_OF_BATTLES; ++i) {
        printf("\t\t%s\n", warships[warship_id].battles[i].name);
    }
}

void print_list_of_warships(List *list_of_warships) {
    Node *node_temp_warship = list_of_warships->head;
    if(node_temp_warship == NULL) {
        printf("No warships found\n");
        return;
    }
    while (node_temp_warship != NULL) {
        Warship temp_warship = warships[node_temp_warship->value];
        printf("%s%c", "_______________________________", '\n');
        printf("Name: \t\t\t\t %s%c", temp_warship.name, '\n');
        printf("Shipyard: \t\t\t %s%c", temp_warship.shipyard, '\n');
        printf("Year of descent: \t\t %s%c", temp_warship.year_of_descent, '\n');
        printf("Number of crew members: \t %s%c", temp_warship.number_of_crew_members, '\n');
        printf("Condition: \t\t\t %s%c", temp_warship.condition, '\n');
        printf("Battles: %c", '\n');
        print_info_about_battles(temp_warship.id_warship);
        printf("%s%c", "_______________________________", '\n');
        node_temp_warship = node_temp_warship->next;
    }
}

void warship_search_by_parameter(List *list_of_warships, char parameter[SIZE_OF_NAME], Parameter type_of_parameter) {
    if (list_of_warships == NULL) return;
    if (list_of_warships->head == NULL) return;
    Node *temp_warship = list_of_warships->head;
    //next_temp_warship нужен, чтобы не потерять значение, следующее за temp_warship, который, возможно, будет удалён из списка.
    Node *next_temp_warship = list_of_warships->head;
    //Смотрим все корабли в списке и проверяем, совпадает ли переданный параметр определённого типа с аналогичным параметром самого корабля.
    while (temp_warship != NULL) {
        next_temp_warship = temp_warship->next;
        switch (type_of_parameter) {
            case _name:
                if (strcmp(warships[temp_warship->value].name, parameter) != 0)
                    delete_node(list_of_warships, temp_warship);
                break;
            case _shipyard:
                if (strcmp(warships[temp_warship->value].shipyard, parameter) != 0)
                    delete_node(list_of_warships, temp_warship);
                break;
            case _year_of_descent:
                if (strcmp(warships[temp_warship->value].year_of_descent, parameter) != 0)
                    delete_node(list_of_warships, temp_warship);
                break;
            case _number_of_crew_members:
                if (strcmp(warships[temp_warship->value].number_of_crew_members, parameter) != 0)
                    delete_node(list_of_warships, temp_warship);
                break;
            case _battles: {
                _Bool warship_was_in_battle = 0;
                //Поиск по всем сражениям, в которых принимал участие корабль
                for (int i = 0; i < NUMBER_OF_BATTLES; ++i) {
                    if (strcmp(warships[temp_warship->value].battles[i].name, parameter) == 0) {
                        warship_was_in_battle = 1;
                        i = NUMBER_OF_BATTLES;
                    }
                }
                if (warship_was_in_battle == 0) {
                    delete_node(list_of_warships, temp_warship);
                }
            }
                break;
            case _condition:
                if (strcmp(warships[temp_warship->value].condition, parameter) != 0)
                    delete_node(list_of_warships, temp_warship);
                break;
        }
        temp_warship = next_temp_warship;
    }
    free(temp_warship);
    temp_warship = NULL;
    free(next_temp_warship);
    next_temp_warship = NULL;
}

List warship_search(char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME]) {
    //Тип параметра, по которому будет производиться поиск.
    Parameter type_of_param = _name;
    List list_of_found_warships;
    list_of_found_warships.head = NULL;
    for (size_t i = 0; i < NUMBER_OF_WARSHIPS; ++i) {
        push_front(&list_of_found_warships, i);
    }

    for (size_t i = 0; i < NUMBER_OF_PARAMETERS; ++i) {
        if (strlen(parameters[i]) != 0) {
            warship_search_by_parameter(&list_of_found_warships, parameters[i], type_of_param);
        }
        type_of_param++;
    }

    return list_of_found_warships;
}

int read_parameters(char parameters_to_return[NUMBER_OF_PARAMETERS][SIZE_OF_NAME]) {
    Parameter param = _name;
    for (size_t i = 0; i < NUMBER_OF_PARAMETERS; ++i) {
        if (strlen(parameters_to_return[i]) == 0) {
            printf("Enter the %s%s", names_of_parameters[i], ":\t");
            if(fgets(parameters_to_return[i], SIZE_OF_NAME, stdin) == NULL) {
                return -1;
            }
            parameters_to_return[i][strcspn(parameters_to_return[i], "\n")] = 0;
        }
        //Проверка, являются ли числами те числовые параметры, которые ввел пользователь.
        if (param == _number_of_crew_members || param == _year_of_descent) {
            if (atoi(parameters_to_return[i]) == 0 && strlen(parameters_to_return[i]) != 0) {
                return -1;
            }
        }
        param++;
    }
    return 1;
}