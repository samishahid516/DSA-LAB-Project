#ifndef ACCOUNT_DETAILS_SCREEN_H
#define ACCOUNT_DETAILS_SCREEN_H

#include <SFML/Graphics.hpp>
#include "User.h"

class AccountDetailsScreen
{
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text titleText;
    sf::Text usernameText;
    sf::Text levelText;
    sf::Text scoreText;
    sf::Text completedLevelsText;
    sf::Text unlockedSkinsText;
    sf::Text backText;

    bool ReturnToMainMenu = false;

    User* user;

public:
    AccountDetailsScreen(sf::RenderWindow& window, User* user);
    void displayAccountDetails();
    void handleInput(sf::Event& event);
    void draw();
    void drawhovereffects();
};

#endif // ACCOUNT_DETAILS_SCREEN_H
