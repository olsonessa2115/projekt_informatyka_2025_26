#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#define MAX_ITEMS 3

class Menu {
private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menuItems[MAX_ITEMS];

public:
    Menu();
    void setup(float width, float height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getPressedItem() const { return selectedItemIndex; }
};

Menu::Menu() {
    selectedItemIndex = 0;
}

void Menu::setup(float width, float height)
{
    if (!font.loadFromFile("arial.ttf")) {
    }

    std::string options[MAX_ITEMS] = { "ZACZNIJ GRE", "WCZYTAJ GRE", "WYJDZ" };

    for (int i = 0; i < MAX_ITEMS; i++) {
        menuItems[i].setFont(font);
        menuItems[i].setString(options[i]);
        menuItems[i].setCharacterSize(40);

        sf::FloatRect textRect = menuItems[i].getLocalBounds();
        menuItems[i].setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        menuItems[i].setPosition(sf::Vector2f(width / 2.0f, height / (MAX_ITEMS + 1) * (i + 1)));

        if (i == 0)
            menuItems[i].setFillColor(sf::Color::Red);
        else
            menuItems[i].setFillColor(sf::Color::White);
    }
}

void Menu::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        window.draw(menuItems[i]);
    }
}

void Menu::moveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown()
{
    if (selectedItemIndex + 1 < MAX_ITEMS)
    {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}