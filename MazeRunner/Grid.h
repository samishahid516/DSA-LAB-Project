#ifndef GRID_H
#define GRID_H
#include <stack>
#include <random> 
#include <algorithm>
#include "CONSTANTS.H"
#include "cell.h"
#include "util.h"



class Grid 
{
private:
    Cell cells[GRID_HEIGHT][GRID_WIDTH];
    pair<int, int> highlited_cell;
public:
    Grid();
    void draw(sf::RenderWindow& window);
    void dfs_maze();
    void remove_wall(int x1, int y1, int x2, int y2);
    void set_wall(int x1, int y1, int x2, int y2);
    void dfs_maze_animation(std::stack<node>& st);
    Cell get_cell(int x, int y) const;
    void set_cell_as_visited(int x, int y);
    void hunt_and_kill_maze();
    pair<int, int> hunt_and_kill_maze_animation(pair<int, int> current_cell);
    pair<int, pair<int, bool>> hunt_animation(pair<int, int> current_cell);
    pair<int, int> hunt() const;
    vector <pair<int, int>> get_neighbors(int x, int y, bool visited = false) const;
    void set_highlited_cell(int x, int y);
    void prim_maze();
    bool prim_maze_animation_step(vector<tuple<int, int, int, int>>& walls);
    void init_grid_shift();
    pair<int, int> origin_shift(pair<int, int> origin);

};

#endif // !GRID_H


