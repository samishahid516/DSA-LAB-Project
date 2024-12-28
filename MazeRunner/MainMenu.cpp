#include "MainMenu.h"
#include "PlayMenu.h"
#include "AccountDetailsScreen.h"
#include "SkinsMenu.h"
#include <iostream>

using namespace std;

MainMenu::MainMenu(sf::RenderWindow& window, User* user)
	: window(window), user(user), selectedOption(0), backgroundOffset(0)
{
	if (!font.loadFromFile("fonts/OuterSpaceMilitia.ttf"))
	{
		cerr << "Error loading font!" << endl;
	}

	menuOptions = { "Play", "View Account Details", "Skins", "Levels" };

	for (size_t i = 0; i < menuOptions.size(); ++i)
	{
		sf::Text option(menuOptions[i], font, 30);
		option.setPosition(100.f, 100.f + i * 50);
		textOptions.push_back(option);
	}

	if (!backgroundTexture.loadFromFile("images/images.jpg"))
	{
		cerr << "Error loading background image!" << endl;
	}
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

	debounceClock.restart();
}

void MainMenu::handleInput()
{
	if (!window.hasFocus())
	{
		window.requestFocus(); // Ensure the window has focus to capture inputs
	}

	// Handle keyboard input (Up, Down, Enter)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (debounceClock.getElapsedTime().asMilliseconds() > 200)
		{
			selectedOption = (selectedOption == 0) ? menuOptions.size() - 1 : selectedOption - 1;
			debounceClock.restart();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (debounceClock.getElapsedTime().asMilliseconds() > 200)
		{
			selectedOption = (selectedOption == menuOptions.size() - 1) ? 0 : selectedOption + 1;
			debounceClock.restart();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		if (debounceClock.getElapsedTime().asMilliseconds() > 200)
		{
			executeOption(selectedOption);
			debounceClock.restart();
		}
	}

	// Handle mouse hover detection
	// Get mouse position relative to the window, works in both windowed and full screen
	auto mousePos = sf::Mouse::getPosition(window);
	for (size_t i = 0; i < textOptions.size(); ++i)
	{
		if (textOptions[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			selectedOption = i;  // Update the selected option based on mouse hover
			break; // Exit after detecting the hovered option
		}
	}

	// Handle mouse click (left button)
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (size_t i = 0; i < textOptions.size(); ++i)
		{
			if (textOptions[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
			{
				executeOption(i);
				break;
			}
		}
	}
}


void MainMenu::draw(float deltaTime)
{
	window.clear();

	// Background update
	updateBackground(deltaTime);
	window.draw(backgroundSprite);

	// Draw menu options with hover effects
	for (size_t i = 0; i < textOptions.size(); ++i)
	{
		// Apply hover effect if this is the selected option
		if (i == selectedOption)
		{
			drawHoverEffects(i);  // Apply hover effect for the selected option
		}
		else
		{
			// Reset other options to normal state (no hover)
			textOptions[i].setFillColor(sf::Color::White);
			textOptions[i].setScale(1.f, 1.f);
		}

		window.draw(textOptions[i]);
	}

	window.display();
}

void MainMenu::drawHoverEffects(size_t i)
{
	// Apply hover effect only for the selected option
	if (i == selectedOption)
	{
		textOptions[i].setFillColor(sf::Color::Red); // Change color to indicate hover
		textOptions[i].setScale(1.2f, 1.2f);         // Slightly scale up the text
	}
}

void MainMenu::updateBackground(float deltaTime)
{
	backgroundOffset += deltaTime * 50.f;
	if (backgroundOffset > backgroundTexture.getSize().x)
		backgroundOffset = 0.f;

	backgroundSprite.setTextureRect(sf::IntRect(static_cast<int>(backgroundOffset), 0, window.getSize().x, window.getSize().y));
}



void MainMenu::checkMouseHover()
{
	auto mousePos = sf::Mouse::getPosition(window);
	for (size_t i = 0; i < textOptions.size(); ++i)
	{
		if (textOptions[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			selectedOption = i;
		}
	}
}


void MainMenu::executeOption(size_t option)
{
	switch (option)
	{
	case 0:
		playMenu();
		break;
	case 1:
		viewAccountDetails();
		break;
	case 2:
		skinsMenu();
		break;
	case 3:
		levelsMenu();
		break;
	default:
		break;
	}
}

void MainMenu::playMenu()
{
	PlayMenu playMenu(window, user);
	playMenu.showPlayMenu();
}

void MainMenu::viewAccountDetails()
{
	AccountDetailsScreen accountDetailsScreen(window, user);
	accountDetailsScreen.displayAccountDetails();
}

void MainMenu::skinsMenu()
{
	SkinsMenu skinsMenu(window, user);
	skinsMenu.showSkins();
}

void MainMenu::levelsMenu()
{
	vector<string> levels = { "Level 1", "Level 2", "Level 3", "Level 4", "Level 5" };
	vector<sf::Text> levelTexts;

	for (size_t i = 0; i < levels.size(); ++i)
	{
		sf::Text levelText(levels[i], font, 30);
		levelText.setPosition(100.f, 100.f + i * 50);
		levelTexts.push_back(levelText);
	}

	size_t selectedLevel = 0;

	while (window.isOpen())
	{
		if (!window.hasFocus())
			return;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
					selectedLevel = (selectedLevel == 0) ? levels.size() - 1 : selectedLevel - 1;

				else if (event.key.code == sf::Keyboard::Down)
					selectedLevel = (selectedLevel == levels.size() - 1) ? 0 : selectedLevel + 1;

				else if (event.key.code == sf::Keyboard::Enter)
				{
					cout << "Selected " << levels[selectedLevel] << endl;
					return;
				}
			}
		}

		window.clear();
		for (size_t i = 0; i < levelTexts.size(); ++i)
		{
			if (i == selectedLevel)
				levelTexts[i].setFillColor(sf::Color::Red);
			else
				levelTexts[i].setFillColor(sf::Color::White);

			window.draw(levelTexts[i]);
		}
		window.display();
	}
}
