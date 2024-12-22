#ifndef BARRIER_H
#define BARRIER_H

#include "Object.h"

enum Connectivity {
    B_NONE,
    B_TOP,
    B_RIGHT,
    B_BOTTOM,
    B_LEFT,
    B_TOP_BOTTOM,
    B_RIGHT_LEFT,
    B_TOP_LEFT,
    B_TOP_RIGHT,
    B_BOTTOM_LEFT,
    B_BOTTOM_RIGHT,
    B_TOP_RIGHT_LEFT,
    B_RIGHT_TOP_BOTTOM,
    B_BOTTOM_RIGHT_LEFT,
    B_LEFT_TOP_BOTTOM,
    B_ALL
};

class Barrier : public Object {
private:
    Connectivity connectivity;
    static SpriteSheet* shared_sprite_sheet;

public :
    Barrier(int x, int y, Connectivity connectivity) : Object(x,y,"barrier"), connectivity(connectivity) {
        if (!shared_sprite_sheet){
            std::cout << "Barrier : sprite sheet not initialized, exiting...";
            exit(1);
        }
        sprites = shared_sprite_sheet;
        this->setCollisionWidth(sprites->width/2);
        this->setCollisionHeight(sprites->height/2);
    };

    void update() override;
    void draw() override;
    static void readSpriteSheet();
    static void deInitSpriteSheet();

    // Read barrier list from file
    static std::vector<Barrier> readBarrierFile(const std::string& in_file);
};

#endif // BARRIER_H