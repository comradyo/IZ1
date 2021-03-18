#ifndef IZ1_WARSHIPS_H
#define IZ1_WARSHIPS_H

#include "List.h"

//Число параметров у корабля
#define NUMBER_OF_PARAMETERS 6
//Максимальный размер введённого параметра
#define SIZE_OF_NAME 20
//Число кораблей в массиве кораблей
#define NUMBER_OF_WARSHIPS 10
//Число боёв у корабля
#define NUMBER_OF_BATTLES 3

//Структура "Корабли"
typedef struct {
    int id_warship;                                     //ID корабля
    char name[SIZE_OF_NAME];                            //Название
    char shipyard[SIZE_OF_NAME];                        //Верфь-производитель
    int year_of_descent;                                //Год спуска на воду
    int number_of_crewmates;                            //Численность экипажа
    char condition[SIZE_OF_NAME];                       //Состояние
    char battles[NUMBER_OF_BATTLES][SIZE_OF_NAME];      //Бои, в которых корабль принимал участие
} Warship;

//Ввод массива кораблей.
_Bool fill_array_of_warships(Warship* array_of_warships, size_t size_of_array);

//Инициализация корабля.
//Если to_search == 1, то необязательно вводить все поля.
_Bool initialize_warship(Warship* warship_to_initialize, _Bool to_search);

_Bool compare_two_warships(Warship first_ws, Warship second_ws);

//Поиск кораблей, параметры которых совпадают с параметрами переданного корабля.
//search_warships(warship_for_searching, warships_arr, size_of_warships_array);
List search_warships(const Warship* warship_to_compare_with, const Warship* array_of_warships, size_t size_of_array);

//Вывод кораблей из списка
void print_list_of_warships(List *list_of_warships, const Warship* array_of_warships, size_t size_of_array);

//Функция, возвращающая список найденных кораблей
List warship_search(char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME]);

#endif //IZ1_WARSHIPS_H
