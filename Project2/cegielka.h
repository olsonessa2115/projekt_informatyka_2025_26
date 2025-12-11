#pragma once
#include <SFML/Graphics.hpp>

class Cegielka {
private:
    sf::RectangleShape blok;
    int wytrzymalosc;
    bool aktywna;

    void ustawKolor();

public:
    Cegielka(float x, float y, int hp);
    sf::RectangleShape& getKsztalt();
    bool czyZniszczona() const;
    void otrzymajObrazenia();
    int pobierzHp() const;
};

Cegielka::Cegielka(float x, float y, int hp) {
    wytrzymalosc = hp;
    aktywna = true;

    blok.setSize(sf::Vector2f(80.f, 25.f));
    blok.setOrigin(40.f, 12.5f);
    blok.setPosition(x, y);
    blok.setOutlineThickness(1.f);
    blok.setOutlineColor(sf::Color::Black);
    ustawKolor();
}

void Cegielka::ustawKolor() {
    if (wytrzymalosc >= 4) blok.setFillColor(sf::Color(255, 20, 147));
    else if (wytrzymalosc == 3) blok.setFillColor(sf::Color(186, 85, 211));
    else if (wytrzymalosc == 2) blok.setFillColor(sf::Color(138, 43, 226));
    else blok.setFillColor(sf::Color(75, 0, 130));
}

sf::RectangleShape& Cegielka::getKsztalt() {
    return blok;
}

bool Cegielka::czyZniszczona() const {
    return !aktywna;
}

void Cegielka::otrzymajObrazenia() {
    if (!aktywna) return;
    wytrzymalosc--;
    ustawKolor();
    if (wytrzymalosc <= 0) aktywna = false;
}

int Cegielka::pobierzHp() const {
    return wytrzymalosc;
}