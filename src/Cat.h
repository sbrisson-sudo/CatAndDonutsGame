#ifndef GAME_CAT_H
#define GAME_CAT_H

#include <vector>
#include <unordered_map>

#include "Object.h"
#include "HelperTools.h"
#include "Keyboard.h"
#include "Hud.h"
#include "Vector2d.h"

class Cat : public Object {
private:
    int color;
    bool walking;
    static SpriteSheet* shared_sprite_sheet;
    std::string name;

    // Additionnal vectors to handle physics
    Vector2D vel = Vector2D(0,0);
    // Other objects it can be attached to 
    vector<Object*> attached_list;
    vector<double> length_bond_list;

    // Map of all the cats by their name for easy access
    static unordered_map<std::string, Cat*> cats_map_by_name;
        
public:
    Cat(int x, int y, int color, std::string name)
        : Object(x, y, "cat"), color(color), name(name) {
            direction = FRONT;
            walking = false;
            sprites = shared_sprite_sheet;
            this->setCollisionWidth(sprites->width*3/4);
            this->setCollisionHeight(sprites->height/2);
            cats_map_by_name[name] = this;
        }

    void update() override;
    void draw() override;
    void add_attached_object(Object* obj, double l0) { attached_list.push_back(obj); length_bond_list.push_back(l0); };
    static void readSpriteSheet();
    static void deInitSpriteSheet();

    static Cat* getCatByName(std::string name_);

    std::string getName() { return name ;};

};

#endif // GAME_CAT_H