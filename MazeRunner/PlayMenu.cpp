#include "PlayMenu.h"
#include <iostream>

PlayMenu::PlayMenu(sf::RenderWindow& window, User* user)
	: window(window), user(user)
{
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		std::cerr << "Error loading font!" << std::endl;
	}

	titleText.setFont(font);
	titleText.setString("Play Menu");
	titleText.setCharacterSize(40);
	titleText.setPosition(50.f, 30.f);

	careerModeText.setFont(font);
	careerModeText.setString("Career Mode");
	careerModeText.setCharacterSize(30);
	careerModeText.setPosition(50.f, 100.f);

	timeAttackModeText.setFont(font);
	timeAttackModeText.setString("Time Attack Mode");
	timeAttackModeText.setCharacterSize(30);
	timeAttackModeText.setPosition(50.f, 150.f);

	botModeText.setFont(font);
	botModeText.setString("Bot Mode");
	botModeText.setCharacterSize(30);
	botModeText.setPosition(50.f, 200.f);

	backText.setFont(font);
	backText.setString("Back to Main Menu");
	backText.setCharacterSize(30);
	backText.setPosition(50.f, window.getSize().y - 100.f);
}

void PlayMenu::showPlayMenu()
{
	bool isRunning = true;
	while (isRunning && window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			handleInput();
		}

		draw();
	}
}

void PlayMenu::handleInput()
{
	if (!window.hasFocus())
	{
		return; // Ignore input if window is not focused
	}

	// Handle mouse click (Left button)
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// Get the mouse position relative to the window
		auto mousePos = sf::Mouse::getPosition(window);

		// Check for Career Mode selection
		if (isCareerModeSelected())
		{
			cout << "Career Mode selected!" << endl;
			CareerMode careerMode(window, user);
			careerMode.playCareerMode();
		}
		// Check for Time Attack Mode selection
		else if (isTimeAttackModeSelected())
		{
			cout << "Time Attack Mode selected!" << std::endl;
		}
		// Check for Bot Mode selection
		else if (isBotModeSelected())
		{
			cout << "Bot Mode selected!" << std::endl;
		}
		// Check if Back button is clicked
		else if (backText.getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			cout << "Going back to Main Menu!" << std::endl;
		}
	}

	// Handle keyboard input for switching modes
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		// Handle up key press (for example, switching menu options or modes)
		cout << "Up key pressed!" << endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		// Handle down key press (for example, switching menu options or modes)
		cout << "Down key pressed!" << endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		// Handle Enter key press (confirm selection)
		cout << "Enter key pressed!" << endl;
	}
}


void PlayMenu::draw()
{
	window.clear();
	window.draw(titleText);
	window.draw(careerModeText);
	window.draw(timeAttackModeText);
	window.draw(botModeText);
	window.draw(backText);
	drawHoverEffects();
	window.display();
}

bool PlayMenu::isModeSelected() const
{
	return isCareerModeSelected() || isTimeAttackModeSelected() || isBotModeSelected();
}

bool PlayMenu::isCareerModeSelected() const
{
	auto mousePos = sf::Mouse::getPosition(window);
	return careerModeText.getGlobalBounds().contains(mousePos.x, mousePos.y);

}

bool PlayMenu::isTimeAttackModeSelected() const
{
	auto mousePos = sf::Mouse::getPosition(window);
	return timeAttackModeText.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

bool PlayMenu::isBotModeSelected() const
{
	auto mousePos = sf::Mouse::getPosition(window);
	return botModeText.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

void PlayMenu::drawHoverEffects()
{
	auto mousePos = sf::Mouse::getPosition(window);

	if (isCareerModeSelected())
	{
		careerModeText.setFillColor(sf::Color::Red);
		careerModeText.setScale(1.2f, 1.2f);
	}
	else
	{
		careerModeText.setFillColor(sf::Color::White);
		careerModeText.setScale(1.f, 1.f);
	}

	if (isTimeAttackModeSelected())
	{
		timeAttackModeText.setFillColor(sf::Color::Red);
		timeAttackModeText.setScale(1.2f, 1.2f);
	}
	else
	{
		timeAttackModeText.setFillColor(sf::Color::White);
		timeAttackModeText.setScale(1.f, 1.f);
	}

	if (isBotModeSelected())
	{
		botModeText.setFillColor(sf::Color::Red);
		botModeText.setScale(1.2f, 1.2f);
	}
	else
	{
		botModeText.setFillColor(sf::Color::White);
		botModeText.setScale(1.f, 1.f);
	}

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
