/*!
  \file
  \author smart_n_smarter
  \version 1
  \date November 2024
  \brief Заголовочный файл содержит определения макросов, структур, функций и
  иных определений необходимых для реализации проекта.

  \details Файл содержит в себе определения макросов, структур, функций и иных
  определений необходимых для реализации проекта библиотеки генерации лабиринтов
  и пещер.
*/

#ifndef S21_MAZE_H
#define S21_MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*!
    \brief Максимальное значение измерения (ширина, высота).
    \details Макрос определяет максимальное значение размерности (ширина или
   высота) поля лабиринта.
*/
#define MAX_MAZE_MEASURE 50

/*!
    \brief Минимальное значение измерения (ширина, высота).
    \details Макрос определяет максимальное значение размерности (ширина или
   высота) поля лабиринта.
*/
#define MIN_MAZE_MEASURE 2

#define MAZE_RIGHT_BORDER 1
#define MAZE_BOTTOM_BORDER 2

/*!
  \brief Коды вовзврата состояния выполнения функций библиотеки.
*/
#define ERRCODE_ERR 1;
#define ERRCODE_OK 0;

/*!
  \brief Перечисление значения флага состояния хранения адреса локатора
*/
enum lset { nset, set };

/*!
  \brief Структура данных описания лабиринта.
  \details Cтруктура представляет собой контейнер для хранения лабиринта.
  grid — это двумерный массив целых чисел, представляющий саму сетку лабиринта.
  значения границ описываются битами: где первый бит отвечает за наличие правой
  границы, второй бит за наличие или отсутствие нижней границы. height и width
  содержат размеры лабиринта по вертикали и горизонтали соответственно.
*/
typedef struct maze {
  int** grid;  ///< Матрица хранения сетки лабиринта
  char height;  ///< Значение высоты лабиринта
  char width;   ///< Значенние ширина лабиринта
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
maze_t* createMaze();
void destroyMaze(maze_t* pmaze);
int** createGrid(const int height, const int width);
void destroyGrid(int** pmatrix, const int height, const int width);

/*!
  \defgroup Address_providers Функции поставщиков адресов
  \brief Функции предназначенные для предоставления адресов структур данных.
*/
maze_t* locateMazeStructure(maze_t* pmaze);

/*!
    \defgroup Data_management_routines Функции работы с данными структур
    \brief Функции предназначенные для чтения и изменения данных.
*/
int setMazeSize(maze_t* pmaze, const int newHeight, const int newWidth);
int getGridValue(maze_t* pmaze, const int hindex, const int windex);
void setGridValue(maze_t* pmaze, const int hindex, const int windex,
                  const int value);
void clearMaze(maze_t* pmaze);
int fillMaze(maze_t* pmaze);
int freadMaze(FILE* pfile, maze_t* pmaze);
int fwriteMaze(FILE* pfile, maze_t* pmaze);

/*!
    \defgroup Maze_generation_routines Функции заполнения лабиринта
    \brief Функции предназначенные для генерации лабиринта.
*/
void generateMazeEller(maze_t* pmaze);

#endif