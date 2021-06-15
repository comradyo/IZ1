#include <stdlib.h>
#include <stdio.h>
#include "../include/Warships.h"

/*
 * Создать структуру для хранения информации о военных кораблях:
 *      названии корабля при постройке,
 *      названии верфи-производителя,
 *      годе спуска на воду,
 *      история участия в военных кампаниях,
 *      численность экипажа,
 *      состояниие (в эксплуатации, списан и т.д.).
 * Составить программу вывода информации обо всех кораблях, соответствующих заданным пользователем критериям.
 *
 */


int main() {

    //Размер массива структур.
    size_t size_of_warships_array = 0;

    //Ввод размера массива структур
    printf("Enter the size of the array: ");
    if(scanf("%zu", &size_of_warships_array) == 0) {
        printf("Incorrect input of the size of warships array");
        return 0;
    }
    getchar();

    if(size_of_warships_array >= 2) {
        //Массив структур "Warship".
        Warship* warships_arr = (Warship*)calloc(sizeof(Warship), size_of_warships_array);
        if(warships_arr == NULL) {
            free(warships_arr);
            return 0;
        }
        
        //Заполнение массива структур
        if(fill_array_of_warships(warships_arr, size_of_warships_array) == 0) {
            printf("Incorrect initialization of the array of warships!\n");
            free(warships_arr);
            warships_arr = NULL;
            return 0;
        }

        //Корабль, хранящий введённые пользователем параметры кораблей
        Warship* warship_for_searching = (Warship*)malloc(sizeof(Warship));
        if(warship_for_searching == NULL) {
            free(warship_for_searching);
            return 0;
        }
        //Инициализация этого корабля
        printf("\n======================================\n");
        printf("Initialization of the parameters of searched warships\n");
        printf("======================================\n");
        if(initialize_warship(warship_for_searching, 1) == 0) {
            printf("Incorrect initialization of the warship for searching!\n");
            free(warship_for_searching);
            return 0;
        }

        if(warship_for_searching != NULL) {
            List list_of_found_warships;
            list_of_found_warships.head = NULL;
            list_of_found_warships = search_warships(warship_for_searching, warships_arr, size_of_warships_array);
            print_list_of_warships(&list_of_found_warships, warships_arr, size_of_warships_array);
            clear_list(&list_of_found_warships);
        }

        free(warship_for_searching);
        warship_for_searching = NULL;
        free(warships_arr);
        warships_arr = NULL;
    } else {
        printf("The size of array can't be less than 2!\n");
        return 0;
    }

    return 0;
    
}