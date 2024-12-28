#ifndef SKINSMENU_H
#define SKINSMENU_H

#include <SFML/Graphics.hpp>
#include "User.h"

class SkinsMenu
{
public:
    SkinsMenu(sf::RenderWindow& window, User* user);
    void showSkins();

private:
    sf::RenderWindow& window;
    User* user;
    sf::Font font;
    std::vector<sf::Text> textOptions;
};

#endif
