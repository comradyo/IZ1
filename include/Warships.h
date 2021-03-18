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

//Структура "Бои"
typedef struct {
    char name[SIZE_OF_NAME];
} Battle;

//Структура "Корабли"
typedef struct {
    int id_warship;                             //ID корабля
    char name[SIZE_OF_NAME];                    //Название
    char shipyard[SIZE_OF_NAME];                //Верфь-производитель
    char year_of_descent[SIZE_OF_NAME];         //Год спуска на воду
    char number_of_crew_members[SIZE_OF_NAME];  //Численность экипажа
    Battle battles[NUMBER_OF_BATTLES];          //Бои, в которых корабль принимал участие
    char condition[SIZE_OF_NAME];               //Состояние
} Warship;

//Прикладная процедура печати боёв, в котором участвовал корабль
void print_info_about_battles(int warship_id);

//Вывод списка всех кораблей
void print_list_of_warships(List *list_of_warships);

//Перечисляемый тип параметров, нужен для поиска корабля по параметрам
typedef enum {
    _name = 0,
    _shipyard = 1,
    _year_of_descent = 2,
    _number_of_crew_members = 3,
    _battles = 4,
    _condition = 5
} Parameter;

//Поиск корабля по параметру, параметры задаются через enum Parameter
void warship_search_by_parameter(List *list_of_warships, char parameter[SIZE_OF_NAME], Parameter type_of_parameter);

//Функция, возвращающая список найденных кораблей
List warship_search(char parameters[NUMBER_OF_PARAMETERS][SIZE_OF_NAME]);

//Считывание параметров
int read_parameters(char parameters_to_return[NUMBER_OF_PARAMETERS][SIZE_OF_NAME]);

#endif //IZ1_WARSHIPS_H
