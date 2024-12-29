// MazeGame.cpp
#include "MazeGame.h"

MazeGame::MazeGame() {}

void MazeGame::start()
{
    // Get a random algorithm without difficulty
    std::function<void()> selectedAlgorithm = RandomAlgorithmSelector::getRandomAlgorithm();

    // Generate the maze using the selected algorithm
    selectedAlgorithm(); // Call the selected maze algorithm

    // No need for window management here since it's handled within the maze algorithm itself
}
