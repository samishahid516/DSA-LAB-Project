#include "SkinsMenu.h"
#include <iostream>

SkinsMenu::SkinsMenu(sf::RenderWindow& window, User* user)
    : window(window), user(user)
{
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        std::cerr << "Error loading font!" << std::endl;
    }

    textOptions.push_back(sf::Text("Skin 1", font, 30));
    textOptions.push_back(sf::Text("Skin 2", font, 30));

    for (size_t i = 0; i < textOptions.size(); ++i)
    {
        textOptions[i].setPosition(100.f, 100.f + i * 50);
    }
}

void SkinsMenu::showSkins()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        for (auto& option : textOptions)
        {
            window.draw(option);
        }

        window.display();
    }
}
