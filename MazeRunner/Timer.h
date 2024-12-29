#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <cstdio>

sf::RenderWindow myWindow(sf::VideoMode(1280, 720), "Maze");
sf::Clock clk;
sf::Text timestr;
sf::Font timefont;
char str[8];
int timerState = 0;
int timee = 0;
int previousTime = 0;
int totalTime = 120;
int minutes, seconds;
int timerFlag = 1;

void sringconvert(int minute, int second) {
    snprintf(str, sizeof(str), "%02d : %02d", minute, second);
}

void loadTimer() {
    if (!timefont.loadFromFile("fonts/font.ttf")) {
        printf("Failed to load font.\n");
        exit(1);
    }
    timestr.setFont(timefont);
    timestr.setPosition(sf::Vector2f(1150.0f, 100.0f));
    timestr.setCharacterSize(24);
    timestr.setFillColor(sf::Color::White);
}

void pauseTimer() {
    timerState = 0;
    timerFlag = 1;
}

void startTimer() {
    clk.restart();
    if (timerFlag) {
        previousTime = 0;
        totalTime = 300; // Set timer to 5 minutes
        timerFlag = 0;
    }
    timerState = 1;
}

void showTimer() {
    if (timerState == 1) {
        timee = clk.getElapsedTime().asSeconds();
        if (previousTime + 1 == timee && totalTime > -1) {
            minutes = totalTime / 60;
            seconds = totalTime % 60;
            sringconvert(minutes, seconds);
            timestr.setString(str);
            totalTime--;
            previousTime++;
        }
        myWindow.draw(timestr);
    }
}