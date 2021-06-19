//
// Created by yudjin on 10/11/20.
//

#ifndef OOP_GUI_H
#define OOP_GUI_H

#include <SFML/Graphics.hpp>

#include "../Model/Cell.h"
#include "../Model/Player.h"


#include <typeinfo>
#include <iostream>
using std::cout;
using std::string;

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

    template<class T>
    sf::Color getEntityColor(T *entity);

    template<class T>
    void drawEntity(T *entity) {
        drawCircleShape(getEntityColor(entity), playerSize,
                        leftX + entity->position.y * rectSize,
                        leftY + entity->position.x * rectSize);
    }

    void drawCoins(Field *f, int endX, int endY);

    void drawCircleShape(sf::Color color, int size, int x, int y);

    void stop();

    void clear();

    void display();

    sf::RenderWindow* getWindow();

private:
    sf::RenderWindow window;
};


template<class T>
sf::Color Gui::getEntityColor(T *entity) {
    sf::Color color;
    string entityName = typeid(*entity).name();
    if( entityName == "6Player") {
        color = sf::Color::Yellow;
    }
    else if(entityName == "5EnemyI11IEnemyStateE") {
        color = sf::Color::Red;
    }
    return color;
}


#endif //OOP_GUI_H
