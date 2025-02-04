# Контроллер

Возможный прототип обработчика

enum events {
    none,
    generateMaze,
    generateCave,
    loadMaze,
    LoadCave,
    saveMaze,
    saveCave
    ...
}

maze_t* eventProcessing(enum events event, FILE* pfile, int* height, int* width) {
    maze_t pmaze = NULL; //или maze_t pmaze = locateMaze(NULL);
    if (event = generateMaze ) {

    } 

    return pmaze; возврат NULL говорит об ошибке и соответственно обрабатывается в интерфейсе.
}

и далее конкретные функции работы с моделью (логикой) на основе событий возникающих в интерфейсе.

