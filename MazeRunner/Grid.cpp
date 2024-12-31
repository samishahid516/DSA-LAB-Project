#include "grid.h"


Grid::Grid() 
{
    srand(time(0));
    highlited_cell = make_pair(-1, -1);
}

void Grid::set_highlited_cell(int x, int y) 
{
    highlited_cell = make_pair(y, x);
}
void Grid::draw(sf::RenderWindow& window) 
{
    float pos_x = WIDTH / 2 - GRID_WIDTH * SQUARE_SIZE / 2, pos_y = HEIGHT / 2 - GRID_HEIGHT * SQUARE_SIZE / 2 - 50;
    for (int i = 0; i < GRID_HEIGHT; i++) 
    {
        for (int j = 0; j < GRID_WIDTH; j++) 
        {
            if (i == highlited_cell.first and j == highlited_cell.second) cells[i][j].draw(window, sf::Vector2f(pos_x + SQUARE_SIZE * i, pos_y + SQUARE_SIZE * j), true);
            else cells[i][j].draw(window, sf::Vector2f(pos_x + SQUARE_SIZE * i, pos_y + SQUARE_SIZE * j));
        }
    }

}


void Grid::remove_wall(int x1, int y1, int x2, int y2) 
{
    if (x1 == x2 and y1 == y2 + 1) 
    {
        cells[y1][x1].remove_left_wall();
        cells[y2][x2].remove_right_wall();
    }
    else if (x1 == x2 and y1 == y2 - 1) 
    {
        cells[y1][x1].remove_right_wall();
        cells[y2][x2].remove_left_wall();
    }
    else if (x1 == x2 + 1 and y1 == y2) 
    {
        cells[y1][x1].remove_top_wall();
        cells[y2][x2].remove_bottom_wall();
    }
    else if (x1 == x2 - 1 and y1 == y2) 
    {
        cells[y1][x1].remove_bottom_wall();
        cells[y2][x2].remove_top_wall();
    }
}
void Grid::set_wall(int x1, int y1, int x2, int y2) 
{
    if (x1 == x2 and y1 == y2 + 1) 
    {
        cells[y1][x1].add_left_wall();
        cells[y2][x2].add_right_wall();
    }
    else if (x1 == x2 and y1 == y2 - 1) 
    {
        cells[y1][x1].add_right_wall();
        cells[y2][x2].add_left_wall();
    }
    else if (x1 == x2 + 1 and y1 == y2) 
    {
        cells[y1][x1].add_top_wall();
        cells[y2][x2].add_bottom_wall();
    }
    else if (x1 == x2 - 1 and y1 == y2) 
    {
        cells[y1][x1].add_bottom_wall();
        cells[y2][x2].add_top_wall();
    }
}

void Grid::dfs_maze()
{
    random_device rd;
    mt19937 g(rd());

    // Step 1: Start from a random cell and mark it as visited
    stack<node> st;
    int cell_x = get_random_number(GRID_HEIGHT);
    int cell_y = get_random_number(GRID_WIDTH);
    cells[cell_x][cell_y].set_visited();

    // Step 2: Get and shuffle neighbors of the starting cell
    vector <pair<int, int>> neigbors = get_neighbors(cell_x, cell_y);
    shuffle(neigbors.begin(), neigbors.end(), g);

    // Step 3: Add unvisited neighbors to the stack
    for (auto pos : neigbors) 
    {
        if (!cells[pos.first][pos.second].check_if_visited()) 
        {
            cells[pos.first][pos.second].set_visited();
            node nd = { pos.first, pos.second, cell_x, cell_y };
            st.push(nd);
        }
    }

    // Step 4: Continue processing the stack until it's empty
    while (!st.empty()) 
    {
        node current_node = st.top(); st.pop();

        // Step 5: Remove the wall between the current and previous cell
        remove_wall(current_node.current_x, current_node.current_y, current_node.prev_x, current_node.prev_y);

        // Step 6: Get and shuffle neighbors of the current cell
        vector <pair<int, int>> neigbors = get_neighbors(current_node.current_x, current_node.current_y);
        shuffle(neigbors.begin(), neigbors.end(), g);

        // Step 7: Add unvisited neighbors to the stack
        for (auto pos : neigbors)
        {
            if (!cells[pos.first][pos.second].check_if_visited()) 
            {
                cells[pos.first][pos.second].set_visited();
                node nd = { pos.first, pos.second, current_node.current_x, current_node.current_y };
                st.push(nd);
            }
        }
    }
}


void Grid::dfs_maze_animation(stack<node>& st) 
{
    if (st.empty()) return;
    random_device rd;
    mt19937 g(rd());
    node current_node = st.top(); st.pop();
    remove_wall(current_node.current_x, current_node.current_y, current_node.prev_x, current_node.prev_y);
    vector <pair<int, int>>  neigbors = get_neighbors(current_node.current_x, current_node.current_y);
    // Shuffle the vector 
    shuffle(neigbors.begin(), neigbors.end(), g);
    for (auto pos : neigbors) 
    {
        if (!cells[pos.first][pos.second].check_if_visited()) 
        {
            cells[pos.first][pos.second].set_visited();
            node nd;
            nd.current_x = pos.first;
            nd.current_y = pos.second;
            nd.prev_x = current_node.current_x;
            nd.prev_y = current_node.current_y;
            st.push(nd);
        }
    }
}

Cell Grid::get_cell(int x, int y)const 
{
    return cells[x][y];
}

void Grid::set_cell_as_visited(int x, int y) 
{
    cells[x][y].set_visited();
}

pair<int, int> Grid::hunt() const 
{
    for (int i = 0; i < GRID_HEIGHT; i++) 
    {
        for (int j = 0; j < GRID_WIDTH; j++) 
        {
            if (!cells[i][j].check_if_visited()) 
            {
                vector <pair<int, int>>  neigbors = get_neighbors(i, j, true);
                for (auto neigbor : neigbors) 
                {
                    if (cells[neigbor.first][neigbor.second].check_if_visited()) 
                    {
                        return neigbor;
                    }
                }
            }
        }
    }
    return make_pair(-1, -1);
}

void Grid::hunt_and_kill_maze()
{
    bool hunted = true;    // Flag to indicate if hunting is still ongoing
    bool dead_end = false; // Flag to indicate if the current cell is a dead-end
    int cell_x = get_random_number(GRID_HEIGHT);
    int cell_y = get_random_number(GRID_WIDTH);
    pair<int, int> current_cell = make_pair(cell_x, cell_y);

    // Step 1: Start with a random cell and mark it as visited
    cells[cell_x][cell_y].set_visited();
    vector <pair<int, int>> neigbors = get_neighbors(cell_x, cell_y);
    pair<int, int> next_cell = neigbors[get_random_number(neigbors.size())];

    // Step 2: Loop until hunting is complete
    while (hunted) 
    {
        // Step 3: Explore the maze from the current cell until a dead-end is found
        while (!dead_end) 
        {
            vector <pair<int, int>> neigbors = get_neighbors(next_cell.first, next_cell.second);
            cells[next_cell.first][next_cell.second].set_visited();
            remove_wall(next_cell.first, next_cell.second, current_cell.first, current_cell.second);
            current_cell = next_cell;

            // Step 4: Move to a random neighbor or mark as dead-end if no neighbors exist
            if (neigbors.size() != 0)
                next_cell = neigbors[get_random_number(neigbors.size())];
            else
                dead_end = true; // Mark dead-end if no neighbors are left
        }

        // Step 5: Hunt for the next unvisited cell
        next_cell = hunt();

        // Step 6: If no unvisited cell is found, stop hunting
        if (next_cell.first == -1 && next_cell.second == -1) {
            hunted = false;
            break;
        }

        // Step 7: Reset for the next hunt
        dead_end = false;
    }
}

vector<pair<int, int>> Grid::get_neighbors(int x, int y, bool  visited) const 
{
    vector<pair<int, int>> res;
    if (visited) {
        if (x > 0) 
        {
            res.push_back(make_pair(x - 1, y));
        }
        if (x < GRID_HEIGHT - 1) 
        {
            res.push_back(make_pair(x + 1, y));
        }
        if (y > 0) 
        {
            res.push_back(make_pair(x, y - 1));
        }
        if (y < GRID_WIDTH - 1) 
        {
            res.push_back(make_pair(x, y + 1));
        }
    }
    else 
    {
        if (x > 0 and !get_cell(x - 1, y).check_if_visited()) 
        {
            res.push_back(make_pair(x - 1, y));
        }
        if (x < GRID_HEIGHT - 1 and !get_cell(x + 1, y).check_if_visited())
        {
            res.push_back(make_pair(x + 1, y));
        }
        if (y > 0 and !get_cell(x, y - 1).check_if_visited()) 
        {
            res.push_back(make_pair(x, y - 1));
        }
        if (y < GRID_WIDTH - 1 and !get_cell(x, y + 1).check_if_visited()) 
        {
            res.push_back(make_pair(x, y + 1));
        }
    }
    return res;
}


pair<int, int> Grid::hunt_and_kill_maze_animation(pair<int, int> current_cell) 
{
    vector <pair<int, int>>  neigbors = get_neighbors(current_cell.first, current_cell.second);
    if (neigbors.size() == 0) 
        return make_pair(-1, -1);
    pair<int, int> next_cell = neigbors[get_random_number(neigbors.size())];
    remove_wall(next_cell.first, next_cell.second, current_cell.first, current_cell.second);
    cells[next_cell.first][next_cell.second].set_visited();
    return next_cell;

}
pair<int, pair<int, bool>> Grid::hunt_animation(pair<int, int> current_cell) 
{
    if (!cells[current_cell.first][current_cell.second].check_if_visited()) 
    {
        vector <pair<int, int>>  neigbors = get_neighbors(current_cell.first, current_cell.second, true);
        for (auto neigbor : neigbors) 
        {
            if (cells[neigbor.first][neigbor.second].check_if_visited()) {
                return make_pair(neigbor.first, make_pair(neigbor.second, true));
            }
        }
    }
    if (current_cell.second < GRID_WIDTH - 1) 
    {
        return make_pair(current_cell.first, make_pair(current_cell.second + 1, false));
    }
    else if (current_cell.first < GRID_HEIGHT - 1) 
    {
        return make_pair(current_cell.first + 1, make_pair(0, false));
    }
    else 
    {
        return make_pair(-1, make_pair(-1, false));
    }

}

void Grid::prim_maze() 
{
    random_device rd;
    mt19937 g(rd());

    // Step 1: Start with a random cell
    int start_x = get_random_number(GRID_HEIGHT);
    int start_y = get_random_number(GRID_WIDTH);
    cells[start_x][start_y].set_visited();

    // Step 2: Add the walls of the cell to the list of walls
    vector<tuple<int, int, int, int>> walls;
    if (start_x > 0) 
        walls.push_back(make_tuple(start_x, start_y, start_x - 1, start_y));
    if (start_x < GRID_HEIGHT - 1) 
        walls.push_back(make_tuple(start_x, start_y, start_x + 1, start_y));
    if (start_y > 0) 
        walls.push_back(make_tuple(start_x, start_y, start_x, start_y - 1));
    if (start_y < GRID_WIDTH - 1) 
        walls.push_back(make_tuple(start_x, start_y, start_x, start_y + 1));

    // Step 3: Loop until there are no walls left in the list
    while (!walls.empty()) 
    {
        // Step 4: Randomly select a wall from the list
        shuffle(walls.begin(), walls.end(), g);
        auto wall = walls.back();
        walls.pop_back();

        int x1 = get<0>(wall);
        int y1 = get<1>(wall);
        int x2 = get<2>(wall);
        int y2 = get<3>(wall);

        // Step 5: If only one of the two cells divided by the wall is visited
        if (cells[x2][y2].check_if_visited() != cells[x1][y1].check_if_visited()) 
        {
            // Remove the wall between the two cells
            remove_wall(x1, y1, x2, y2);

            // Mark the unvisited cell as part of the maze
            cells[x2][y2].set_visited();

            // Add the neighboring walls of the cell to the list
            if (x2 > 0 && !cells[x2 - 1][y2].check_if_visited())
                walls.push_back(make_tuple(x2, y2, x2 - 1, y2));
            if (x2 < GRID_HEIGHT - 1 && !cells[x2 + 1][y2].check_if_visited()) 
                walls.push_back(make_tuple(x2, y2, x2 + 1, y2));
            if (y2 > 0 && !cells[x2][y2 - 1].check_if_visited())
                walls.push_back(make_tuple(x2, y2, x2, y2 - 1));
            if (y2 < GRID_WIDTH - 1 && !cells[x2][y2 + 1].check_if_visited()) 
                walls.push_back(make_tuple(x2, y2, x2, y2 + 1));
        }
    }
}

bool Grid::prim_maze_animation_step(vector<tuple<int, int, int, int>>& walls) 
{
    if (walls.empty()) return false;

    random_device rd;
    mt19937 g(rd());
    shuffle(walls.begin(), walls.end(), g);

    auto wall = walls.back();
    walls.pop_back();

    int x1 = get<0>(wall);
    int y1 = get<1>(wall);
    int x2 = get<2>(wall);
    int y2 = get<3>(wall);

    if (cells[x2][y2].check_if_visited() != cells[x1][y1].check_if_visited()) 
    {
        remove_wall(x1, y1, x2, y2);
        cells[x2][y2].set_visited();

        if (x2 > 0 && !cells[x2 - 1][y2].check_if_visited()) 
            walls.push_back(make_tuple(x2, y2, x2 - 1, y2));
        if (x2 < GRID_HEIGHT - 1 && !cells[x2 + 1][y2].check_if_visited()) 
            walls.push_back(make_tuple(x2, y2, x2 + 1, y2));
        if (y2 > 0 && !cells[x2][y2 - 1].check_if_visited()) 
            walls.push_back(make_tuple(x2, y2, x2, y2 - 1));
        if (y2 < GRID_WIDTH - 1 && !cells[x2][y2 + 1].check_if_visited()) 
            walls.push_back(make_tuple(x2, y2, x2, y2 + 1));

        return true;
    }

    return true;
}

void Grid::init_grid_shift() 
{
    for (int i = 0; i < GRID_HEIGHT; i++) 
    {
        for (int j = 0; j < GRID_WIDTH - 1; j++) 
        {
            cells[i][j].set_direction(i, j + 1);
            remove_wall(i, j, i, j + 1);
        }
    }
    for (int i = 0; i < GRID_HEIGHT - 1; i++) 
    {
        cells[i][GRID_WIDTH - 1].set_direction(i + 1, GRID_WIDTH - 1);
        remove_wall(i, GRID_WIDTH - 1, i + 1, GRID_WIDTH - 1);
    }
}

pair<int, int> Grid::origin_shift(pair<int, int> origin)
{
    // Step 1: Get the neighbors of the current origin cell
    vector <pair<int, int>> neigbors = get_neighbors(origin.first, origin.second, true);

    // Step 2: Randomly select the next cell from the neighbors
    pair<int, int> next_cell = neigbors[get_random_number(neigbors.size())];

    // Step 3: Highlight the selected next cell
    set_highlited_cell(next_cell.first, next_cell.second);

    // Step 4: If the next cell already has a direction set (i.e., it has been visited previously), remove the wall
    if (cells[next_cell.first][next_cell.second].get_direction().first != -1 &&
        cells[next_cell.first][next_cell.second].get_direction().second != -1)
    {
        set_wall(next_cell.first, next_cell.second,
            cells[next_cell.first][next_cell.second].get_direction().first,
            cells[next_cell.first][next_cell.second].get_direction().second);
        cells[next_cell.first][next_cell.second].set_direction(-1, -1); // Reset direction
    }

    // Step 5: Set the direction of the origin cell to the next cell
    cells[origin.first][origin.second].set_direction(next_cell.first, next_cell.second);

    // Step 6: Remove the wall between the origin cell and the next cell to create a path
    remove_wall(origin.first, origin.second, next_cell.first, next_cell.second);

    // Step 7: Return the next cell
    return next_cell;
}
