#include "RandomAlgorithmSelector.h"
#include "Algorithms.h"


std::function<void()> RandomAlgorithmSelector::getRandomAlgorithm()
{
    // List of algorithms without difficulty parameters
    std::vector<std::function<void()>> algorithms = {
        []() { dfs_maze(); }, // Call dfs_maze without difficulty
        []() { prim_maze(); }  // Call prim_maze without difficulty
    };

    // Seed the random generator only once
    static bool isSeeded = false;
    if (!isSeeded) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        isSeeded = true;
    }

    // Select a random algorithm
    int randomIndex = std::rand() % algorithms.size();
    return algorithms[randomIndex]; // Return the randomly selected algorithm
}