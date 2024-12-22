#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "Sprite.h"

class Animation {

protected:
    int x,y ;  
    int timer;
    int duration; // duration in frames

    static std::vector<Animation*> animation_list;

public:
    Animation() : x(0), y(0), timer(0), duration(0){
        animation_list.push_back(this);
    }
    Animation(int x, int y, int duration) : x(x), y(y), timer(0), duration(duration){
        animation_list.push_back(this);
    }

    virtual ~Animation() = default;

    virtual void draw() = 0;
    static void drawAllAnimations();
    static int GetNbAnimations();

};

class LoveAnimation : public Animation {
private:
    static ALLEGRO_BITMAP* bitmap;

public:
    LoveAnimation(int x, int y) : Animation(x, y, 3*30) {};
    static void readSpriteSheet();
    static void deinitSprite();
    void draw() override;
};



#endif // ANIMATIONS_H