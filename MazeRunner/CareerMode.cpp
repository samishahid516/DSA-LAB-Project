#include "CareerMode.h"
#include "DatabaseConnection.h"


CareerMode::CareerMode(sf::RenderWindow& window, User* user)
	: window(window), user(user), currentLevelIndex(0)
{
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		cerr << "Error loading font!" << endl;
	}

	levelText.setFont(font);
	levelText.setCharacterSize(20);
	levelText.setFillColor(sf::Color::White);
	levelText.setPosition(10.f, 10.f);

	loadLevels();
}

void CareerMode::loadLevels()
{
	for (int i = 1; i <= 10; ++i)
	{
		string filePath = "levels/level" + to_string(i) + ".txt";
		levels.emplace_back(i, filePath, window);
	}
}

bool CareerMode::loadUserProgress(DatabaseConnection& db)
{
	wstring query = L"SELECT CompletedLevels FROM [Users] WHERE Username = N'" +
		wstring(user->getUsername().begin(), user->getUsername().end()) + L"'";

	int maxCompletedLevel = db.executeQuery(query);
	if (maxCompletedLevel == -1)
	{
		cerr << "Error retrieving user progress from database!" << endl;
		return false;
	}
	currentLevelIndex = maxCompletedLevel;
	return true;
}

void CareerMode::playCareerMode()
{
	DatabaseConnection db;

	if (!db.connect())
	{
		cerr << "Failed to connect to the database!" << endl;
		return;
	}

	if (!loadUserProgress(db))
	{
		cerr << "Error loading user progress!" << endl;
		db.disconnect();
		return;
	}

	while (currentLevelIndex < levels.size() && window.isOpen())
	{
		// Draw the maze and UI first
		window.clear();
		levels[currentLevelIndex].drawMaze();
		drawUI();
		window.display();

		// Now handle user input after the maze and UI have been drawn
		levels[currentLevelIndex].handleInput();

		if (levels[currentLevelIndex].isCompleted())
		{
			if (saveLevelProgress(db, levels[currentLevelIndex].getLevelNumber()))
			{
				cout << "Level " << currentLevelIndex + 1 << " saved to database!" << endl;
				if (currentLevelIndex + 1 < levels.size())
				{
					currentLevelIndex++;
				}
				else
				{
					cout << "Congratulations! You have completed all levels!" << endl;
					break;
				}
			}
			else
			{
				cerr << "Failed to save level progress to database!" << endl;
			}
		}
	}

	db.disconnect();
}


void CareerMode::drawUI()
{
	levelText.setString("Level: " + to_string(currentLevelIndex));
	window.draw(levelText);
}

bool CareerMode::saveLevelProgress(DatabaseConnection& db, int levelNumber)
{
	wstring query = L"UPDATE [Users] SET completedlevels = " +
		to_wstring(levelNumber) + L" WHERE Username = N'" +
		wstring(user->getUsername().begin(), user->getUsername().end()) + L"'";

	return db.executeQuery(query); // Assuming `executeQuery` can handle updates as well.
}
