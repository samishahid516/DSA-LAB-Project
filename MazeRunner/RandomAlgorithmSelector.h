#ifndef RANDOM_ALGORITHM_SELECTOR_H
#define RANDOM_ALGORITHM_SELECTOR_H

#include <functional>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string> // Include for std::string
#include "Algorithms.h"

class RandomAlgorithmSelector
{
public:
    static std::function<void()> getRandomAlgorithm();
};

#endif // RANDOM_ALGORITHM_SELECTOR_H
