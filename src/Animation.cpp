#include <math.h>

#include "HelperTools.h"
#include "Animation.h"
#include "DrawOrders.h"

std::vector<Animation*> Animation::animation_list;

void Animation::drawAllAnimations() {
    // Iterate through the list backwards to safely remove elements
    for (int i = animation_list.size() - 1; i >= 0; i--) {
        Animation* anim = animation_list[i];
        
        if (anim->timer > anim->duration) {
            // Remove from list first
            animation_list.erase(animation_list.begin() + i);
            // Then delete the object
            delete anim;
        } else {
            // Only draw if the animation is still active
            anim->draw();
        }
    }
}

int Animation::GetNbAnimations() {
    return animation_list.size();
}


// Love animation

ALLEGRO_BITMAP* LoveAnimation::bitmap = nullptr;

void LoveAnimation::readSpriteSheet() {
    std::string sprite_file = "./sprites/UI/heart_9x9.png";
    bitmap = al_load_bitmap(sprite_file.c_str());
    must_init(bitmap, sprite_file.c_str());
}

void LoveAnimation::deinitSprite() {
    al_destroy_bitmap(bitmap);
}

void LoveAnimation::draw() {

    if (!bitmap){
        std::cout << "LoveAnimation : sprite not read yet" << std::endl;
        exit(1);
    }

    int x_draw = this->x;
    int y_draw = this->y + std::sin((float)(timer)/8)*3;
    int z_order = this->y + 30;

    new DrawOrder(x_draw, y_draw, z_order, bitmap); 

    // increment timer
    timer ++;
}