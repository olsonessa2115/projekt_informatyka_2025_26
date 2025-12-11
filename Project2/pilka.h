#pragma once
#include <SFML/Graphics.hpp>

class Pilka {
private:
    sf::CircleShape kula;

public:
    Pilka();
    void ustawPozycje(float x, float y);
    void ruch(float dx, float dy);
    sf::Vector2f pobierzPozycje() const;
    float pobierzPromien() const;
    sf::CircleShape& getKsztalt();
};

Pilka::Pilka() {
    kula.setRadius(12.f);
    kula.setOrigin(12.f, 12.f);
    kula.setFillColor(sf::Color(255, 140, 0));
    kula.setOutlineThickness(2.f);
    kula.setOutlineColor(sf::Color::White);
    ustawPozycje(400.f, 320.f);
}

void Pilka::ustawPozycje(float x, float y) {
    kula.setPosition(x, y);
}

void Pilka::ruch(float dx, float dy) {
    kula.move(dx, dy);
}

sf::Vector2f Pilka::pobierzPozycje() const {
    return kula.getPosition();
}

float Pilka::pobierzPromien() const {
    return kula.getRadius();
}

sf::CircleShape& Pilka::getKsztalt() {
    return kula;
}