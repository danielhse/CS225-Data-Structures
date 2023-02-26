/* Your code here! */
#include "maze.h"
#include "dsets.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <stack>
#include <queue>
#include <sys/time.h>

using namespace std;

SquareMaze::SquareMaze(){
    w = 0;
    h = 0;
}

void SquareMaze::makeMaze(int width, int height){
    w = width;
    h = height;
    Size = w * h;
    Sets.addelements(Size);
    if (Size == 0)
        return;
    for(int i = 0; i < Size; i++) {
        right.push_back(1);
        down.push_back(1);
    }
    
    //int i = 0;
    while (Sets.size(0) < Size) { //not connected but acyclic
        X = rand() % w; 
        Y = rand() % h;
        if(rand() % 2 == true){ 
            if(X != w - 1){
                if(Sets.find(X + Y * w) != Sets.find(X + Y * w + 1)){
                    setWall(X, Y, 0, 0);  
                    Sets.setunion(X + Y * w, X + Y * w + 1);
                    //i++;
                }
            }
        }
        else{ 
            if(Y != h - 1){
                if(Sets.find(X + Y * w) != Sets.find(X + (Y + 1) * w)){
                    setWall(X, Y, 1, 0);
                    Sets.setunion(X + Y * w, X + (Y + 1) * w);
                    //i++;
                }
            }
        }
    }
    
    /**
    while(Sets.size(0) < Size){  //connected but not acyclic
        int x = rand() % w;
        int y = rand() % h;
        if(rand() % 2 != true){
            if(y != h - 1){
                if(Sets.find(x + y * w) != Sets.find(x + (y + 1) * w)){
                    setWall(x, y, 1, 0);
                    Sets.setunion(x + y * w, x + (y + 1) * w);
                }
            }
        }
        else{
            if(x != w - 1){
                if(Sets.find(x + y * w) != Sets.find(x + y * w + 1)){
                    setWall(x, y, 0, 0);  
                    Sets.setunion(x + y * w, x + y * w + 1);
                }
            }
        }
    }
    */
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
    if (dir == 0)
        return !right[x + y * w];
    else if (dir == 1)
        return !down[x + y * w];
    else if (dir == 2){
        if (x != 0)
            return !right[x + y * w - 1];
        else 
            return 0;
    }
    else if (dir == 3) {
        if ( y != 0)
            return !down[x + (y - 1) * w];
        else
            return 0;
    }
    return 0;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if (dir == true)
        down[x + y * w] = exists;
    if (dir == false)
        right[x + y * w] = exists;
}

vector<int> SquareMaze::solveMaze(){
    int x, y, curr;
    //vector<int> distance;
    vector<int> out;
    queue<int> bfs;
    vector<pair<int, int>> p_d(w * h); 
    //distance.push_back(0);
    //path.push_back(0);
    bfs.push(0);
    int lp = w * (h - 1);
    Size = w * h;
    for (int i = 1; i < Size; i++) {
        p_d[i].first = -1;
        p_d[i].second = 0;
    }

    while (bfs.empty() == false) {
        curr = bfs.front();
        bfs.pop();
        if (canTravel(curr % w, curr / w, 0) == 1) {
            if(p_d[curr + 1].first == -1) {
                bfs.push(curr + 1);
                p_d[curr + 1].first = curr;
                p_d[curr + 1].second = p_d[curr].second + 1;
            }
        }
        if (canTravel(curr % w, curr / w, 1) == 1) {
            if(p_d[curr + w].first == -1) {
                bfs.push(curr + w);
                p_d[curr + w].first = curr;
                p_d[curr + w].second = p_d[curr].second + 1;
            }
        }
        if (canTravel(curr % w, curr / w, 2) == 1) {
            if(p_d[curr - 1].first == -1) {
                bfs.push(curr - 1);
                p_d[curr - 1].first = curr;
                p_d[curr - 1].second = p_d[curr].second + 1;
            }
        }
        if (canTravel(curr % w, curr / w, 3) == 1) {
            if(p_d[curr - w].first == -1) {
                bfs.push(curr - w);
                p_d[curr - w].first = curr;
                p_d[curr - w].second = p_d[curr].second + 1;
            }
        }
    }

    for (int j = 0; j < w; j++) {
        if (p_d[w * (h - 1) + j].second > p_d[lp].second)
            lp = w * (h - 1) + j;
    }
    
    finish = lp;
    curr = finish; 
    while (curr != false) {
        if (p_d[curr].first == curr - 1)
            out.push_back(0);
        if (p_d[curr].first == curr - w)
            out.push_back(1);
        if (p_d[curr].first == curr + 1)
            out.push_back(2);
        if (p_d[curr].first == curr + w) 
            out.push_back(3);
        curr = p_d[curr].first;
    }
    reverse(out.begin(), out.end());
    return out;
}

PNG* SquareMaze::drawMaze() const{
    PNG* done = new PNG(w * 10 + 1, h * 10 + 1);
    for(int x = 10; x < w * 10 + 1; x++){
        HSLAPixel& cp = done->getPixel(x, 0);
        cp.l = 0; 
    }
    for(int y = 0; y < h * 10 + 1; y++){
        HSLAPixel& cp = done->getPixel(0, y);
        cp.l = 0;  
    }
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            if(right[x + y * w] == 1){
                for(int k = 0; k < 11; k++){
                HSLAPixel& cp = done->getPixel((x + 1) * 10, y * 10 + k);
                cp.l = 0;  
                }
            }
            if(down[x + y * w] == 1){
                for(int k = 0; k < 11; k++){
                    HSLAPixel& cp = done->getPixel(x * 10 + k, (y + 1) * 10);
                    cp.l = 0;  
                }
            }
        }
    }
    return done;
    delete done;
}

PNG* SquareMaze::drawMazeWithSolution(){
    PNG* done = drawMaze();
    vector<int> out = solveMaze();
    pair<int, int> curr(5, 5);
    for (int x = 1; x < 10; x++) {
        HSLAPixel & curr_p = done->getPixel((finish % w) * 10 + x, ((finish / h) + 1) * 10);
        curr_p.l = 1.0;
    }
    for (size_t i = 0; i < out.size(); i++){
        if (out[i] == 0) {
            for (int j = 0; j < 11; j++) {
                HSLAPixel & curr_p = done->getPixel(curr.first + j, curr.second);
                curr_p.h = 0.0;
                curr_p.s = 1.0;
                curr_p.l = 0.5;
                curr_p.a = 1.0;
            }
            curr.first = curr.first + 10;
        }
        else if (out[i] == 1) {
            for (int j = 0; j < 11; j++) {
                HSLAPixel & curr_p = done->getPixel(curr.first, curr.second + j);
                curr_p.h = 0.0;
                curr_p.s = 1.0;
                curr_p.l = 0.5;
                curr_p.a = 1.0;
            }
            curr.second = curr.second + 10;
        }
        else if (out[i] == 2) {
            for (int j = 0; j < 11; j++) {
                HSLAPixel & curr_p = done->getPixel(curr.first - j, curr.second);
                curr_p.h = 0.0;
                curr_p.s = 1.0;
                curr_p.l = 0.5;
                curr_p.a = 1.0;
            }
            curr.first = curr.first - 10;
        }
        else if (out[i] == 3) {
            for (int j = 0; j < 11; j++) {
                HSLAPixel & curr_p = done->getPixel(curr.first, curr.second - j);
                curr_p.h = 0.0;
                curr_p.s = 1.0;
                curr_p.l = 0.5;
                curr_p.a = 1.0;
            }
            curr.second = curr.second - 10;
        } 
    }
    return done;
}
