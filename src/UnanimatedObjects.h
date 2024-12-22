#ifndef UNANIMATED_OBJECTS_H
#define UNANIMATED_OBJECTS_H

#include <algorithm>

#include "Object.h"
#include "Sprite.h"


class Donut : public Object {
private : 
    int color;
    static SpriteSheet* sprite_sheet;
    static std::vector<Donut*> donut_list;

public : 
    Donut(int x, int y, int color) : Object(x, y, "donut"), color(color) {
        sprites = sprite_sheet;
        this->setCollisionWidth(sprites->width*3/4);
        this->setCollisionHeight(sprites->height*3/4);
        donut_list.push_back(this);
    };

    ~Donut() {
        auto it = std::find(donut_list.begin(), donut_list.end(), this);
        if (it != donut_list.end()) {
            donut_list.erase(it);
        }
    }

    void update() override;
    void draw() override;

    // void setAsEaten() { eaten = false; };

    static void drawAll();
    static void readSpriteSheet();
    static void deInitSpriteSheet();

    static Donut* getDonut(int i) {
        return donut_list[i];
    }
};

class Bush : public Object {
private : 
    static SpriteSheet* sprite_sheet;

public :

    Bush(int x, int y) : Object(x, y, "bush") {
        sprites = sprite_sheet;
        this->setCollisionWidth(sprites->width);
        this->setCollisionHeight(sprites->height*3/4);
    };

    void update() override;
    void draw() override;

    static void readSpriteSheet();
    static void deInitSpriteSheet();

};

class Chest : public Object {
private : 
    bool opened;
    static SpriteSheet* sprite_sheet;

public :

    Chest(int x, int y) : Object(x, y, "chest"), opened(false) {
        sprites = sprite_sheet;
        this->setCollisionWidth(sprites->width);
        this->setCollisionHeight(sprites->height*3/4);
    };

    void update() override;
    void draw() override;

    static void readSpriteSheet();
    static void deInitSpriteSheet();

    void setOpened(bool _opened) { opened = _opened; };
    bool getOpened() { return opened; };

};



#endif // UNANIMATED_OBJECTS_H