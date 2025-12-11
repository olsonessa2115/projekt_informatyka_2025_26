#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
private:
    std::vector<sf::Text> przyciski;
    sf::Font czcionka;
    int indeksWyboru;

    void odswiezWyglad();

public:
    Menu();
    void zaladuj(float szerokosc, float wysokosc);
    void rysuj(sf::RenderWindow& okno);
    void nawiguj(int delta);
    int dajWybor() const;
};

Menu::Menu() {
    indeksWyboru = 0;
}

void Menu::zaladuj(float szerokosc, float wysokosc) {
    if (!czcionka.loadFromFile("arial.ttf")) return;

    std::vector<std::string> etykiety = { "ZACZNIJ GRE", "WCZYTAJ GRE", "WYJDZ" };

    for (size_t i = 0; i < etykiety.size(); ++i) {
        sf::Text tekst;
        tekst.setFont(czcionka);
        tekst.setString(etykiety[i]);
        tekst.setCharacterSize(40);

        sf::FloatRect wymiary = tekst.getLocalBounds();
        tekst.setOrigin(wymiary.left + wymiary.width / 2.0f,
            wymiary.top + wymiary.height / 2.0f);

        tekst.setPosition(szerokosc / 2.0f, wysokosc / (etykiety.size() + 1) * (i + 1));
        przyciski.push_back(tekst);
    }
    odswiezWyglad();
}

void Menu::odswiezWyglad() {
    for (size_t i = 0; i < przyciski.size(); ++i) {
        if ((int)i == indeksWyboru)
            przyciski[i].setFillColor(sf::Color::Red);
        else
            przyciski[i].setFillColor(sf::Color::White);
    }
}

void Menu::nawiguj(int delta) {
    int nowy = indeksWyboru + delta;
    if (nowy >= 0 && nowy < (int)przyciski.size()) {
        indeksWyboru = nowy;
        odswiezWyglad();
    }
}

void Menu::rysuj(sf::RenderWindow& okno) {
    for (const auto& btn : przyciski) {
        okno.draw(btn);
    }
}

int Menu::dajWybor() const {
    return indeksWyboru;
}