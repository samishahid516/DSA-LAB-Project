#include <SFML/Graphics.hpp>
#include <iostream>
#include "User.h"
#include "DatabaseConnection.h"
#include "MazeGame.h"
#include "Grid.h"
#include "Algorithms.h"

void showMainMenu(User* user);
void showAlgorithmsMenu();
void showGenerationAlgorithms();
//void showSolvingAlgorithms();

int main()
{
    DatabaseConnection db;
    if (!db.connect())
    {
        std::cerr << "Failed to connect to the database. Exiting..." << std::endl;
        return 1;
    }

    User* user = new User;
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
            system("cls");
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
                cout << "User registered successfully!" << std::endl;
            }
            else
            {
                cout << "Registration failed. Username might already exist." << std::endl;
            }
            break;
        }
        case 2:
        {
           
            system("cls"); 
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
                cout << "Login successful!" << std::endl;
                isLoggedIn = true;
            }
            else
            {
                cout << "Invalid username or password. Please try again." << std::endl;
            }
            break;
        }
        case 3:
            cout << "Exiting program. Goodbye!" << std::endl;
            delete user;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << std::endl;
        }

    } while (!isLoggedIn);

    showMainMenu(user);

    delete user;
    return 0;
}

void showMainMenu(User* user)
{
    int choice;
    do
    {
        system("cls");

        cout << "\n========= Main Menu =========\n";
        cout << "User: " << user->getUsername() << "\n";
        cout << "User Score: " << user->getScore() << endl;
        cout << "Accout Level: " << user->getAccountLevel() << endl;
        cout << "1. Play\n";
        cout << "2. Time Attack\n";
        cout << "3. Algorithms\n";
        cout << "4. Exit\n";
        cout << "=============================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            MazeGame game;
            game.start(); // Start the game and generate the maze
            break;
        }
        case 2:
        {
            cout << "Time Attack is under development!" << endl;
            break;
        }
        case 3:
        {
            showAlgorithmsMenu();
            break;
        }
        case 4:
        {
            cout << "Exiting program. Goodbye!" << std::endl;
            return;
        }
        default:
        {
            cout << "Invalid choice. Please try again." << endl;
        }
        }
    } while (choice != 4);
}


void showAlgorithmsMenu() 
{
    int choice;
    do 
    {
        system("cls");
        cout << "\n========= Algorithms Menu =========\n";
        cout << "1. Maze Generation Algorithms\n";
        cout << "2. Maze Solving Algorithms\n";
        cout << "3. Back to Main Menu\n";
        cout << "===================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
        case 1:
        {
            showGenerationAlgorithms(); // Call Maze Generation menu
            break;
        }
        case 2:
        {
            //showSolvingAlgorithms(); // Placeholder for solving menu
            //break;
        }
        case 3:
        {

            cout << "Returning to Main Menu...\n";
            return;
        }
        default:
        {
            cout << "Invalid choice. Please try again.\n";
        }
        }
    } while (choice != 3);
}

void showGenerationAlgorithms() 
{
    int choice;
    do 
    {
        system("cls");
        cout << "\n========= Maze Generation Algorithms =========\n";
        cout << "1. DFS Maze Algorithm\n";
        cout << "2. Hunt and Kill Algorithm\n";
        cout << "3. Prim's Algorithm\n";
        cout << "4. Origin Shift Algorithm" << endl;
        cout << "4. Back to Algorithms Menu\n";
        std::cout << "==============================================\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) 
        {
        case 1:
        {
            cout << "Launching DFS Maze Algorithm...\n";
            dfs_maze_animation();
            break;
        }
        case 2:
        {
            cout << "Launching Hunt and Kill Maze Algorithm...\n";
            hunt_and_kill_maze_animation();
            break;
        }
        case 3:
        {
            cout << "Launching Prim's Maze Algorithm...\n";
            prim_maze_animation();
            break;
        }
        case 4:
        {
            cout << "Launching Origin Shift Algorithm...\n";
            origin_shift_animation();
            break;
        }
        case 5:
        {
            cout << "Returning to Algorithms Menu...\n";
            return;
        }
        default:
        {
            cout << "Invalid choice. Please try again.\n";
        }
        }
    } while (choice != 5);
}

