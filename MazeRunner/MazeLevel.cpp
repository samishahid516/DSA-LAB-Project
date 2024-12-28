#include "MazeLevel.h"
#include <fstream>
#include <stack>
#include <iostream>

MazeLevel::MazeLevel(int levelNumber, const std::string& filePath, sf::RenderWindow& window, float cellSize)
	: levelNumber(levelNumber), window(window), cellSize(cellSize)
{
	loadMazeFromFile(filePath);

	if (!moveBuffer.loadFromFile("sounds/move_sound.wav")) {
		std::cerr << "Error loading move sound!" << std::endl;
	}
	moveSound.setBuffer(moveBuffer);

	wallShape.setSize(sf::Vector2f(cellSize, cellSize));
	pathShape.setSize(sf::Vector2f(cellSize, cellSize));
	playerShape.setSize(sf::Vector2f(cellSize, cellSize));
	endDoorShape.setSize(sf::Vector2f(cellSize, cellSize));

	// Load textures for wall (bricks), path (grass), player, start door, and end door
	if (!wallTexture.loadFromFile("images/wall.png")) {
		std::cerr << "Error loading brick wall texture!" << std::endl;
	}
	if (!playerTexture.loadFromFile("images/player.png")) {
		std::cerr << "Error loading player icon texture!" << std::endl;
	}

	if (!endDoorTexture.loadFromFile("images/end_door.png")) {
		std::cerr << "Error loading end door texture!" << std::endl;
	}

	wallShape.setTexture(&wallTexture);
	playerShape.setTexture(&playerTexture);
	endDoorShape.setTexture(&endDoorTexture);

	// Find the player’s starting position in the maze
	for (int y = 0; y < mazeLayout.size(); ++y)
	{
		for (int x = 0; x < mazeLayout[y].size(); ++x)
		{
			if (mazeLayout[y][x] == 'S')
			{
				playerPosition = { x, y };
				break;
			}
		}
	}
}

bool MazeLevel::movePlayer(int dx, int dy)
{
	int newX = playerPosition.first + dx;
	int newY = playerPosition.second + dy;

	// Check if within bounds and valid move
	if (newX < 0 || newX >= mazeLayout[0].size() || newY < 0 || newY >= mazeLayout.size())
		return false;
	if (mazeLayout[newY][newX] == '1') // Wall check
		return false;

	playerPosition = { newX, newY };

	// Play the movement sound
	moveSound.play(); // This will play the sound whenever the player moves

	return true;
}

void MazeLevel::backtrack()
{
	if (!movementStack.empty())
	{
		playerPosition = movementStack.top();
		movementStack.pop();
	}
}

void MazeLevel::handleInput()
{
	if (!window.hasFocus())
		return;

	int dx = 0, dy = 0;

	// Check for movement keys using isKeyPressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))  // Move up
	{
		dy = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))  // Move down
	{
		dy = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))  // Move left
	{
		dx = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))  // Move right
	{
		dx = 1;
	}

	// Check for backtracking with the 'B' key
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))  // Backtrack
	{
		backtrack();
		return;
	}

	// Prevent moving back to the last position
	if (!movementStack.empty())
	{
		auto lastPosition = movementStack.top();
		int lastX = lastPosition.first;
		int lastY = lastPosition.second;

		// Check if the player is trying to move to the last position
		if (playerPosition.first + dx == lastX && playerPosition.second + dy == lastY)
		{
			movementStack.pop();
			playerPosition = { lastX, lastY };  // Reset to the previous position
			return;
		}
	}

	// Move player
	movePlayer(dx, dy);
}


bool MazeLevel::isCompleted()
{
	if (playerPosition.second >= 0 && playerPosition.second < mazeLayout.size() &&
		playerPosition.first >= 0 && playerPosition.first < mazeLayout[playerPosition.second].size())
	{
		return mazeLayout[playerPosition.second][playerPosition.first] == 'E';
	}
}

void MazeLevel::loadMazeFromFile(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		std::cerr << "Error opening maze file: " << filePath << std::endl;
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		mazeLayout.push_back(line);
	}
}

int MazeLevel::getLevelNumber() const
{
	return levelNumber;
}

void MazeLevel::drawMaze()
{
	for (int y = 0; y < mazeLayout.size(); ++y)
	{
		for (int x = 0; x < mazeLayout[y].size(); ++x)
		{
			float posX = x * cellSize;
			float posY = y * cellSize;

			if (mazeLayout[y][x] == 'S') // Start position
			{
				sf::Sprite playerSprite(playerTexture);
				playerSprite.setPosition(posX, posY);
				window.draw(playerSprite); // Draw player
			}
			else if (mazeLayout[y][x] == 'E') // End position
			{
				sf::Sprite endDoorSprite(endDoorTexture);
				endDoorSprite.setPosition(posX, posY);
				window.draw(endDoorSprite); // Draw end door
			}
			else if (mazeLayout[y][x] == '1') // Wall (bricks)
			{
				sf::Sprite wallSprite(wallTexture);
				wallSprite.setPosition(posX, posY);
				window.draw(wallSprite); // Draw wall
			}
			else if (mazeLayout[y][x] == '0') // Path (grass)
			{
				sf::RectangleShape pathShape(sf::Vector2f(cellSize, cellSize));
				pathShape.setPosition(posX, posY);
				pathShape.setFillColor(sf::Color::Green); // Path color (grass)
				window.draw(pathShape); // Draw path
			}
		}
	}
}
