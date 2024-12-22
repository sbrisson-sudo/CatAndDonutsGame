#include <fmt/core.h>

#include "Object.h"
#include "Hud.h"

std::vector<Object*> Object::objects_list;

void Object::deinit_sprites() {
    sprites->deinit();
}

bool Object::collision() {

    // HUD& hud = HUD::getHUD();

    int this_W = this->collision_width;
    int this_H = this->collision_height;

    // hud.writeDebugText(fmt::format("Number of objects : {}", objects_list.size()));
    // hud.writeDebugText(fmt::format("Collision box size : {}", this_W, this_H));
    
    for (auto& obj : objects_list) {

        if (obj == this) continue;

        int obj_W = obj->collision_width;
        int obj_H = obj->collision_height;

        if ((x + this_W/2) < (obj->x - obj_W/2))  continue;
        if ((x - this_W/2) > (obj->x + obj_W/2))  continue;
        if (y  < (obj->y - obj_H))  continue;
        if ((y - this_H)  > obj->y)  continue;

        // Inside the bounding box = collision
        is_facing = obj;
        return true;
    }
    return false;
}

bool Object::checkId(std::string checked_id){
    return this->id == checked_id;
}

