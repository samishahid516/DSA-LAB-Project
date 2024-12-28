#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "AccountDetailsScreen.h"
#include "PlayMenu.h"
#include "User.h"

using namespace std;

class MainMenu
{
private:
    User* user;
    sf::RenderWindow& window;
    sf::Font font;
    vector<string> menuOptions;
    vector<sf::Text> textOptions;
    size_t selectedOption;
    sf::Clock debounceClock;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    float backgroundOffset = 0.f;

public:
    MainMenu(sf::RenderWindow& window, User* user);
    ~MainMenu() = default;

    void handleInput();
    void updateBackground(float deltaTime);
    void draw(float deltaTime);
    void checkMouseHover();
    void drawHoverEffects(size_t i);
    void executeOption(size_t option);
    void playMenu();
    void levelsMenu();
    void viewAccountDetails();
    void skinsMenu();
};

#endif
