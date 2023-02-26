/* Your code here! */
#pragma once

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include <vector>

using namespace std;
using namespace cs225;
class SquareMaze{
public:
    int w, h, finish, Size, X, Y;
    SquareMaze();
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    PNG* drawMaze() const;
    PNG* drawMazeWithSolution();
    DisjointSets Sets;
    vector<bool> right;
    vector<bool> down;
    //vector<pair<bool, bool>> wall;
};
