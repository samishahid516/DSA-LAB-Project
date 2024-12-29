#include "algorithms.h"

void dfs_maze()
{
    // Font loading (you can do this once outside of the function if it's used multiple times)
    static sf::Font font;
    if (font.getInfo().family == "") // Check if font is already loaded
    {
        if (!font.loadFromFile("./fonts/arial.ttf"))
        {
            puts("ERROR: Font loading failed!");
            return;
        }
    }

    // Setup title
    sf::Text title;
    title.setCharacterSize(30);
    title.setFont(font);
    title.setString("DFS Maze");
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    title.setPosition(WIDTH / 2, 50);

    // Create grid and adjust it based on difficulty level
    Grid grid;  // Creating Grid object

    // Adjust grid properties (e.g., grid size) based on difficulty leve  // Assuming you have a method that adjusts the grid based on difficulty

    grid.dfs_maze();  // Run the DFS algorithm to generate the maze

    // Setup SFML window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "DFS Maze");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Draw the maze
        grid.draw(window);

        // Draw the title
        window.draw(title);
        window.display();
        window.clear();
    }
}



void dfs_maze_animation()
{
    system("cls");
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 g(rd());

    // Load font
    sf::Font font;
    if (!font.loadFromFile("./fonts/arial.ttf")) {
        puts("ERROR ! ");
        return;
    }

    // Setup title text
    sf::Text title;
    title.setCharacterSize(30);
    title.setFont(font);
    title.setString("DFS Maze Animation");
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    title.setPosition(WIDTH / 2, 50);

    // Initialize grid and DFS stack
    Grid grid;
    std::stack<node> st;
    int cell_x = get_random_number(GRID_HEIGHT);
    int cell_y = get_random_number(GRID_WIDTH);
    grid.get_cell(cell_x, cell_y).set_visited();
    std::vector<std::pair<int, int>> neighbors = grid.get_neighbors(cell_x, cell_y);

    // Shuffle neighbors
    std::shuffle(neighbors.begin(), neighbors.end(), g);
    for (auto pos : neighbors) {
        if (!grid.get_cell(pos.first, pos.second).check_if_visited()) {
            grid.get_cell(pos.first, pos.second).set_visited();
            node nd;
            nd.current_x = pos.first;
            nd.current_y = pos.second;
            nd.prev_x = cell_x;
            nd.prev_y = cell_y;
            st.push(nd);
        }
    }

    // Setup SFML window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "DFS Maze Animation");

    // Create a clock to manage the timing of each frame
    sf::Clock clock;
    float frameTime = 0.01f;  // 10 milliseconds per frame

    // Animation loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Check if enough time has passed for the next frame update
        if (clock.getElapsedTime().asSeconds() >= frameTime) {
            grid.dfs_maze_animation(st);  // Update the maze animation
            clock.restart();  // Restart the clock for the next frame

            // Draw the updated grid and title
            grid.draw(window);
            window.draw(title);
            window.display();
            window.clear();
        }
    }
}


void hunt_and_kill_maze() {
    sf::Font font;
    if (!font.loadFromFile("./fonts/arial.ttf")) {
        puts("ERROR ! ");
        return;
    }

    sf::Text title;
    title.setCharacterSize(30);
    title.setFont(font);
    title.setString("Hunt and Kill Maze");
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    title.setPosition(WIDTH / 2, 50);
    Grid grid;
    grid.hunt_and_kill_maze();
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Hunt and Kill Maze");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        grid.draw(window);
        window.draw(title);
        window.display();
        window.clear();
    }
}


void hunt_and_kill_maze_animation() 
{
    system("cls");
    sf::Font font;
    if (!font.loadFromFile("./fonts/arial.ttf")) {
        puts("ERROR ! ");
        return;
    }

    sf::Text title;
    title.setCharacterSize(30);
    title.setFont(font);
    title.setString("Hunt and Kill Maze Animation");
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    title.setPosition(WIDTH / 2, 50);
    Grid grid;
    bool hunt = false, done = false;
    int cell_x = get_random_number(GRID_HEIGHT);
    int cell_y = get_random_number(GRID_WIDTH);
    std::pair<int, int> current_cell = std::make_pair(cell_x, cell_y);
    std::pair<int, int> hunted_cell;
    grid.get_cell(cell_x, cell_y).set_visited();
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Hunt and Kill Maze Animation");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (!done) {
            if (!hunt) {
                grid.set_highlited_cell(-1, -1);
                current_cell = grid.hunt_and_kill_maze_animation(current_cell);
                if (current_cell.first == -1 and current_cell.second == -1) {
                    hunt = true;
                    hunted_cell = std::make_pair(0, 0);
                }
                sf::sleep(sf::milliseconds(10));
            }
            else {
                grid.set_highlited_cell(hunted_cell.first, hunted_cell.second);
                auto res = grid.hunt_animation(hunted_cell);
                if (res.second.second == true) {
                    current_cell = std::make_pair(res.first, res.second.first);
                    hunt = false;
                }
                else if (res.first == -1 and res.second.first == -1) {
                    hunt = false;
                    done = true;
                    grid.set_highlited_cell(-1, -1);
                }
                else {
                    hunted_cell = std::make_pair(res.first, res.second.first);
                }
                sf::sleep(sf::milliseconds(10));
            }
        }
        grid.draw(window);
        window.draw(title);
        window.display();
        window.clear();
    }
}

void prim_maze() {
    sf::Font font;
    if (!font.loadFromFile("./fonts/arial.ttf")) {
        puts("ERROR ! ");
        return;
    }

    sf::Text title;
    title.setCharacterSize(30);
    title.setFont(font);
    title.setString("Prim's Maze");
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    title.setPosition(WIDTH / 2, 50);
    Grid grid;
    grid.prim_maze();
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Prim's Maze");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        grid.draw(window);
        window.draw(title);
        window.display();
        window.clear();
    }
}

void prim_maze_animation() 
{
    system("cls");
    sf::Font font;
    if (!font.loadFromFile("./fonts/arial.ttf")) {
        puts("ERROR ! ");
        return;
    }

    sf::Text title;
    title.setCharacterSize(30);
    title.setFont(font);
    title.setString("Prim's Maze Animation");
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    title.setPosition(WIDTH / 2, 50);
    Grid grid;
    std::vector<std::tuple<int, int, int, int>> walls;

    int start_x = get_random_number(GRID_HEIGHT);
    int start_y = get_random_number(GRID_WIDTH);
    grid.set_cell_as_visited(start_x, start_y);

    if (start_x > 0) walls.push_back(std::make_tuple(start_x, start_y, start_x - 1, start_y));
    if (start_x < GRID_HEIGHT - 1) walls.push_back(std::make_tuple(start_x, start_y, start_x + 1, start_y));
    if (start_y > 0) walls.push_back(std::make_tuple(start_x, start_y, start_x, start_y - 1));
    if (start_y < GRID_WIDTH - 1) walls.push_back(std::make_tuple(start_x, start_y, start_x, start_y + 1));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Prim's Maze Animation");

    bool animation_completed = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!animation_completed) {
            animation_completed = !grid.prim_maze_animation_step(walls);
        }

        grid.draw(window);
        window.draw(title);
        window.display();
        window.clear();

        sf::sleep(sf::milliseconds(10));
    }
}



void origin_shift_animation() 
{
    system("cls");
    sf::Font font;
    if (!font.loadFromFile("./fonts/arial.ttf")) {
        puts("ERROR ! ");
        return;
    }
    sf::Text title;
    title.setCharacterSize(30);
    title.setFont(font);
    title.setString("Origin Shift Maze Animation");
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    title.setPosition(WIDTH / 2, 50);
    Grid grid;

    grid.init_grid_shift();
    std::pair<int, int> shift_cell = std::make_pair(GRID_HEIGHT - 1, GRID_WIDTH - 1);
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Origin Shift Maze Animation");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        grid.draw(window);
        shift_cell = grid.origin_shift(shift_cell);
        window.draw(title);
        window.display();
        window.clear();
        sf::sleep(sf::milliseconds(10));
    }
}


void origin_shift() {
    sf::Font font;
    if (!font.loadFromFile("./fonts/arial.ttf")) {
        puts("ERROR ! ");
        return;
    }
    sf::Text title;
    title.setCharacterSize(30);
    title.setFont(font);
    title.setString("Origin Shift Maze");
    title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);
    title.setPosition(WIDTH / 2, 50);
    Grid grid;
    grid.init_grid_shift();
    std::pair<int, int> shift_cell = std::make_pair(GRID_HEIGHT - 1, GRID_WIDTH - 1);
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Origin Shift Maze");
    for (int i = 0; i < 100000; i++) {
        shift_cell = grid.origin_shift(shift_cell);
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        grid.draw(window);
        shift_cell = grid.origin_shift(shift_cell);
        window.draw(title);
        window.display();
        window.clear();
        sf::sleep(sf::milliseconds(50));
    }
}