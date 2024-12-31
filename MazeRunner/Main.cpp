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
            int flag;
            MenuReady();
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
                startGame(); 
                myWindow.display();
            }
            break;
        }
        case 2:
        {
            showGenerationAlgorithms();
            break;
        }
        case 3:
        {
            cout << "Exiting program. Goodbye!" << endl;
            return;
        }
        default:
        {
            cout << "Invalid choice. Please try again." << endl;
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
        cout << "\n========= Maze Generation Algorithms =========\n";
        cout << "1. DFS Maze Algorithm\n";
        cout << "2. Hunt and Kill Algorithm\n";
        cout << "3. Prim's Algorithm\n";
        cout << "4. Origin Shift Algorithm\n";
        cout << "5. Back to Menu\n";
        cout << "==============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Launching DFS Maze Algorithm...\n";
            dfs_maze_animation();
            break;
        case 2:
            cout << "Launching Hunt and Kill Maze Algorithm...\n";
            hunt_and_kill_maze_animation();
            break;
        case 3:
            cout << "Launching Prim's Maze Algorithm...\n";
            prim_maze_animation();
            break;
        case 4:
            cout << "Launching Origin Shift Algorithm...\n";
            origin_shift_animation();
            break;
        case 5:
            cout << "Returning to Algorithms Menu...\n";
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

int main()
{
    showMainMenu();
    return 0;
}