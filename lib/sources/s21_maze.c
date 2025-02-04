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

  \details Функция предназначена для создания основной структуры maze_t.
  В ходе выплолнения создается пустая структура хранения либиринта.
*/
maze_t* createMaze() {
  maze_t* pmaze = NULL;

  if ((pmaze = (maze_t*)malloc(sizeof(maze_t))) != NULL) {
    pmaze->height = 0;
    pmaze->width = 0;
  }

  return pmaze;
}

/*!
  \ingroup Data_Structure_management Функции управления структурами данных
  \brief Функция уничтожения структуры maze_t.
  \param [in] pmaze Указатель на адрес структуры maze_t.

  \details Функция выполняет освобождение области памяти выделенной структуре
  maze_t. Выполнение операции осуществляется только при условии, что в качестве
  входного параметра передан указатель на область памяти.
*/
void destroyMaze(maze_t* pmaze) {
  if (pmaze) {
    if (pmaze->grid) {
      destroyGrid(pmaze->grid, pmaze->height, pmaze->width)
    }
    free(pmaze);
  }
}

/*!
  \ingroup Data_Structure_management Функции управления структурами данных
  \brief Функция создания матрицы сетки лабиринта.
  \param [in] height высота матрицы лабиринта.
  \param [in] width ширина матрицы лабиринта.
  \return указатель на матрицу хранениия сетки лабиринта.

  \details Функция предназначена для создания матрицы хранения лабиринта.
  В ходе выпололнения создается пустая структура хранения либиринта. Заполнение
  матрицы нулевыми значениями производится при ее создании.
*/
int** createGrid(const int height, const int width) {
  int** grid = NULL;

  if (height < MIN_MAZE_MEASURE || height > MAX_MAZE_MEASURE ||
      width < MIN_MAZE_MEASURE || width > MAX_MAZE_MEASURE) {
    return grid;
  }

  if ((grid = (int**)malloc(sizeof(int*) * height)) != NULL) {
    int* lines = NULL;
    if ((lines = (int*)calloc(height * width, sizeof(int))) != NULL) {
      for (int i = 0; i < height; i++) {
        *(grid + i) = lines + (i * width);
      }
    } else {
      free(grid);
      grid = NULL;
    }
  }

  return grid;
}

/*!
  \ingroup Data_Structure_management Функции управления структурами данных
  \brief Функция уничтожения матрицы сетки лабиринта.
  \param [in, out] pmatrix указатель на матрицу хранения лабиринта.
  \param [in] height высота матрицы лабиринта.
  \param [in] width ширина матрицы лабиринта.

  \details Функция предназначена для уничтожения матрицы хранения лабиринта.
  Функция предназначена для освобождания памяти выделенной матрице хранения
  лабиринта.
*/
void destroyGrid(int** pmatrix, const int height, const int width) {
  if (pmatrix) {
    if (*pmatrix) free(*pmatrix);
    free(pmatrix);
  }
}

/*!
  \ingroup Address_providers Функции поставщиков адресов
  \brief Функция локатор выделенных ресурсов структуре maze_t
  \param [in] pmaze Указатель на адрес структуры maze_t
  \return Указатель на область памяти, хранящую структру данных maze_t

  \details Функции устанавливают и возвращают указатели на структурe maze_t.
  Если адрес локатору ранее не передавался, то осуществляется сохранение
  адреса в структуре локатора. Если передан NULL и ранее локатору передавался
  адрес игровой структуры то функция возвращает значение ранее сохранненого
  адреса. При повторной передаче адреса функции локатору, состояние локатора
  изменяется на 'не задан' (nset), адрес приводится в состояние NULL и функция
  возвращает NULL.
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
  \ingroup Data_management_routines Функции работы с данными структур
  \brief Функция предназначенная для получения значения хранимого в ячейке
  матрицы. \param [in] pmaze Указатель на адрес структуры maze_t. \param [in]
  hindex Индекс ячейки в матрице по высоте. \param [in] windex Индекс ячейки в
  матрице по ширине \return Целочисленное значение хранимое в ячейке.

  \details Функции предназначена для получения значения из ячейки матрцы по
  индексам
*/
int getGridValue(maze_t* pmaze, const int hindex, const int windex) {
  int retval = -1;

  if (pmaze) {
    if (pmaze->grid) {
      if (hindex < pmaze->height && hindex >= 0 && windex < pmaze->width &&
          windex >= 0)
        retval = pmaze->grid[hindex][windex];
    }
  }

  return retval;
}

/*!
  \ingroup Data_management_routines Функции работы с данными структур
  \brief Функция предназначенная для получения значения хранимого в ячейке
  матрицы.
  \param [in] pmaze Указатель на адрес структуры maze_t.
  \param [in] hindex Индекс ячейки в матрице по высоте.
  \param [in] windex Индекс ячейки в матрице по ширине.
  \param [in] value Значение записываемое в ячейку.

  \details Функции предназначена для задания значения в ячейке матрцы по
  индексам.
*/
void setGridValue(maze_t* pmaze, const int hindex, const int windex,
                  const int value) {
  if (pmaze) {
    if (pmaze->grid) {
      if (hindex < pmaze->height && hindex >= 0 && windex < pmaze->width &&
          windex >= 0)
        pmaze->grid[hindex][windex] = value;
    }
  }
}

/*!
  \ingroup Data_management_routines Функции работы с данными структур
  \brief Функция очистки матрицы значений.
  \param [in] pmaze Указатель на адрес структуры maze_t.

  \details Функции приводит структуру maze_t к пустому состоянию. В ходе
  выполнения функция осуществляет удаление матрицы значений и приводит значение
  высоты и ширины лабиринта к значению 0.
*/
void clearMaze(maze_t* pmaze) {
  if (pmaze) {
    if (pmaze->grid) {
      destroyGrid(pmaze->grid, pmaze->height, pmaze->width);
      pmaze->grid = NULL;
      pmaze->height = 0;
      pmaze->width = 0;
    }
  }
}

/*!
  \ingroup Data_management_routines Функции работы с данными структур
  \brief Функция инициализации размеров сетки лабиринта.
  \param [in, out] pmaze Указатель на адрес структуры maze_t.
  \param [in] newHeight Новое значение высоты сетки массива
  \param [in] newWidth Новое значение ширины сетки массива
  \return Код ошибки ERRCODE_OK (0) или ERRCODE_ERR(1).

  \details Функции задает новую размерность сетки лаибиринта по высоте и ширине.
  Значения высоты и ширины не могут буть меньше значения MIN_MAZE_MEASURE и
  больше MAX_MAZE_MEASURE. При заднии размеров не входящих в диапазон допустимых
  значений выполнение функции немедленно прекращается. При наличии указателя на
  ранее созданную сетку лабиринта, область памяти занятая лабиринтом очищается.
  \warning Выполнение функции не приводит к созданию сетки лабиринта.
*/
int setMazeSize(maze_t* pmaze, const int newHeight, const int newWidth) {
  int errval = ERRCODE_ERR;

  if (pmaze) {
    if (newHeight >= MIN_MAZE_MEASURE && newHeight <= MAX_MAZE_MEASURE &&
        newWidth >= MIN_MAZE_MEASURE && newWidth <= MAX_MAZE_MEASURE) {
      clearMaze(pmaze);
      pmaze->height = newHeight;
      pmaze->width = newWidth;
      errval = ERRCODE_OK
    }
  }

  return errval;
}

/*!
  \ingroup Data_management_routines Функции работы с данными структур
  \brief Функция заполнения матрицы лабиринта случай0ными значениями.
  \param [in] pfile Указатель на дескриптор файла.
  \param [in] pmaze Указатель на структуру maze_t.
  \return Возвращает 1 при возникновении исключения или 0.

  \details Функции предназначена заполнения матрицы лабиринта из файла.
*/
int freadMaze(FILE* pfile, maze_t* pmaze) {
  int errval = ERRCODE_ERR;

  if (!pfile) return errval;

  // if (pmaze) destroyMaze(pmaze);

  //   int mheight, mwidth;
  //   fscanf(pfile, "%d %d", &mheight, &mwidth);

  //   if (createMaze(mheight, mwidth)) {
  //     for (int i = 0; i < mheight; i++) {
  //       for (int j = 0; j < mwidth; j++) {
  //         int val;
  //         fscanf(pfile, "%d", &val);
  //         setMatrixValue(pmaze, i, j, val);
  //       }
  //     }
  //     for (int i = 0; i < mheight; i++) {
  //       for (int j = 0; j < mwidth; j++) {
  //         int val;
  //         fscanf(pfile, "%d", &val);
  //         val = (val << 1) + getMatrixValue(pmaze, i, j);
  //         setMatrixValue(pmaze, i, j, val);
  //       }
  //     }
  //     errval = ERRCODE_OK;
  //   }

  return errval;
}

/*!
  \ingroup Data_management_routines Функции работы с данными структур
  \brief Функция заполнения матрицы лабиринта случайными значениями.
  \param [in] pfile Указатель на дескриптор файла.
  \param [in] pmaze Указатель на адрес структуры maze_t.
  \return Возвращает 1 при возникновении исключения или 0.

  \details Функции предназначена для сохранения матрицы лабиринта в файл.
*/
int fwriteMaze(FILE* pfile, maze_t* pmaze) {
  int errval = ERRCODE_ERR;

  //   if (!pfile || !pmaze) return errval;

  //   fprintf(pfile, "%d %d\n", pmaze->height, pmaze->width);
  //   for (int i = 0; i < pmaze->height; i++) {
  //     for (int j = 0; j < pmaze->width; j++) {
  //       int val = getMatrixValue(pmaze, i, j);
  //       val = val << 31 >> 31;
  //       fprintf(pfile, "%d", val);
  //       if (i != pmaze->height - 1) fprintf(pfile, " ");
  //     }
  //     fprintf(pfile, "\n");
  //   }
  //   for (int i = 0; i < pmaze->height; i++) {
  //     for (int j = 0; j < pmaze->width; j++) {
  //       int val = getMatrixValue(pmaze, i, j);
  //       val = val << 30 >> 31;
  //       fprintf(pfile, "%d", val);
  //       if (i != pmaze->height - 1) fprintf(pfile, " ");
  //     }
  //     fprintf(pfile, "\n");
  //   }

  return errval;
}

/*!
  \ingroup Maze_generation_routines Функции заполнения лабиринта
  \brief Функция генерации лабиринта на основе алгоритма Эллера (Maze
  Generation: Eller's Algorithm). \param [in, out] pmaze Указатель на адрес
  структуры maze_t.

  \details Функции предназначена для генерации произвольного лабиринта с
  использование алгоритма Эллера.
*/
int generateMazeEller(maze_t* pmaze) {
  int errval = ERRCODE_ERR;
  // Проверка условий выполнения (выход если не условия не соблюдены):
  // наличие действительного указателя
  if (!pmaze) return errval;
  // допустимость размеров лабиринта
  if (pmaze->height < MIN_MAZE_MEASURE || pmaze->height > MAX_MAZE_MEASURE ||
      pmaze->width < MIN_MAZE_MEASURE || pmaze->width > MAX_MAZE_MEASURE)
    return errval;

  // Проверяем наличие указателя на матрицу. Если есть, то убиваем.
  if (pmaze->grid) {
    size_t matrix_height = sizeof(pmaze->grid / sizeof(int*));
    size_t matrix_width = sizeof(*(pmaze->grid) / sizeof(int)) / matrix_height;
    destroyGrid(pmaze->grid, (int)matrix_height, (int)matrix_width);
  }
  // Создаем новую чистую матрицу.
  if ((pmaze->grid = createGrid(pmaze->height, pmaze->width)) == NULL)
    return errval;  // Если возникла ошибка при выделении памяти для сетки -
                    // выходим.

  //заполняем массив всеми границами
  for (int i = 0; i < pmaze->height * pmaze->width; i++) {
    *(*(pmaze->grid) + i) = MAZE_BOTTOM_BORDER + MAZE_RIGHT_BORDER;
  }

  return errval;
}
