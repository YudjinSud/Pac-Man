//
// Created by yudjin on 10/11/20.
//

#include "Gui.h"


void Gui::drawPlayer(Player player) {
    drawCircleShape(sf::Color::Yellow, playerSize,
                    leftX + player.y * rectSize,
                    leftY + player.x * rectSize);
}

void Gui::drawCoins(Field *f, int endX, int endY) {
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            sf::Color color = sf::Color::Yellow;
            Item *c = f->_cells[i][j].item;
            if (c && c->isAlive()) {
                if(c->getX() == endX && c->getY() == endY) {
                    color = sf::Color::Red;
                }
                drawCircleShape(color, coinSize,
                                leftX + c->getY() * rectSize,
                                leftY + c->getX() * rectSize);
            }
        }
    }
}

void Gui::drawWall(Cell c) {
    sf::RectangleShape sh;
    sh.setSize(v2f(rectSize, rectSize));
    sh.setFillColor(sf::Color::Blue);
    sh.setOutlineColor(sf::Color::Red);
    sh.setOutlineThickness(1);
    sh.setPosition(leftX + c.y * rectSize, leftY + c.x * rectSize);
    window.draw(sh);
}

void Gui::drawCircleShape(sf::Color color, int size, int x, int y) {
    sf::CircleShape sh;
    sh.setRadius(size);
    sh.setFillColor(color);
    sh.setPosition(x, y);
    sh.setOrigin(-rectSize / 4, -rectSize / 4);
    window.draw(sh);
}


sf::RenderWindow* Gui::getWindow() {
    return &window;
}

void Gui::stop() {
    this->window.close();
}

void Gui::clear() {
    this->window.clear();
}

void Gui::display() {
    sleep(sf::milliseconds(latency));
    this->window.display();
}

sf::RenderWindow* Gui::create() {
    this->window.create(sf::VideoMode(widthPixels, heightPixels), "PAC-MAN");
    return &window;
}
