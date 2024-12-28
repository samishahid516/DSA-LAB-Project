#ifndef MAZELEVEL_H
#define MAZELEVEL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // To include sound functionality
#include <vector>
#include <string>
#include <stack>

using namespace std;

class MazeLevel
{
public:
	// Constructor
	MazeLevel(int levelNumber, const std::string& filePath, sf::RenderWindow& window, float cellSize = 50.f);

	// Player movement methods
	bool movePlayer(int dx, int dy);
	void backtrack();
	void handleInput();

	// Level status methods
	bool isCompleted();
	int getLevelNumber() const;

	// Rendering method
	void drawMaze();

private:
	// Helper methods
	void loadMazeFromFile(const std::string& filePath);

	// Attributes
	int levelNumber;
	float cellSize;
	sf::RenderWindow& window;

	// Maze representation
	std::vector<std::string> mazeLayout;
	std::pair<int, int> playerPosition;

	// SFML shapes for rendering
	sf::RectangleShape wallShape;
	sf::RectangleShape pathShape;
	sf::RectangleShape playerShape;
	sf::RectangleShape endDoorShape;
	sf::SoundBuffer moveBuffer;
	sf::Sound moveSound;

	sf::Texture wallTexture;
	sf::Texture playerTexture;       // Player icon texture  // Start door texture
	sf::Texture endDoorTexture;      // End door texture

	// Stack to store movement for backtracking
	std::stack<std::pair<int, int>> movementStack;
};

#endif // MAZELEVEL_H
