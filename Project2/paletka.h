#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
    sf::RectangleShape belka;

public:
    Paletka();
    void ustawPozycje(float x, float y);
    void przesun(float x);
    sf::Vector2f pobierzPozycje() const;
    sf::RectangleShape& getKsztalt();
};

Paletka::Paletka() {
    belka.setSize(sf::Vector2f(120.f, 15.f));
    belka.setOrigin(60.f, 7.5f);
    belka.setFillColor(sf::Color(0, 255, 255));
    belka.setOutlineThickness(2.f);
    belka.setOutlineColor(sf::Color::Blue);
    ustawPozycje(400.f, 570.f);
}

void Paletka::ustawPozycje(float x, float y) {
    belka.setPosition(x, y);
}

void Paletka::przesun(float x) {
    belka.move(x, 0.f);
}

sf::Vector2f Paletka::pobierzPozycje() const {
    return belka.getPosition();
}

sf::RectangleShape& Paletka::getKsztalt() {
    return belka;
}