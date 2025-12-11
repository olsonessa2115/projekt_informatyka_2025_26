#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <cmath>
#include "cegielka.h"
#include "pilka.h"
#include "paletka.h"
#include "menu.h"

enum Tryb { START, ROZGRYWKA, PAUZA, PRZEGRANA, KONIEC };

class Game {
private:
    sf::RenderWindow okno;
    Tryb stan;
    sf::Clock zegarKolizji;

    Menu interfejsMenu;
    Paletka gracz;
    Pilka kula;
    std::vector<Cegielka> poziom;

    sf::Font font;
    sf::Text txtPauza;
    sf::Text txtGameOver;

    sf::Vector2f predkoscPilki;
    float predkoscGracza;

    void inicjalizujZasoby();
    void resetujMape();
    void obslugaInputu();
    void logikaGry();
    void renderowanie();

    void logikaKolizjiSciany();
    void logikaKolizjiPaletka();
    void logikaKolizjiCegly();

    void systemZapisu();
    void systemOdczytu();

public:
    Game();
    void start();
};

Game::Game() : okno(sf::VideoMode(800, 600), "Arkanoid") {
    okno.setFramerateLimit(60);
    stan = START;
    predkoscGracza = 9.0f;

    interfejsMenu.zaladuj(800.f, 600.f);
    inicjalizujZasoby();
    resetujMape();
}

void Game::inicjalizujZasoby() {
    if (font.loadFromFile("arial.ttf")) {
        txtPauza.setFont(font);
        txtPauza.setString("PAUZA (ESC - powrot)");
        txtPauza.setCharacterSize(40);
        txtPauza.setOrigin(txtPauza.getLocalBounds().width / 2, txtPauza.getLocalBounds().height / 2);
        txtPauza.setPosition(400, 300);

        txtGameOver.setFont(font);
        txtGameOver.setString("GAME OVER (ENTER - restart)");
        txtGameOver.setCharacterSize(40);
        txtGameOver.setFillColor(sf::Color::Red);
        txtGameOver.setOrigin(txtGameOver.getLocalBounds().width / 2, txtGameOver.getLocalBounds().height / 2);
        txtGameOver.setPosition(400, 300);
    }
}

void Game::resetujMape() {
    gracz.ustawPozycje(400.f, 570.f);
    kula.ustawPozycje(400.f, 320.f);
    predkoscPilki = { 5.0f, 5.0f };

    poziom.clear();
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 8; x++) {
            int hp = 4 - (y / 2);
            if (hp < 1) hp = 1;
            poziom.emplace_back(102.5f + x * 85.f, 50.f + y * 30.f, hp);
        }
    }
}

void Game::start() {
    while (okno.isOpen() && stan != KONIEC) {
        obslugaInputu();
        logikaGry();
        renderowanie();
    }
}

void Game::obslugaInputu() {
    sf::Event e;
    while (okno.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            stan = KONIEC;
            okno.close();
        }

        if (e.type == sf::Event::KeyPressed) {
            if (stan == START) {
                if (e.key.code == sf::Keyboard::Up) interfejsMenu.nawiguj(-1);
                else if (e.key.code == sf::Keyboard::Down) interfejsMenu.nawiguj(1);
                else if (e.key.code == sf::Keyboard::Return) {
                    int w = interfejsMenu.dajWybor();
                    if (w == 0) { resetujMape(); stan = ROZGRYWKA; }
                    else if (w == 1) { systemOdczytu(); stan = ROZGRYWKA; }
                    else if (w == 2) { stan = KONIEC; okno.close(); }
                }
            }
            else if (stan == ROZGRYWKA) {
                if (e.key.code == sf::Keyboard::Escape) stan = PAUZA;
                else if (e.key.code == sf::Keyboard::F5) systemZapisu();
                else if (e.key.code == sf::Keyboard::F6) systemOdczytu();
            }
            else if (stan == PAUZA) {
                if (e.key.code == sf::Keyboard::Escape) stan = ROZGRYWKA;
            }
            else if (stan == PRZEGRANA) {
                if (e.key.code == sf::Keyboard::Return) {
                    resetujMape();
                    stan = ROZGRYWKA;
                }
            }
        }
    }

    if (stan == ROZGRYWKA) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (gracz.pobierzPozycje().x - 60.f > 0)
                gracz.przesun(-predkoscGracza);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (gracz.pobierzPozycje().x + 60.f < 800)
                gracz.przesun(predkoscGracza);
        }
    }
}

void Game::logikaGry() {
    if (stan != ROZGRYWKA) return;

    kula.ruch(predkoscPilki.x, predkoscPilki.y);

    logikaKolizjiSciany();

    if (zegarKolizji.getElapsedTime().asMilliseconds() > 50) {
        logikaKolizjiPaletka();
        logikaKolizjiCegly();
    }
}

void Game::logikaKolizjiSciany() {
    sf::Vector2f pos = kula.pobierzPozycje();
    float r = kula.pobierzPromien();

    if (pos.x - r <= 0 || pos.x + r >= 800) predkoscPilki.x = -predkoscPilki.x;
    if (pos.y - r <= 0) predkoscPilki.y = -predkoscPilki.y;

    if (pos.y - r > 600) stan = PRZEGRANA;
}

void Game::logikaKolizjiPaletka() {
    sf::Vector2f pilkaPos = kula.pobierzPozycje();
    sf::Vector2f paletkaPos = gracz.pobierzPozycje();
    float r = kula.pobierzPromien();

    if (pilkaPos.y + r >= paletkaPos.y - 7.5f &&
        pilkaPos.y - r <= paletkaPos.y + 7.5f &&
        pilkaPos.x + r >= paletkaPos.x - 60.f &&
        pilkaPos.x - r <= paletkaPos.x + 60.f)
    {
        predkoscPilki.y = -std::abs(predkoscPilki.y);
        zegarKolizji.restart();
    }
}

void Game::logikaKolizjiCegly() {
    sf::FloatRect bBox = kula.getKsztalt().getGlobalBounds();

    for (size_t i = 0; i < poziom.size(); ) {
        if (poziom[i].czyZniszczona()) {
            i++;
            continue;
        }

        sf::FloatRect cBox = poziom[i].getKsztalt().getGlobalBounds();

        if (bBox.intersects(cBox)) {
            poziom[i].otrzymajObrazenia();

            sf::FloatRect intersekcja;
            bBox.intersects(cBox, intersekcja);

            if (intersekcja.width < intersekcja.height)
                predkoscPilki.x = -predkoscPilki.x;
            else
                predkoscPilki.y = -predkoscPilki.y;

            zegarKolizji.restart();

            if (poziom[i].czyZniszczona()) {
                poziom.erase(poziom.begin() + i);
            }
            else {
                i++;
            }
            return;
        }
        i++;
    }
}

void Game::renderowanie() {
    okno.clear(sf::Color(20, 20, 40));

    if (stan == START) {
        interfejsMenu.rysuj(okno);
    }
    else {
        okno.draw(gracz.getKsztalt());
        okno.draw(kula.getKsztalt());
        for (auto& c : poziom) okno.draw(c.getKsztalt());

        if (stan == PAUZA) okno.draw(txtPauza);
        if (stan == PRZEGRANA) okno.draw(txtGameOver);
    }
    okno.display();
}

void Game::systemZapisu() {
    std::ofstream plik("savegame.txt");
    if (!plik.is_open()) return;

    plik << gracz.pobierzPozycje().x << " " << gracz.pobierzPozycje().y << "\n"
        << kula.pobierzPozycje().x << " " << kula.pobierzPozycje().y << "\n"
        << predkoscPilki.x << " " << predkoscPilki.y << "\n"
        << poziom.size() << "\n";

    for (auto& c : poziom) {
        plik << c.getKsztalt().getPosition().x << " "
            << c.getKsztalt().getPosition().y << " "
            << c.pobierzHp() << "\n";
    }
}

void Game::systemOdczytu() {
    std::ifstream plik("savegame.txt");
    if (!plik.is_open()) return;

    float gx, gy, kx, ky;
    size_t ilosc;

    plik >> gx >> gy >> kx >> ky >> predkoscPilki.x >> predkoscPilki.y >> ilosc;

    gracz.ustawPozycje(gx, gy);
    kula.ustawPozycje(kx, ky);

    poziom.clear();
    for (size_t i = 0; i < ilosc; i++) {
        float cx, cy;
        int hp;
        plik >> cx >> cy >> hp;
        poziom.emplace_back(cx, cy, hp);
    }
}