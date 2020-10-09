#include "Field.h"

Field *Field::field = nullptr;

Field *Field::GetInstance(int start_num, int end_num) {
    if (field == nullptr) {
        field = new Field(start_num, end_num);
    }
    return field;
}

Field::Field(Field &&other) noexcept: _cells(other._cells),
                                      _start_no(other._start_no), _end_no(other._end_no),
                                      availableSize(other.availableSize), sizeAll(other.sizeAll) {
    other._cells = nullptr;
}


void deepCopyField(Cell **f, Cell **s) {
    f = new Cell *[height + wallOffset];
    for (int i = 0; i < height + wallOffset; i++) {
        f[i] = new Cell[width + wallOffset];
        for (int j = 0; j < width + wallOffset; j++) {
            f[i][j] = s[i][j];
        }
    }
}


Field::Field(Field &other) : _start_no(other._start_no), _end_no(other._end_no), availableSize(other.availableSize),
                             sizeAll(other.sizeAll) {
    deepCopyField(_cells, other._cells);
}


Field &Field::operator=(Field &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    std::swap(_cells, other._cells);
    std::swap(_start_no, other._end_no);
    std::swap(_end_no, other._end_no);
    std::swap(availableSize, other.availableSize);
    return *this;
}


Field &Field::operator=(const Field &other) {
    if (this == &other) {
        return *this;
    }
    _start_no = other._start_no;
    _end_no = other._end_no;
    availableSize = other.availableSize;
    deepCopyField(_cells, other._cells);
    return *this;
}


void Field::createGraph() {
    int cnt = 1;
    // для каждой из клеток определить список смежности
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            _cells[i][j].num = cnt++;
            for (int l = 0; l < adjacencySize; l++) {
                _cells[i][j].adjacencyList[l][0] = i + dx[l];
                _cells[i][j].adjacencyList[l][1] = j + dy[l];
            }
        }
    }

    // Границы поля - должны быть недоступны для хода.
    for (int i = 0; i < width + wallOffset; i++) {
        _cells[0][i].num = cnt++;
        _cells[width + wallOffset - 1][i].num = cnt++;
        makeWall(0, i);
        makeWall(width + wallOffset - 1, i);
    }
    for (int j = 0; j < height + wallOffset; j++) {
        _cells[j][0].num = cnt++;
        _cells[j][height+wallOffset - 1].num = cnt++;
        makeWall(j, 0);
        makeWall(j, height + wallOffset - 1);
    }
}


void Field::initCoins(int *startCoords) {
    coins = std::vector<std::vector<Coin*>>(height+1, std::vector<Coin*>(width+1));
    for(auto it : *this) {
        if(it.is_available) {
            coins[it.x][it.y] = new Coin(it.x,it.y);
        }
    }
    coins[startCoords[0]][startCoords[1]]->isAlive = 0; // нет монетки на старте
}

Field::Field(int start_num, int end_num) : _start_no(start_num), _end_no(end_num) {
    _cells = new Cell *[height + wallOffset];
    for (int i = 0; i < height + wallOffset; i++) {
        _cells[i] = new Cell[width + wallOffset];
        for (int j = 0; j < width + wallOffset; j++) {
            _cells[i][j].x = i;
            _cells[i][j].y = j;
        }
    }
    createGraph();
}

int* Field::coordsByNum(int num) {
    int *coords = new int[2];
    coords[0] = (num - 1) / height + 1;
    coords[1] = (num - 1) % width + 1;
    return coords;
}


/**
 * Обход графа в глубину с подсчетом посещенных вершин
 * @param from - ячейка старта
 * @param visited - bool массив с номерами посещенных вершин
 * @return  количество вершин, доступных из from
 */
int Field::dfs(Cell from, bool *visited) {
    int visitedCount = 1;
    visited[from.num] = true;
//    for(int i = 1; i <= availableSize+1; i++)
    for (auto x : from.adjacencyList) {
        Cell to = _cells[x[0]][x[1]];
        if (to.is_available && !visited[to.num]) {
            visitedCount += dfs(to, visited);
        }
    }
    return visitedCount;
}

/**
 * Проверяет, связен ли граф (сохранен ли инвариант в текущий момент)
 */
bool Field::checkConnectedComponent() {
    bool visited[size()];
    for(int i = 1; i <= size(); i++) visited[i] = false;
    int *coords = coordsByNum(_start_no);
    int x = coords[0], y = coords[1];
    int df = dfs(_cells[x][y], visited);
    return df == availableSize;
}


void Field::makeWall(int num) {
    int *coords = coordsByNum(num);
    int x = coords[0], y = coords[1];
    makeWall(x, y);
}


void Field::makeWall(int x, int y) {
    if (_cells[x][y].is_available) {
        _cells[x][y].is_available = false;
        availableSize--;
    }
}

bool Field::isAvailable(int x, int y) {
    return _cells[x][y].is_available;
}

Field::~Field() {
    for (int i = 0; i < height + wallOffset; i++)
        delete _cells[i];
    delete _cells;
}


Field::iterator::iterator(Field &field, size_t index) : field(field), nIndex(index) {}

Cell Field::iterator::iterator::operator*() const {
    return field._cells[nIndex / (height + wallOffset)][nIndex % (width + wallOffset)];
}

Field::iterator &Field::iterator::operator++(int i) {
    return ++(*this);
}

Field::iterator &Field::iterator::operator++() {
    nIndex++;
    return *this;
}

size_t Field::size() const {
    return sizeAll;
}

Field::iterator Field::begin() {
    return Field::iterator(*this, 0);
}

Field::iterator Field::end() {
    return Field::iterator(*this, size());
}


bool Field::iterator::operator!=(const iterator &other) const {
    return nIndex != other.nIndex;
}