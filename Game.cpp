//
// Created by yudjin on 10/5/20.
//

#include "Game.h"

#define RESET   "\033[0m"
#define EXIT     "\033[1m\033[31m"      /* Bold Red */
#define START   "\033[1m\033[32m"      /* Bold Green */
#define BORDER   "\033[1m\033[37m"      /* Bold Black */
#define PLAIN  "\033[1m\033[33m"      /* Bold Yellow */

#define v2f sf::Vector2f

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
    window.create(sf::VideoMode(widthPixels, heightPixels), "PAC-MAN");

    // TODO(YudjinSud):
    // Logging system which will enable configure game start/end point
    // from file. Also this system should provide map-configuration.

    start = 1, end = 3;
    startCoords = f->coordsByNum(start);
    endCoords = f->coordsByNum(end);

    f = Field::GetInstance(start, end);
    player = new Player(startCoords[0], startCoords[1]);

    // Необходимо проверять, что это не вход и не выход
    f->makeWall(5);
//    f->makeWall(15);
//    f->makeWall(32);
//    f->makeWall(76);
//    f->makeWall(9);
//    f->makeWall(34);

    f->initCoins(startCoords);
    dbgGraph(f, start, end);

    while (window.isOpen()) {
        tick();
        draw();
    }
}

void Game::checkCoinsStatus() {
    int x = player->x, y = player->y;
    // Прошел ли через монетку?
    if (f->coins[x][y]->isAlive) {
        *player += *(f->coins[x][y]); // Взаимодействие игрока с элементом через перегруженный оператор
        f->coins[x][y]->isAlive = false;
    }
//    cout << player->score << '\n';
}

void Game::checkEndStatus() {
    //Подсчет количества оставшихся монет
    int cnt = 0;
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            Coin *c = f->coins[i][j];
            if (c && c->isAlive) cnt++;
        }
    }
    bool isEndReached = endCoords[0] == player->x && endCoords[1] == player->y;
    if (player->life == 0 || cnt == 0 || isEndReached) {
        window.close();
    }
}

void Game::tick() {
    while (window.pollEvent(events)) {
        if (events.type == sf::Event::Closed)
            window.close();
        if (events.type == sf::Event::KeyPressed) {
            processInput();
        }
    }
    checkCoinsStatus();
    checkEndStatus();
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
            window.close();
    }

}

void Game::drawWall(Cell c) {
    sf::RectangleShape sh;
    sh.setSize(v2f(rectSize, rectSize));
    sh.setFillColor(sf::Color::Blue);
    sh.setOutlineColor(sf::Color::Red);
    sh.setOutlineThickness(1);
    sh.setPosition(leftX + c.y * rectSize, leftY + c.x * rectSize);
    window.draw(sh);
}

void Game::drawCircleShape(sf::Color color, int size, int x, int y) {
    sf::CircleShape sh;
    sh.setRadius(size);
    sh.setFillColor(color);
    sh.setPosition(x, y);
    sh.setOrigin(-rectSize / 4, -rectSize / 4);
    window.draw(sh);
}

void Game::drawPlayer() {
    drawCircleShape(sf::Color::Yellow, playerSize,
                    leftX + player->y * rectSize,
                    leftY + player->x * rectSize);
}


void Game::drawCoins() {
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            sf::Color color = sf::Color::Yellow;
            Coin *c = f->coins[i][j];
            if (c && c->isAlive) {
                if(c->x == endCoords[0] && c->y == endCoords[1]) {
                    color = sf::Color::Red;
                }
                drawCircleShape(color, coinSize,
                                leftX + c->y * rectSize,
                                leftY + c->x * rectSize);
            }
        }
    }
}

void Game::draw() {
    window.clear();
    for (auto it : *f) {
        if (it.is_available == 0) {
            drawWall(it);
        }
    }
    drawPlayer();
    drawCoins();
    sleep(sf::milliseconds(latency));
    window.display();
}