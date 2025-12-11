#pragma once
#include <SFML/Graphics.hpp>
#include "paletka.h"

class Pilka {
private:
    sf::Vector2f position;
    sf::CircleShape pilka;
public:
    Pilka();
    void przesun(float x_in, float y_in);
    void kolizja(sf::Clock& zegar, float& dx, float& dy, sf::RenderWindow& window, Paletka& p1, Pilka& p2);
    sf::CircleShape getPilka() const { return pilka; }
    sf::Vector2f getPos() const { return pilka.getPosition(); }
    void setPosition(float x, float y) { pilka.setPosition(x, y); }
};

Pilka::Pilka() {
    pilka.setRadius(12.f);
    pilka.setOrigin(12.f, 12.f);
    pilka.setPosition(400.f, 320.f);
    pilka.setFillColor(sf::Color(255, 140, 0));
    pilka.setOutlineThickness(2.f);
    pilka.setOutlineColor(sf::Color::White);
}

void Pilka::przesun(float x_in, float y_in) {
    sf::Vector2f pos;
    pos.x = x_in;
    pos.y = y_in;
    pilka.move(pos);
}

void Pilka::kolizja(sf::Clock& zegar, float& dx, float& dy, sf::RenderWindow& window, Paletka& p1, Pilka& p2) {
    if (zegar.getElapsedTime().asMilliseconds() > 15.0f) {
        if (p2.getPos().x + pilka.getRadius() >= static_cast<float>(window.getSize().x) || p2.getPos().x - pilka.getRadius() <= 0)
            dx = -dx;

        if (p2.getPos().y - pilka.getRadius() <= 0.f)
            dy = -dy;

        if (p2.getPos().y + pilka.getRadius() >= p1.getPos().y - 5.f &&
            p2.getPos().y - pilka.getRadius() <= p1.getPos().y + 5.f &&
            p2.getPos().x + pilka.getRadius() >= p1.getPos().x - 60.f &&
            p2.getPos().x - pilka.getRadius() <= p1.getPos().x + 60.f) {
            dy = -dy;
        }

        p2.przesun(dx, dy);
        zegar.restart();
    }
}