#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SFML/Graphics.hpp>

using namespace std;

const int WIDTH = 2000, HEIGHT = 1200;
const int GRID_HEIGHT = 40, GRID_WIDTH = 40;
const int SQUARE_SIZE = 20;
const float LINE_THICKNESS = 0.9f;
const int CELL_SIZE = std::min(WIDTH / GRID_WIDTH, HEIGHT / GRID_HEIGHT);

#endif