#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

#include "Cat.h"
#include "Keyboard.h"
#include "DrawOrders.h"

#define N_COLOR_CAT 4
#define CAT_W 32
#define CAT_H 32

SpriteSheet* Cat::shared_sprite_sheet = nullptr;

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

void Cat::update() {

    return;
    // walking = false;
    //
    // if(keyboard.get(ALLEGRO_KEY_LEFT)){
    //     // x -= speed;
    //     direction = LEFT;
    //     walking = true;
    // }    
    // if(keyboard.get(ALLEGRO_KEY_RIGHT)){
    //     // x += speed;
    //     direction = RIGHT;
    //     walking = true;
    // }    
    // if(keyboard.get(ALLEGRO_KEY_UP)){
    //     // y -= speed;
    //     direction = BACK;
    //     walking = true;
    // }
    // if(keyboard.get(ALLEGRO_KEY_DOWN)){
    //     // y += speed;
    //     direction = FRONT;
    //     walking = true;
    // }
}

void Cat::draw() {

    ALLEGRO_BITMAP* bitmap;

    int walk_mode = (frames / 15) % 2;

    if (walking) {
        bitmap = sprites->get("walking", color*N_COLOR_CAT+direction*2+walk_mode);
    } else {
        bitmap = sprites->get("idle", color*N_COLOR_CAT+direction);
    }

    int x_draw = this->x - sprites->width/2;
    int y_draw = this->y - sprites->height;
    int z_order = this->y;

    new DrawOrder(x_draw, y_draw, z_order, bitmap); 
}
