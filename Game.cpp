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

void dbgGraph(Field *f) {
    for (auto it : *f) {
        if (it.is_available > 0) {
            cout << it.num << " :: ";
            for (int i = 0; i < adjacencySize; i++) {
                cout << "(" << it.adjacencyList[i][0] << ", " << it.adjacencyList[i][1]
                     << ")";
            }
            cout << "\n";
        }
    }
}

void Game::init() {
    window.create(sf::VideoMode(widthPixels, heightPixels), "PAC-MAN");

    // TODO(YudjinSud):
    // Logging system which will enable configure game start/end point
    // from file. Also this system should provide map-configuration.

    int start = 1, end = 9;

    f = Field::GetInstance(start, end);
    player = new Player(start,start);

    f->makeWall(2);
    f->makeWall(2 + 10);
    f->makeWall(12 + width);
    f->makeWall(22 + width);
    f->makeWall(32 + width);
//    f->makeWall(42 + width);
//    f->makeWall(52 + width);
    f->makeWall(62 + width);
    f->makeWall(72 + width);
    f->makeWall(82 + width);
    f->makeWall(5);
    f->makeWall(9);


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

     //dbgGraph(f);

    if (f->checkConnectedComponent()) {
        cout << START << "Граф связен - инвариант сохранен !\n";
    } else {
        cout << EXIT << "Инвариант нарушен !\n";
    }


    while (window.isOpen()) {
        tick();
        draw();
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
    cout << player->x << " " << player->y << "\n";
}

void Game::drawWall(Cell c) {
    sf::RectangleShape sh;
    sh.setSize(v2f(rectSize, rectSize));
    sh.setFillColor(sf::Color::Blue);
    sh.setOutlineColor(sf::Color::Red);
    sh.setOutlineThickness(1);
    sh.setPosition(leftX + c.y*rectSize, leftY+ c.x * rectSize);
    window.draw(sh);
}

void Game::drawPlayer() {
    sf::CircleShape sh;
    sh.setRadius(playerSize);
    sh.setFillColor(sf::Color::Yellow);
    sh.setPosition(leftX + player->y*rectSize, leftY  + player->x*rectSize);
    sh.setOrigin(-rectSize/4, -rectSize/4);
    window.draw(sh);
}

void Game::draw() {
    window.clear();
    for(auto it : *f) {
        if(it.is_available == 0) {
            drawWall(it);
        }
    }
    drawPlayer();
    sleep(sf::milliseconds(latency));
    window.display();
}