//
// Created by yudjin on 10/11/20.
//

#ifndef OOP_GUI_H
#define OOP_GUI_H

#include <SFML/Graphics.hpp>

#include "../Model/Cell.h"
#include "../Model/Player.h"

#define widthPixels 640
#define heightPixels 640
#define rectSize 25
#define playerSize 7
#define coinSize 3
#define latency 5
#define leftX widthPixels / 3
#define leftY heightPixels/ 3

#define v2f sf::Vector2f

class Gui {
public:
    Gui() = default;

    sf::RenderWindow *create();

    void drawWall(Cell f);

    void drawPlayer(Player player);

    void drawCoins(Field *f, int endX, int endY);

    void drawCircleShape(sf::Color color, int size, int x, int y);

    void stop();

    void clear();

    void display();

    sf::RenderWindow* getWindow();

private:
    sf::RenderWindow window;
};


#endif //OOP_GUI_H
