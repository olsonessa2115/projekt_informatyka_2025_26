#pragma once
#include <SFML/Graphics.hpp>
#include <array>

class cegielka {
private:
    sf::RectangleShape cegla;
    sf::Vector2f position;
    float pktZycia;
    bool JestZniszczony;
    static const std::array<sf::Color, 4> kolory;
public:
    cegielka(int x, int y, int L);
    void rysuj(sf::RenderWindow& window);
    void trafienie();
    void aktualizujkolor();
    sf::Vector2f getPos() const { return cegla.getPosition(); }
    bool getJestZniszczony() const { return JestZniszczony; }
    float getHp() const { return pktZycia; }
};

const std::array<sf::Color, 4> cegielka::kolory = {
    sf::Color(75, 0, 130),
    sf::Color(138, 43, 226),
    sf::Color(186, 85, 211),
    sf::Color(255, 20, 147)
};

cegielka::cegielka(int x, int y, int L) {
    pktZycia = static_cast<float>(L);
    JestZniszczony = false;
    cegla.setSize({ 80.f, 25.f });
    cegla.setOrigin(40.f, 12.5f);
    cegla.setPosition(static_cast<float>(x), static_cast<float>(y));
    cegla.setOutlineThickness(1.f);
    cegla.setOutlineColor(sf::Color::Black);
    aktualizujkolor();
}

void cegielka::aktualizujkolor() {
    if (pktZycia >= 1 && pktZycia <= 4)
        cegla.setFillColor(kolory[static_cast<size_t>(pktZycia - 1)]);
    else if (pktZycia > 0)
        cegla.setFillColor(kolory[3]);
}

void cegielka::trafienie() {
    if (JestZniszczony)
        return;
    pktZycia--;
    aktualizujkolor();
    if (pktZycia <= 0)
        JestZniszczony = true;
}

void cegielka::rysuj(sf::RenderWindow& window) {
    window.draw(cegla);
}