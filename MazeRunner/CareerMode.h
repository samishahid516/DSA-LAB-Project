#ifndef CAREERMODE_H
#define CAREERMODE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "User.h"
#include "MazeLevel.h"
#include "DatabaseConnection.h"

using namespace std;

class CareerMode
{
private:
    sf::RenderWindow& window;
    vector<MazeLevel> levels;
    int currentLevelIndex;
    sf::Font font;
    sf::Text levelText;
    User* user;

    bool saveLevelProgress(DatabaseConnection& db, int levelNumber);

public:
    CareerMode(sf::RenderWindow& window, User* user);
    void loadLevels();
    void playCareerMode();
    void drawUI();
    bool loadUserProgress(DatabaseConnection& db);
};

#endif
