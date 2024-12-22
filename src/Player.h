#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "Object.h"
#include "HelperTools.h"

class Player : public Object {
private:
    int dx,dy;
    int speed;
    bool walking;
        
public:
    Player(int x, int y) : Object(x, y, "player") {
        speed = 3;
        direction = RIGHT;
        walking = false;
    };

    void update() override;
    void draw() override;
    void readSpriteSheet();
};


#endif // GAME_PLAYER_H