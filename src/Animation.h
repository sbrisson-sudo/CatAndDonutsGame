#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "Sprite.h"
#include "Object.h"

class Animation {

protected:
    Object* attached_object = nullptr;
    int timer;
    int duration; // duration in frames

    static std::vector<Animation*> animation_list;

public:
    Animation(Object* obj, int duration) : attached_object(obj), timer(0), duration(duration){
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
    LoveAnimation(Object* object) : Animation(object, 3*30) {};
    static void readSpriteSheet();
    static void deinitSprite();
    void draw() override;
};



#endif // ANIMATIONS_H