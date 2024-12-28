#include <SFML/Graphics.hpp>
#include <iostream>
#include "User.h"
#include "DatabaseConnection.h"
#include "MainMenu.h"

int main()
{
    // Step 1: Set up database connection
    DatabaseConnection db;
    if (!db.connect())
    {
        cerr << "Failed to connect to the database. Exiting..." << endl;
        return 1;
    }

    User* user = new User;;
    int choice;
    bool isLoggedIn = false;

    do
    {
        cout << "\n========= User Management =========\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "===================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string username, password;
            cout << "\n--- Register ---\n";
            cout << "Enter Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;

            user->setUsername(username);
            user->setPassword(password);

            if (user->registerUser(db))
            {
                cout << "User registered successfully!" << endl;
            }
            else
            {
                cout << "Registration failed. Username might already exist." << endl;
            }
            break;
        }
        case 2:
        {
            string username, password;
            cout << "\n--- Login ---\n";
            cout << "Enter Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;

            user->setUsername(username);
            user->setPassword(password);

            if (user->loginUser(db))
            {
                cout << "Login successful!" << endl;
                isLoggedIn = true;
            }
            else
            {
                cout << "Invalid username or password. Please try again." << endl;
            }
            break;
        }
        case 3:
            cout << "Exiting program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (!isLoggedIn);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Main Menu", sf::Style::Default);
    MainMenu menu(window,user);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            menu.handleInput();
        }

        float deltaTime = clock.restart().asSeconds();
        menu.draw(deltaTime);
    }


    delete user;
    return 0;
}