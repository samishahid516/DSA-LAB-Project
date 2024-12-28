#ifndef PLAYMENU_H
#define PLAYMENU_H

#include <SFML/Graphics.hpp>
#include "CareerMode.h"
#include "User.h"

class PlayMenu
{
public:
    PlayMenu(sf::RenderWindow& window, User* user);

    void showPlayMenu();
    void handleInput();
    void draw();
    bool isModeSelected() const;

private:
    sf::RenderWindow& window;
    User* user;

    sf::Font font;
    sf::Text titleText;
    sf::Text careerModeText;
    sf::Text timeAttackModeText;
    sf::Text botModeText;
    sf::Text backText;

    void drawHoverEffects();
    bool isCareerModeSelected() const;
    bool isTimeAttackModeSelected() const;
    bool isBotModeSelected() const;
};

#endif // PLAYMENU_H
