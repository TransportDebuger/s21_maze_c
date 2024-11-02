/*!
  \file
  \author smart_n_smarter
  \version 1
  \date November 2024
  \brief Файл содержит реализации функций используемых в проекте. 

  \details Файл содержит реализации функций используемых в проекте.
*/

#include "s21_maze.h"

/*!
  \ingroup Data_Structure_management Функции управления структурами данных
  \brief Функция создания структуры maze_t.
  \return Целочисленное значение кода ошибки.

  Функция предназначена для создания основной структуры maze_t.
  В ходе выплолнения создается структура хранения либиринта. Указатель на адрес созданной структуры передается локатору ресурсов.
*/
int createMaze(int height, int width) {
    int errval = ERRCODE_ERR;

    if (height < MAX_MAZE_MEASURE && height > 0 && 
        width < MAX_MAZE_MEASURE && width > 0 && 
        locateMazeStructure(NULL) == NULL) 
        errval = ERRCODE_OK;
    
    if (!errval) {
        maze_t* pmaze = (maze_t *)malloc(sizeof(maze_t));
        if (pmaze) {
            pmaze->height = height;
            pmaze->width = width;
            pmaze->border_matrix = createMtarix(height, width);
            locateMazeStructure(pmaze);
        }
    }

    return errval;
}

/*!
  \ingroup Data_Structure_management Функции управления структурами данных
  \brief Функция уничтожения структуры maze_t.
  \param [in] pmaze Указатель на адрес структуры maze_t.

  \details Функция выполняет освобождение области памяти выделенной структуре maze_t. Выполнение операции осуществляется только при условии, что в качестве входного параметра передан указатель на область памяти.
*/
void destroyMaze(maze_t* pmaze) {
    if (pmaze) {
        destroyMatrix(pmaze->border_matrix);
        //функция уничтожения матрицы
        free(pmaze);
        locateMazeStructure(pmaze);
        pmaze = NULL;
    }
}

/*!
  \ingroup Data_Structure_management Функции управления структурами данных
  \brief Функция уничтожения матрицы описателей границ.
  \param [in] height Значение количества ячеек матрицы по высоте.
  \param [in] width Значение количества ячеек матрицы по ширине.
  \return Указатель на область памяти хранящей матрицу.

  \details Функция выполняет создание матрицы значений границ ячеек в лабиринте. Значения ячеек принудительно приведены к значению 0;
*/
int** createMatrix(const int height, const int width) {
    int** pmatrix = (int**)malloc(height * sizeof(int*));
    int* values = (int*)calloc(height * width, sizeof(int));
    for (int i = 0; i < height; i++) {
      pmatrix[i] = values + i * width;   
    }

    return pmatrix;
}

/*!
  \ingroup Data_Structure_management Функции управления структурами данных
  \brief Функция уничтожения матрицы описателей границ.
  \param [in] pmaze Указатель на область памяти, хранящий матрицу границ ячеек лабиринта.

  \details Функция выполняет уничтожение матрицы значений границ ячеек в лабиринте.
*/
void destroyMatrix(int** pmatrix) {
    if (pmatrix) {
        free(*pmatrix);
        free(pmatrix);
        pmatrix = NULL;
    }
}

/*!
  \ingroup Address_providers Функции поставщиков адресов.
  \brief Функция локатор выделенных ресурсов структуре maze_t.
  \param [in] pmaze Указатель на адрес структуры maze_t.
  \return Указатель на область памяти, хранящую структру данных maze_t

  \details Функции устанавливают и возвращают указатели на структурe maze_t. 
  Если адрес локатору ранее не передавался, то осуществляется сохранение
  адреса в структуре локатора. Если передан NULL и ранее локатору передавался
  адрес игровой структуры то функция возвращает значение ранее сохранненого
  адреса. При повторной передаче адреса функции локатору, состояние локатора
  изменяется на 'не задан' (nset), адрес приводится в состояние NULL и функция возвращает NULL.
*/
maze_t* locateMazeStructure(maze_t* pmaze) {
    static maze_locator_t m_locate = {0};

    if (pmaze == m_locate.addr && m_locate.setval) {
        m_locate.addr = NULL;
        m_locate.setval = nset;
    } else if (pmaze) {
        m_locate.addr = pmaze;
        m_locate.setval = set;
    }

    return m_locate.addr;
}

/*!
  \ingroup Data_management_routines Функции работы с данными структур.
  \brief Функция предназначенная для получения значения хранимого в ячейке матрицы.
  \param [in] pmaze Указатель на адрес структуры maze_t.
  \param [in] hindex Индекс ячейки в матрице по высоте.
  \param [in] windex Индекс ячейки в матрице по ширине
  \return Целочисленное значение хранимое в ячейке.

  \details Функции предназначена для получения значения из ячейки матрцы по индексам
*/
int getMatrixValue(maze_t* pmaze, const int hindex, const int windex) {
    int retval = -1;

    if (pmaze) {
        if (hindex < pmaze->height && hindex >= 0 && windex < pmaze->width && windex >= 0) 
            retval = pmaze->border_matrix[hindex][windex];
    }

    return retval;
}

/*!
  \ingroup Data_management_routines Функции работы с данными структур.
  \brief Функция предназначенная для получения значения хранимого в ячейке матрицы.
  \param [in] pmaze Указатель на адрес структуры maze_t.
  \param [in] hindex Индекс ячейки в матрице по высоте.
  \param [in] windex Индекс ячейки в матрице по ширине.
  \param [in] value Значение записываемое в ячейку.

  \details Функции предназначена для задания значения в ячейке матрцы по индексам.
*/
void setMatrixValue(maze_t* pmaze, const int hindex, const int windex, const int value) {
    if (pmaze) {
        if (hindex < pmaze->height && hindex >= 0 && windex < pmaze->width && windex >= 0)
            pmaze->border_matrix[hindex][windex] = value;
    }
}

/*!
  \ingroup Data_management_routines Функции работы с данными структур.
  \brief Функция очистки матрицы значений.
  \param [in] pmaze Указатель на адрес структуры maze_t.

  \details Функции предназначена очистки значений матрицы.
*/
void clearMatrix(maze_t* pmaze) {
    if (pmaze) {
        for (int i = 0; i < pmaze->height; i++) {
            for (int j = 0; j < pmaze->width; j++) {
                setMatrixValue(pmaze, i, j, 0);
            }
        }
    }
}