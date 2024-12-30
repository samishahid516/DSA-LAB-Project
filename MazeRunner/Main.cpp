#include <SFML/Graphics.hpp>
#include <iostream>
#include "Grid.h"
#include "Algorithms.h"
#include "Controller.h"

void showGenerationAlgorithms();

void showMainMenu()
{
    int choice;
    do
    {
        system("cls");

        
        cout << "\n========= Main Menu =========\n";
        cout << "1. Play\n";
        cout << "2. Algorithms\n";
        cout << "3. Exit\n";
        cout << "=============================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Call the game setup and start
            int flag;
            MenuReady();  // Initialize the game assets (menu textures, etc.)
            srand(time(NULL));
            myWindow.setFramerateLimit(10);

            while (myWindow.isOpen())
            {
                while (myWindow.pollEvent(eve))
                {
                    if (eve.type == sf::Event::Closed)
                    {
                        myWindow.close();
                    }
                }
                myWindow.clear();
                startGame();  // Main game logic starts here
                myWindow.display();
            }
            break;
        }
        case 2:
        {
            showGenerationAlgorithms();
            break;
        }
        case 4:
        {
            std::cout << "Exiting program. Goodbye!" << std::endl;
            return;
        }
        default:
        {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
        }
    } while (choice != 4);
}

void showGenerationAlgorithms()
{
    int choice;
    do
    {
        system("cls");
        std::cout << "\n========= Maze Generation Algorithms =========\n";
        std::cout << "1. DFS Maze Algorithm\n";
        std::cout << "2. Hunt and Kill Algorithm\n";
        std::cout << "3. Prim's Algorithm\n";
        std::cout << "4. Origin Shift Algorithm\n";
        std::cout << "5. Back to Algorithms Menu\n";
        std::cout << "==============================================\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "Launching DFS Maze Algorithm...\n";
            dfs_maze_animation();
            break;
        case 2:
            std::cout << "Launching Hunt and Kill Maze Algorithm...\n";
            hunt_and_kill_maze_animation();
            break;
        case 3:
            std::cout << "Launching Prim's Maze Algorithm...\n";
            prim_maze_animation();
            break;
        case 4:
            std::cout << "Launching Origin Shift Algorithm...\n";
            origin_shift_animation();
            break;
        case 5:
            std::cout << "Returning to Algorithms Menu...\n";
            return;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

int main()
{
    showMainMenu();
    return 0;
}