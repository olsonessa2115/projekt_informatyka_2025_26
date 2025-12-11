#pragma once
#include <SFML/Graphics.hpp>

class Paletka {
private:
    sf::RectangleShape paletka;
    sf::Vector2f position;
    float predkosc = 9.0f;
public:
    Paletka();
    void ruch();
    void rysuj(sf::RenderWindow& window);
    sf::Vector2f getPos() const { return paletka.getPosition(); }
    void setPosition(float x, float y) { paletka.setPosition(x, y); }
};

Paletka::Paletka() {
    paletka.setSize({ 120.f, 15.f });
    paletka.setOrigin(60.f, 7.5f);
    paletka.setPosition(400.f, 570.f);
    paletka.setFillColor(sf::Color(0, 255, 255));
    paletka.setOutlineThickness(2.f);
    paletka.setOutlineColor(sf::Color::Blue);
}

void Paletka::ruch() {
    sf::Vector2f pos = paletka.getPosition();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (pos.x - paletka.getSize().x / 2.f >= 0.f)
            paletka.move(-predkosc, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (pos.x + paletka.getSize().x / 2.f <= 800.f)
            paletka.move(predkosc, 0.f);
    }
}

void Paletka::rysuj(sf::RenderWindow& window) {
    window.draw(paletka);
}