#ifndef GAME_CAT_H
#define GAME_CAT_H

#include "Object.h"
#include "HelperTools.h"
#include "Keyboard.h"
#include "Hud.h"

class Cat : public Object {
private:
    int color;
    bool walking;
    static SpriteSheet* shared_sprite_sheet;
    std::string name;
        
public:
    Cat() : Object() {
        id = "cat";
        color = 0;
        name = "No Name";
        x = BUFFER_W * 3/4;
        y = BUFFER_H * 3/4;    
        direction = RIGHT;
        walking = false;
        sprites = shared_sprite_sheet;
        this->setCollisionWidth(sprites->width*3/4);
        this->setCollisionHeight(sprites->height/2);
    };

    Cat(int x, int y, int color, std::string name)
        : Object(x, y, "cat"), color(color), name(name) {
            direction = FRONT;
            walking = false;
            sprites = shared_sprite_sheet;
            this->setCollisionWidth(sprites->width*3/4);
            this->setCollisionHeight(sprites->height/2);
        }

    void update() override;
    void draw() override;
    static void readSpriteSheet();
    static void deInitSpriteSheet();

    std::string getName() { return name ;};

};

#endif // GAME_CAT_H