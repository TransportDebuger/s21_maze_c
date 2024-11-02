
/*!
  \file
  \author smart_n_smarter
  \version 1
  \date November 2024
  \brief Заголовочный файл содержит определения макросов, структур, функций и
  иных определений необходимых для реализации проекта.

  \details Файл содержит в себе определения макросов, структур, функций и иных
  определений влияющих на реализацию проекта.
*/

#ifndef S21_MAZE_H
#define S21_MAZE_H

#include <stdio.h>
#include <stdlib.h>

/*!
    \brief Максимальное значение измерения (ширина, высота).
    \details Макрос определяет максимальное значение размерности (ширина или
   высота) поля лабиринта.
*/
#define MAX_MAZE_MEASURE 50

#define ERRCODE_ERR 0;
#define ERRCODE_OK 1;

/*!
  \brief Перечисление значения флага состояния хранения адреса локатора
*/
enum lset { nset, set };

/*!
  \brief Структура данных описания лабиринта.
  \details Структура предназначена для хранения указателей на матрицы описания
  границ лабиринта и его размерности.
*/
typedef struct maze {
  int** border_matrix;  ///< Указатель на матрицу хранения данных о правых
                        ///< границах ячеек лабиринта
  char height;          ///< Значение высоты лабиринта
  char width;           ///< Значенние ширина лабиринта
} maze_t;

/*!
  \brief Структура хранения локатора адреса структуры maze_t.
*/
typedef struct maze_locator {
  maze_t* addr;  ///< Указатель на структуру maze_t
  enum lset setval;  ///< Признак наличия заданного адреса.
} maze_locator_t;

/*!
  \defgroup Data_Structure_management Функции управления структурами данных
  \brief Функции предназначены для создания и уничтожения структур данных
*/
int createMaze(int height, int width);
void destroyMaze(maze_t* pmaze);
int** createMatrix(const int height, const int width);
void destroyMatrix(int** pmatrix);

/*!
  \defgroup Address_providers Функции поставщиков адресов
  \brief Функции предназначенные для предоставления адресов структур данных.
*/
maze_t* locateMazeStructure(maze_t* pmaze);

/*!
    \defgroup Data_management_routines Функции работы с данными структур
    \brief Функции предназначенные для чтения и изменения данных.
*/
int getMatrixValue(maze_t* pmaze, const int hindex, const int windex);
void setMatrixValue(maze_t* pmaze, const int hindex, const int windex,
                    const int value);
void clearMatrix(maze_t* pmaze);

// /*!
//     \defgroup Data_files_routines Функции работы с файлами
//     \brief Функции предназначенные для чтения и записи данных в файл.
// */
// int readMazeData(FILE* fname, maze_t* pmaze);
// int saveMazeData(FILE* fname, maze_t* pmaze);

#endif