#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include "cegielka.h"
#include "pilka.h"
#include "paletka.h"
#include "menu.h"

enum class GameState { Menu, Playing, Paused, GameOver, Exiting };

class Game {
private:
    sf::RenderWindow window;
    sf::Clock zegar;
    sf::Font font;
    sf::Text pauseText;
    sf::Text gameOverText;
    GameState currentState;

    Menu menu;
    Paletka p1;
    Pilka p2;
    std::vector<cegielka> cegly;

    float dx = 5.0f;
    float dy = 5.0f;

    void processEvents();
    void update();
    void render();
    void saveGame();
    void loadGame();
    void resetGame();

public:
    Game();
    void run();
};

Game::Game() : window(sf::VideoMode(800, 600), "Arkanoid")
{
    window.setFramerateLimit(60);
    currentState = GameState::Menu;

    menu.setup(800.f, 600.f);

    if (font.loadFromFile("arial.ttf")) {
        pauseText.setFont(font);
        pauseText.setString("PAUZA\nNacisnij ESC aby wznowic");
        pauseText.setCharacterSize(40);
        pauseText.setFillColor(sf::Color::White);
        pauseText.setOutlineColor(sf::Color::Black);
        pauseText.setOutlineThickness(2.f);
        sf::FloatRect pauseRect = pauseText.getLocalBounds();
        pauseText.setOrigin(pauseRect.left + pauseRect.width / 2.0f,
            pauseRect.top + pauseRect.height / 2.0f);
        pauseText.setPosition(400.f, 300.f);

        gameOverText.setFont(font);
        gameOverText.setString("GAME OVER\nNacisnij ENTER, aby zagrac ponownie");
        gameOverText.setCharacterSize(40);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setOutlineColor(sf::Color::White);
        gameOverText.setOutlineThickness(2.f);
        sf::FloatRect goRect = gameOverText.getLocalBounds();
        gameOverText.setOrigin(goRect.left + goRect.width / 2.0f,
            goRect.top + goRect.height / 2.0f);
        gameOverText.setPosition(400.f, 300.f);
    }

    resetGame();
}

void Game::resetGame() {
    p1.setPosition(400.f, 570.f);
    p2.setPosition(400.f, 320.f);

    dx = 5.0f;
    dy = 5.0f;

    cegly.clear();
    const int rows = 6;
    const int cols = 8;
    const float spacingX = 85.f;
    const float spacingY = 30.f;
    const float totalWidth = (cols - 1) * spacingX;
    const float startX = (800.f - totalWidth) / 2.f;
    const float startY = 50.f;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < cols; x++)
        {
            int hp = 4 - (y / 2);
            if (hp < 1) hp = 1;
            cegly.emplace_back(static_cast<int>(startX + x * spacingX),
                static_cast<int>(startY + y * spacingY),
                hp);
        }
}

void Game::run() {
    while (window.isOpen() && currentState != GameState::Exiting) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            currentState = GameState::Exiting;
            window.close();
        }

        if (currentState == GameState::Menu) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    menu.moveUp();
                }
                if (event.key.code == sf::Keyboard::Down) {
                    menu.moveDown();
                }
                if (event.key.code == sf::Keyboard::Return) {
                    int selected = menu.getPressedItem();

                    if (selected == 0) {
                        resetGame();
                        currentState = GameState::Playing;
                    }
                    else if (selected == 1) {
                        loadGame();
                        currentState = GameState::Playing;
                    }
                    else if (selected == 2) {
                        currentState = GameState::Exiting;
                        window.close();
                    }
                }
            }
        }
        else if (currentState == GameState::Playing) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    currentState = GameState::Paused;
                }
                else if (event.key.code == sf::Keyboard::F5) {
                    saveGame();
                }
                else if (event.key.code == sf::Keyboard::F6) {
                    loadGame();
                }
            }
        }
        else if (currentState == GameState::Paused) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                currentState = GameState::Playing;
            }
        }
        else if (currentState == GameState::GameOver) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                resetGame();
                currentState = GameState::Playing;
            }
        }
    }
}

void Game::update() {
    if (currentState == GameState::Playing) {
        p1.ruch();
        p2.kolizja(zegar, dx, dy, window, p1, p2);

        for (int i = 0; i < static_cast<int>(cegly.size()); i++) {
            if (p2.getPos().y - 15.f <= cegly[i].getPos().y + 12.5f &&
                p2.getPos().y + 15.f >= cegly[i].getPos().y - 12.5f &&
                p2.getPos().x + 15.f >= cegly[i].getPos().x - 40.f &&
                p2.getPos().x - 15.f <= cegly[i].getPos().x + 40.f) {

                float diffX = p2.getPos().x - cegly[i].getPos().x;
                float diffY = p2.getPos().y - cegly[i].getPos().y;

                if (std::abs(diffX) > std::abs(diffY)) {
                    dx = -dx;
                    p2.przesun(dx > 0 ? 10.f : -10.f, 0.f);
                }
                else {
                    dy = -dy;
                    p2.przesun(0.f, dy > 0 ? 10.f : -10.f);
                }

                cegly[i].trafienie();
                if (cegly[i].getJestZniszczony()) {
                    cegly.erase(cegly.begin() + i);
                }
                break;
            }
        }

        float radius = p2.getPilka().getRadius();
        if (p2.getPos().y - radius > static_cast<float>(window.getSize().y) + 10.f) {
            currentState = GameState::GameOver;
        }
    }
}

void Game::render() {
    window.clear(sf::Color(20, 20, 40));

    if (currentState == GameState::Menu) {
        menu.draw(window);
    }
    else if (currentState == GameState::Playing || currentState == GameState::Paused || currentState == GameState::GameOver) {
        for (auto& cegla : cegly) {
            cegla.rysuj(window);
        }
        window.draw(p2.getPilka());
        p1.rysuj(window);

        if (currentState == GameState::Paused) {
            window.draw(pauseText);
        }
        else if (currentState == GameState::GameOver) {
            window.draw(gameOverText);
        }
    }
    window.display();
}

void Game::saveGame() {
    std::ofstream file("savegame.txt");
    if (file.is_open()) {
        file << p1.getPos().x << " " << p1.getPos().y << "\n";
        file << p2.getPos().x << " " << p2.getPos().y << "\n";
        file << dx << " " << dy << "\n";
        file << cegly.size() << "\n";
        for (const auto& c : cegly) {
            file << c.getPos().x << " " << c.getPos().y << " " << c.getHp() << "\n";
        }
        file.close();
    }
}

void Game::loadGame() {
    std::ifstream file("savegame.txt");
    if (file.is_open()) {
        float px, py, bx, by, ballDx, ballDy;
        size_t brickCount;
        file >> px >> py;
        p1.setPosition(px, py);
        file >> bx >> by;
        p2.setPosition(bx, by);
        file >> ballDx >> ballDy;
        dx = ballDx;
        dy = ballDy;
        file >> brickCount;
        cegly.clear();
        for (size_t i = 0; i < brickCount; i++) {
            float cx, cy, hp;
            file >> cx >> cy >> hp;
            cegly.emplace_back(static_cast<int>(cx), static_cast<int>(cy), static_cast<int>(hp));
        }
        file.close();
    }
}