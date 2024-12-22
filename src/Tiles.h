#ifndef TILES_H
#define TILES_H

#include "HelperTools.h"
#include "Sprite.h"

class Tiles {
private:
    SpriteSheet* sprites;
    std::vector<std::vector<int>> grid;

public:
    void readSpriteSheet();
    void gridInitRandom(int Nx, int Ny);
    void draw();
};

#endif // TILES_H