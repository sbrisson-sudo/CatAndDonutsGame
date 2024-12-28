#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <fmt/core.h>


#include "Player.h"
#include "Keyboard.h"
#include "DrawOrders.h"
#include "Hud.h"
#include "Animation.h"
#include "Cat.h"
#include "UnanimatedObjects.h"


void Player::readSpriteSheet() {

    // Read the sprite sheet file
    std::string sprite_file = "./sprites/Characters/pokemon_character_32_brown_hair.png";
    const int player_W = 32;
    const int player_H = 32;

    // // test that files exists
    // bool file_exist = std::filesystem::exists(sprite_file);
    // std::cout << sprite_file << " file exists = " << file_exist << std::endl;

    // Instantiate a new SpriteSheet object
    sprites = new SpriteSheet;

    sprites->readSpriteSheetFile(player_W, player_H, sprite_file);
    // Grabbing the sprites
    std::vector<ALLEGRO_BITMAP*> idle_sprites; // 4 directions
    std::vector<ALLEGRO_BITMAP*> walking_sprites; // 4 directions x 2 postures

    idle_sprites.push_back(sprites->grabSprite(2, 1));
    idle_sprites.push_back(sprites->grabSprite(0, 0));
    idle_sprites.push_back(sprites->grabSprite(1, 0));
    idle_sprites.push_back(sprites->grabSprite(0, 2));
    sprites->add(std::string("idle"), idle_sprites);

    walking_sprites.push_back(sprites->grabSprite(2, 2));
    walking_sprites.push_back(sprites->grabSprite(2, 3));
    walking_sprites.push_back(sprites->grabSprite(2, 0));
    walking_sprites.push_back(sprites->grabSprite(1, 3));
    walking_sprites.push_back(sprites->grabSprite(1, 1));
    walking_sprites.push_back(sprites->grabSprite(1, 2));
    walking_sprites.push_back(sprites->grabSprite(0, 1));
    walking_sprites.push_back(sprites->grabSprite(0, 3));
    sprites->add(std::string("walking"), walking_sprites);

    this->setCollisionWidth(18);
    this->setCollisionHeight(13);
}

void Player::update() {

    // Get keyboard and hud
    Keyboard& keyboard = Keyboard::getKeyboard();
    HUD& hud = HUD::getHUD();

    walking = false;
    dx = 0;
    dy = 0;

    if(keyboard.get(ALLEGRO_KEY_LEFT)){
        dx = -speed;
        x -= speed;
        direction = LEFT;
        walking = true;
    }    
    if(keyboard.get(ALLEGRO_KEY_RIGHT)){
        dx = speed;
        x += speed;
        direction = RIGHT;
        walking = true;
    }    
    if(keyboard.get(ALLEGRO_KEY_UP)){
        dy = -speed;
        y -= speed;
        direction = BACK;
        walking = true;
    }
    if(keyboard.get(ALLEGRO_KEY_DOWN)){
        dy = speed;
        y += speed;
        direction = FRONT;
        walking = true;
    }

    // Check collision with world boundaries
    if(x < sprites->width/2)
        x = sprites->width/2;
    if(y < sprites->height)
        y = sprites->height;

    if(x > WORLD_W - sprites->width/2)
        x = WORLD_W - sprites->width/2;
    if(y > WORLD_H)
        y = WORLD_H;

    // If moving : reset the is_facing pointer
    if ( (dx != 0) || (dy != 0)){
        // hud.writeDebugText("Moving !!");
        is_facing = nullptr;
    }
    
    // Check collision with other objects
    if (this->collision()){
        walking = false;
        x -= dx;
        y -= dy;
    }

    // Interactions with cats
    if ((this->is_facing) && (this->is_facing->checkId("cat"))){
        
        Cat* cat = dynamic_cast<Cat*>(this->is_facing);

        hud.writePanelMessage(fmt::format("You have found {} ! Press SPACE to pet her", cat->getName()));

        // Changing cat direction
        Direction cat_direction;
        switch (direction)
        {
        case FRONT:
            cat_direction = BACK;
            break;
        case BACK:
            cat_direction = FRONT;
            break;
        case RIGHT:
            cat_direction = LEFT;
            break;
        case LEFT:
            cat_direction = RIGHT;
            break;
        }
        this->is_facing->setDirection(cat_direction);

        // Adding the pet animation
        if(keyboard.get(ALLEGRO_KEY_SPACE)){

            // hud.writeDebugText("Petting the cat...");
            if (Animation::GetNbAnimations() == 0)
                new LoveAnimation(this->is_facing->getX()-5, this->is_facing->getY() - 32);


            if (!muis_pet && (cat->getName() == "Muis"))
                muis_pet = true;

            if (!nala_pet && (cat->getName() == "Nala"))
                nala_pet = true;

        }
    }

    // Interaction with donuts
    if ((this->is_facing) && (this->is_facing->checkId("donut"))){

        Donut* donut = dynamic_cast<Donut*>(this->is_facing);
        hud.writePanelMessage("Press SPACE to eat this delicious donut");
        
        if(keyboard.get(ALLEGRO_KEY_SPACE)){
            // hud.writeDebugText("EAting the donut..");
            delete donut;
            this->is_facing = nullptr;
            donuts_eaten++;
        }
    }

    // Intraction with chest
    if ((this->is_facing) && (this->is_facing->checkId("chest"))){
        Chest* chest = dynamic_cast<Chest*>(this->is_facing);

        hud.writePanelMessage("Press SPACE to open the chest");
        
        if(!chest->getOpened() && keyboard.get(ALLEGRO_KEY_SPACE)){
            chest_opened = true;
            // hud.writeDebugText("Opening the chest");
            chest->setOpened(true);
            std::vector<std::string> chest_message = {
                "Merry Christmas sweetie !!", 
                "I have tried to make a game as sweet as you <3", 
                "Can't wait to share a lot more in the year to come",
                "                                     Your sweet mouse."
                };
            hud.writeChestMessage(chest_message, chest);
        }
    }



    // Update coordinates of buffer
    DrawOrder::set_buffer_coordinates(x - BUFFER_W/2, y - BUFFER_H/2);
}

void Player::draw() {

    ALLEGRO_BITMAP* bitmap;

    int walk_mode = (frames / 15) % 2;
    if (walking) {
        bitmap = sprites->get("walking", direction*2+walk_mode);
    } else {
        bitmap = sprites->get("idle", direction);
    }

    int x_draw = this->x - sprites->width/2;
    int y_draw = this->y - sprites->height;
    int z_order = this->y;

    new DrawOrder(x_draw, y_draw, z_order, bitmap); 
}