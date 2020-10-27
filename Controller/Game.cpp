//
// Created by yudjin on 10/5/20.
//

#include "Game.h"

#define RESET   "\033[0m"
#define EXIT     "\033[1m\033[31m"      /* Bold Red */
#define START   "\033[1m\033[32m"      /* Bold Green */
#define BORDER   "\033[1m\033[37m"      /* Bold Black */
#define PLAIN  "\033[1m\033[33m"      /* Bold Yellow */

using namespace std;

void dbgGraph(Field *f, int start, int end) {
    int cnt = 1;
    for (auto it : *f) {
        if (it.num == start)
            cout << START;
        else if (it.num == end)
            cout << EXIT;
        else if (it.is_available == 0) {
            cout << BORDER;
        } else cout << PLAIN;
        cout << it.is_available << RESET;
        if (cnt++ % (width + wallOffset) == 0) cout << "\n";
    }

    if (f->checkConnectedComponent()) {
        cout << START << "Граф связен - инвариант сохранен !\n";
    } else {
        cout << EXIT << "Инвариант нарушен !\n";
    }

}


void Game::init() {
    gui.create();
    // TODO(YudjinSud):
    // Logging system which will enable configure game start/end point
    // from file. Also this system should provide map-configuration.

    start = 1, end = 66;
    startCoords = f->coordsByNum(start);
    endCoords = f->coordsByNum(end);

    f = Field::GetInstance(start, end);
    player = new Player(startCoords[0], startCoords[1]);

    // Необходимо проверять, что это не вход и не выход
    f->makeWall(5);
    f->makeWall(15);
    f->makeWall(32);
    f->makeWall(76);
    f->makeWall(9);
    f->makeWall(34);

    ICreator *coinsFabric = new CoinCreator(); // Монетный двор (фабрика монет)
    f->initItems(startCoords, *coinsFabric);

    fileLogger = new FileLogger(player, LOG_FILE);
    consoleLogger = new ConsoleLogger(player);
   // fileLogger->unSubscribe();

    // consoleLogger = new ConsoleLogger(f->_cells[2][2].item);
    // fileLogger = new FileLogger(f->_cells[2][2].item);

    dbgGraph(f, start, end);

    while (gui.getWindow()->isOpen()) {
        tick();
        draw();
    }
}

void Game::checkCoinsStatus() {
    int x = player->x, y = player->y;
    // Прошел ли через монетку?
    Item *coin = f->_cells[x][y].item;
    if (coin->isAlive()) {
        *player += *(coin); // Взаимодействие игрока с элементом через перегруженный оператор
        coin->setAlive(false);
    }
    coin->Notify();
}

void Game::checkEndStatus() {
    //Подсчет количества оставшихся монет
    int cnt = 0;
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            Item *c = f->_cells[i][j].item;
            if (c && c->isAlive()) cnt++;
        }
    }
    bool isEndReached = endCoords[0] == player->x && endCoords[1] == player->y;
    if (player->life == 0 || cnt == 0 || isEndReached) {
        gui.stop();
    }
}

void Game::tick() {
    while (gui.getWindow()->pollEvent(events)) {
        if (events.type == sf::Event::Closed)
            gui.stop();
        if (events.type == sf::Event::KeyPressed) {
            processInput();
            checkCoinsStatus();
            checkEndStatus();
        }
    }
}

void Game::processInput() {
    switch (events.key.code) {
        case sf::Keyboard::Up:
            player->move(-1, 0,
                         f->isAvailable(player->x - 1, player->y));
            break;
        case sf::Keyboard::Left:
            player->move(0, -1,
                         f->isAvailable(player->x, player->y - 1));
            break;
        case sf::Keyboard::Right:
            player->move(0, 1,
                         f->isAvailable(player->x, player->y + 1));
            break;
        case sf::Keyboard::Down:
            player->move(1, 0,
                         f->isAvailable(player->x + 1, player->y));
            break;
        case sf::Keyboard::Escape:
            gui.stop();
    }

}


void Game::draw() {
    gui.clear();
    for (auto it : *f) {
        if (it.is_available == 0) {
            gui.drawWall(it);
        }
    }
    gui.drawPlayer(*player);
    gui.drawCoins(f, endCoords[0], endCoords[1]);
    gui.display();
}

Game::~Game() {
    delete consoleLogger;
    delete fileLogger;
}
