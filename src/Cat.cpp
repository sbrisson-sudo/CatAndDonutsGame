#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <cmath>

#include "Cat.h"
#include "Keyboard.h"
#include "DrawOrders.h"

#define N_COLOR_CAT 4
#define CAT_W 32
#define CAT_H 32

SpriteSheet* Cat::shared_sprite_sheet = nullptr;

// Dictionnary of all cats 
unordered_map<std::string, Cat*> Cat::cats_map_by_name = {};

void Cat::readSpriteSheet() {

    if (!shared_sprite_sheet) {
        // Read the sprite sheet file
        std::string sprite_file = "./sprites/Cats/pixel_art_cats.png";

        // Instantiate a new SpriteSheet object
        shared_sprite_sheet = new SpriteSheet;
        shared_sprite_sheet->readSpriteSheetFile(CAT_W, CAT_H, sprite_file);

        // Grabbing the sprites
        std::vector<ALLEGRO_BITMAP*> idle_sprites; // 4 colros * 4 directions 
        std::vector<ALLEGRO_BITMAP*> walking_sprites; // 4 colors * 4 directions x 2 postures

        for (int i_cat=0; i_cat<N_COLOR_CAT; i_cat++){
            
            // Idle sprites (4 directions)
            idle_sprites.push_back(shared_sprite_sheet->grabSprite(0, i_cat));
            idle_sprites.push_back(shared_sprite_sheet->grabSprite(6, i_cat));
            idle_sprites.push_back(shared_sprite_sheet->grabSprite(3, i_cat));
            idle_sprites.push_back(shared_sprite_sheet->grabSprite(9, i_cat));

            shared_sprite_sheet->add(std::string("idle"), idle_sprites);

            // Walking sprites (2*4 directions)
            walking_sprites.push_back(shared_sprite_sheet->grabSprite(1, i_cat));
            walking_sprites.push_back(shared_sprite_sheet->grabSprite(2, i_cat));
            walking_sprites.push_back(shared_sprite_sheet->grabSprite(7, i_cat));
            walking_sprites.push_back(shared_sprite_sheet->grabSprite(8, i_cat));
            walking_sprites.push_back(shared_sprite_sheet->grabSprite(4, i_cat));
            walking_sprites.push_back(shared_sprite_sheet->grabSprite(5, i_cat));
            walking_sprites.push_back(shared_sprite_sheet->grabSprite(10, i_cat));
            walking_sprites.push_back(shared_sprite_sheet->grabSprite(11, i_cat));

            shared_sprite_sheet->add(std::string("walking"), walking_sprites);
        }

    }

    return;
}

void Cat::deInitSpriteSheet(){
    if (shared_sprite_sheet){
        shared_sprite_sheet->deinit();
        shared_sprite_sheet = nullptr;
    }
}

Cat* Cat::getCatByName(std::string name_){
    if (cats_map_by_name.find(name_) == cats_map_by_name.end()){
        std::cout << "Error : no cat registered with name " << name_ << std::endl;
        return nullptr;
    }
    return cats_map_by_name[name_];
}

void Cat::update() {

    double stiffness = 200.0;
    double mass = 1.0;
    double damping_ratio = 1.0;
    double delta_t = 1/60.;

    walking = false;

    // If attached to the player
    if (!attached_list.empty()) {

        // Compute acceleration
        double w = std::sqrt(stiffness / mass); // oscillation frequency
        Vector2D acc(0,0);
        Vector2D AB;
        int i = 0;
        for (Object* obj : attached_list) {
            AB = obj->getPos() - pos;
            // If obj == player -> critically damped spring
            if (obj->checkId("player")){
                acc += AB.unitVector() * (AB.l2Norm() - length_bond_list[i]) * stiffness / mass -  vel * 2*damping_ratio*w;
            } else { // If cat -> spring only if too close
                if (AB.l2Norm() < length_bond_list[i]) {
                    acc += AB.unitVector() * (AB.l2Norm() - length_bond_list[i]) * stiffness / mass;
                }
            }
            i++;
        }

        // Compute new position / vel (Semi-implicit Euler)
        vel += acc * delta_t;

        // Adjust it to account for collision detection
        pos += vel * delta_t;


        // Set if walking
        double speed_walking_threshold = 2.0;
        walking = vel.l2Norm() > speed_walking_threshold;

        // Get walking direction
        if (walking) {
            if (fabs(vel.x) > fabs(vel.y)){
                if (vel.x > 0){
                    direction = RIGHT;
                } else {
                    direction = LEFT;
                }
            } else {
                if (vel.y > 0){
                    direction = FRONT;
                } else {
                    direction = BACK;
                }
            }
        }
    
    }
    return;
}

void Cat::draw() {

    ALLEGRO_BITMAP* bitmap;

    int walk_mode = (frames / 15) % 2;

    // std::cout << color*N_COLOR_CAT+direction*2+walk_mode << std::endl;

    if (walking) {
        bitmap = sprites->get("walking", color*8+direction*2+walk_mode);
    } else {
        bitmap = sprites->get("idle", color*4+direction);
    }

    int x_draw = round(this->pos.x) - sprites->width/2;
    int y_draw = round(this->pos.y) - sprites->height;
    int z_order = round(this->pos.y);

    new DrawOrder(x_draw, y_draw, z_order, bitmap); 
}
