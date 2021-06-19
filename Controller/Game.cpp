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
    int restore;
    cout << "Новая игра или из файла(0/1)?\n";
    cin >> restore;
    f = Field::GetInstance(start_no, end_no);
    fieldCaretaker = new FieldCaretaker(f);
    startCoords = f->coordsByNum(start_no);
    endCoords = f->coordsByNum(end_no);

    player = new Player({startCoords[0], startCoords[1]});
    f->player = player;
    if(restore) {
        fieldCaretaker->initFromFile();
    }
    else {
        // Необходимо проверять, что это не вход и не выход
        f->makeWall(5);
        f->makeWall(15);
        f->makeWall(32);
        f->makeWall(76);
        f->makeWall(9);
        f->makeWall(34);
        ICreator *coinsFabric = new CoinCreator(); // Монетный двор (фабрика монет)
        f->initItems(startCoords, *coinsFabric);
    }
    gui.create();


  //  fileLogger = new FileLogger(player, LOG_FILE);
    consoleLogger = new ConsoleLogger(player);
   // fileLogger->unSubscribe();
    // consoleLogger = new ConsoleLogger(f->_cells[2][2].item);
    // fileLogger = new FileLogger(f->_cells[2][2].item);

    dbgGraph(f, start_no, end_no);

    fieldCaretaker->backUp();
    fieldCaretaker->history();

    Enemy<IEnemyState> *akabei = new Enemy<IEnemyState>(player, {5, 5});
    akabei->transitionState(new Scared());
    akabei->transitionState(new Akabei());
    akabei->scare();
    enemies.push_back(akabei);

    while (gui.getWindow()->isOpen()) {
        tick();
        draw();
    }
}

void Game::checkCoinsStatus() {
    int x = player->position.x, y = player->position.y;
    // Прошел ли через монетку?
    Item *coin = f->_cells[x][y].item;
    if (coin->isAlive()) {
        *player += *(coin); // Взаимодействие игрока с элементом через перегруженный оператор
        coin->setAlive(false);
    }
    coin->Notify();
}

bool Game::collisionWithEnemies() {
    for(auto x : enemies) {
        if(x->position == player->position) {
            return true;
        }
    }
    return false;
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
    int x = player->position.x, y = player->position.y;
    bool isEndReached = endCoords[0] == x && endCoords[1] == y;
    if (player->life == 0 || cnt == 0 || isEndReached) {
        draw();
        gui.stop();
        fieldCaretaker->backUp();
    }
    else if(collisionWithEnemies()) {
        fieldCaretaker->undo();
        enemies.back()->position = {5, 5};
        player->life--;
        fieldCaretaker->backUp();
    }
}

void Game::tick() {
    while (gui.getWindow()->pollEvent(events)) {
        if (events.type == sf::Event::Closed)
            gui.stop();
        if (events.type == sf::Event::KeyPressed) {
            processInput();
            for(auto x : enemies) {
                x->update();
            }
            checkCoinsStatus();
            checkEndStatus();
        }
    }
}

void Game::processInput() {
    int x = player->position.x, y = player->position.y;
    switch (events.key.code) {
        case sf::Keyboard::Up:
            player->move({-1, 0},
                         f->isAvailable(x - 1, y));
            break;
        case sf::Keyboard::Left:
            player->move({0, -1},
                         f->isAvailable(x, y - 1));
            break;
        case sf::Keyboard::Right:
            player->move({0, 1},
                         f->isAvailable(x, y + 1));
            break;
        case sf::Keyboard::Down:
            player->move({1, 0},
                         f->isAvailable(x + 1, y));
            break;
        case sf::Keyboard::Escape:
            fieldCaretaker->backUp();
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
    for(auto x : enemies) {
        gui.drawEntity(x);
    }
    gui.drawEntity<Player>(player);
    gui.drawCoins(f, endCoords[0], endCoords[1]);
    gui.display();
}
