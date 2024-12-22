#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

#include "Sprite.h"
#include "HelperTools.h"

#include <allegro5/allegro_image.h>


// Construction : reading sprite sheet 
void SpriteSheet::readSpriteSheetFile(int width, int height, std::string sprite_sheet_path) {
    this->width = width; 
    this->height = height;
    const char * path = sprite_sheet_path.c_str();

    _sprite_sheet = al_load_bitmap(path);
    must_init(_sprite_sheet, path);
}   

// // Get a Sprite from the sprite sheet using the pixel coordinates
// ALLEGRO_BITMAP* SpriteSheet::grabSpriteAbs(int x_start, int y_start) {
//     ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(_sprite_sheet, x_start, y_start, width, height);
//     return sprite;
// }


// Get a Sprite from the sprite sheet using the sprite grid coordinates
ALLEGRO_BITMAP* SpriteSheet::grabSprite(int row, int col) {
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(_sprite_sheet, row*width, col*height, width, height);
    return sprite;
}

// Get a Sprite from the sprite sheet using the pixel grid coordinates
ALLEGRO_BITMAP* SpriteSheet::grabSpritePixel(int x_start, int y_start) {
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(_sprite_sheet, x_start, y_start, width, height);
    return sprite;
}



// Add a single texture
void SpriteSheet::add(const std::string& identifier, ALLEGRO_BITMAP* sprite) {
    spriteMap[identifier] = {sprite};
}

// Add a vector of textures (for animations, etc.)
void SpriteSheet::add(const std::string& identifier, std::vector<ALLEGRO_BITMAP*>& sprites) {
    spriteMap[identifier] = sprites;
}

// Get a single texture by identifier
ALLEGRO_BITMAP* SpriteSheet::get(const std::string& identifier) {
    if (spriteMap.find(identifier) == spriteMap.end() || spriteMap[identifier].empty()) {
        throw std::out_of_range("Identifier not found: " + identifier);
    }
    return spriteMap[identifier][0];
}

// Get a specific texture from a multi-texture entry
ALLEGRO_BITMAP* SpriteSheet::get(const std::string& identifier, size_t index) {
    if (spriteMap.find(identifier) == spriteMap.end()) {
        throw std::out_of_range("Identifier not found: " + identifier);
    }
    if (index >= spriteMap[identifier].size()) {
        throw std::out_of_range("Index out of range for identifier: " + identifier);
    }
    return spriteMap[identifier][index];
}

// Deinit the bitmaps
void SpriteSheet::deinit() {
    // Loop on the sprites
    for (auto& it: spriteMap) {
        for (auto & bitmap : it.second ) {
            al_destroy_bitmap(bitmap);
        }
    }
    // Destroy the sprite sheet bitmap
    al_destroy_bitmap(_sprite_sheet);
}

// Print info 
void SpriteSheet::printInfo(){
    for (auto& it: spriteMap) {
        std::cout << "Identifier " << it.first << " -> " << it.second.size() << " sprites\n";
    }
}

