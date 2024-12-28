#include "AccountDetailsScreen.h"

AccountDetailsScreen::AccountDetailsScreen(sf::RenderWindow& window, User* user)
    : window(window), user(user)
{
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        cerr << "Error loading font!" << std::endl;
    }

    titleText.setFont(font);
    titleText.setString("Account Details");
    titleText.setCharacterSize(40);
    titleText.setPosition(50.f, 30.f);

    usernameText.setFont(font);
    levelText.setFont(font);
    scoreText.setFont(font);
    completedLevelsText.setFont(font);
    unlockedSkinsText.setFont(font);

    backText.setFont(font);
    backText.setString("Back to Main Menu");
    backText.setCharacterSize(30);
    backText.setPosition(50.f, window.getSize().y - 100.f); 
}

void AccountDetailsScreen::displayAccountDetails()
{
    usernameText.setString("Username: " + user->getUsername());
    levelText.setString("Account Level: " + to_string(user->getAccountLevel()));
    scoreText.setString("Score: " + to_string(user->getScore()));

    string completedLevelsStr = "Completed Levels: ";
    for (int level : user->getCompletedLevels()) 
    {
        completedLevelsStr += to_string(level) + " ";
    }
    completedLevelsText.setString(completedLevelsStr);
 
    string unlockedSkinsStr = "Unlocked Skins: ";
    for (int skin : user->getUnlockedSkins()) 
    {
        unlockedSkinsStr += to_string(skin) + " ";
    }
    unlockedSkinsText.setString(unlockedSkinsStr);

    usernameText.setPosition(50.f, 100.f);
    levelText.setPosition(50.f, 150.f);
    scoreText.setPosition(50.f, 200.f);
    completedLevelsText.setPosition(50.f, 250.f);
    unlockedSkinsText.setPosition(50.f, 300.f);
    backText.setPosition(50.f, window.getSize().y - 100.f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            handleInput(event);
        }

        draw();
    }
}

void AccountDetailsScreen::handleInput(sf::Event& event)
{
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                window.close();
            }
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (backText.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) 
            {
                window.close();
            }
        }
    }
}

void AccountDetailsScreen::draw()
{
    window.clear();
    window.draw(titleText);
    window.draw(usernameText);
    window.draw(levelText);
    window.draw(scoreText);
    window.draw(completedLevelsText);
    window.draw(unlockedSkinsText);
    drawhovereffects();
    window.draw(backText);
    window.display();
}

void AccountDetailsScreen::drawhovereffects()
{
    auto mousePos = sf::Mouse::getPosition(window);
    if (backText.getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        backText.setFillColor(sf::Color::Red);
        backText.setScale(1.2f, 1.2f);
    }
    else
    {
        backText.setFillColor(sf::Color::White);
        backText.setScale(1.f, 1.f);
    }
}
