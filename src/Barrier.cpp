#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Barrier.h"
#include "DrawOrders.h"


SpriteSheet* Barrier::shared_sprite_sheet = nullptr;

void Barrier::readSpriteSheet() {

    if (!shared_sprite_sheet) {
        // Read the sprite sheet file
        std::string sprite_file = "./sprites/Tileset/Fences.png";
        shared_sprite_sheet = new SpriteSheet;
        shared_sprite_sheet->readSpriteSheetFile(16, 16, sprite_file);

        // Grabbing the sprites
        std::vector<ALLEGRO_BITMAP*> barrier_sprites;

        // Read in the enum order : 
        // NONE
        barrier_sprites.push_back(shared_sprite_sheet->grabSprite(0,3));
        // TOP
        barrier_sprites.push_back(shared_sprite_sheet->grabSprite(0,2));
        // RIGHT
        barrier_sprites.push_back(shared_sprite_sheet->grabSprite(1,3));
        // BOTTOM
        barrier_sprites.push_back(shared_sprite_sheet->grabSprite(0,0));
        // LEFT
        barrier_sprites.push_back(shared_sprite_sheet->grabSprite(3,3));
        // TOP_BOTTOM
        barrier_sprites.push_back(shared_sprite_sheet->grabSprite(0,1));
        // RIGHT_LEFT
        barrier_sprites.push_back(shared_sprite_sheet->grabSprite(2,3));
        // TOP_LEFT
        barrier_sprites.push_back(shared_sprite_sheet->grabSprite(3,2));
        // TOP_RIGHT
        barrier_sprites.push_back(shared_sprite_sheet->grabSprite(1,2));
        // BOTTOM_LEFT
        barrier_sprites.push_back(shared_sprite_sheet->grabSprite(3,0));
        // BOTTOM_RIGHT
        barrier_sprites.push_back(shared_sprite_sheet->grabSprite(1,0));
        // TOP_RIGHT_LEFT
        barrier_sprites.push_back(shared_sprite_sheet->grabSprite(2,2));
        // RIGHT_TOP_BOTTOM
        barrier_sprites.push_back(shared_sprite_sheet->grabSprite(1,1));
        //BOTTOM_RIGHT_LEFT
        barrier_sprites.push_back(shared_sprite_sheet->grabSprite(2,0));
        // LEFT_TOP_BOTTOM
        barrier_sprites.push_back(shared_sprite_sheet->grabSprite(3,1));
        // ALL
        barrier_sprites.push_back(shared_sprite_sheet->grabSprite(2,1));

        shared_sprite_sheet->add(std::string("barrier"), barrier_sprites);
    }
}

void Barrier::deInitSpriteSheet(){
    if (shared_sprite_sheet){
        shared_sprite_sheet->deinit();
        shared_sprite_sheet = nullptr;
    }
}

void Barrier::update() {
    return;
}

void Barrier::draw() {
    ALLEGRO_BITMAP* bitmap;
    bitmap = sprites->get("barrier", connectivity);
    int x_draw = this->x - sprites->width/2;
    int y_draw = this->y - sprites->height;
    int z_order = this->y;
    new DrawOrder(x_draw, y_draw, z_order, bitmap); 
}

std::vector<Barrier> Barrier::readBarrierFile(const std::string& file_name) {

    std::ifstream file(file_name);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open the file: " + file_name);
    }

    std::vector<Barrier> barriers;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int x, y, conn;
        if (!(iss >> x >> y >> conn)) {
            throw std::runtime_error("Error parsing line: " + line);
        }

        barriers.emplace_back(x, y, static_cast<Connectivity>(conn));
    }

    return barriers;
}