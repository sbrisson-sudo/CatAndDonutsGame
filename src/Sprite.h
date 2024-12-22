
#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

/*
This class is meant to contain a sprite sheet (containing several sprites relative to the same object) as well as a convenient way of accessing these sprites through
identifiers via an unordered map object.
*/

class SpriteSheet {
private:
    // Map to store single textures or arrays of textures
    ALLEGRO_BITMAP* _sprite_sheet;
    std::unordered_map<std::string, std::vector<ALLEGRO_BITMAP*>> spriteMap;

public:
    int width, height;

    // Constructor
    SpriteSheet() : _sprite_sheet(nullptr) {}

    // Reading the sprite sheet from a file
    void readSpriteSheetFile(int width, int height, std::string sprite_sheet_path);

    // Grad a sprite from the sprite sheet
    ALLEGRO_BITMAP* grabSprite(int x_start, int y_start);
    ALLEGRO_BITMAP* grabSpritePixel(int x_start, int y_start);

    // Add a single texture
    void add(const std::string& identifier, ALLEGRO_BITMAP* sprite);

    // Add a vector of textures (for animations, etc.)
    void add(const std::string& identifier, std::vector<ALLEGRO_BITMAP*>& stripes);

    // Get a single texture by identifier
    ALLEGRO_BITMAP* get(const std::string& identifier);

    // Get a specific texture from a multi-texture entry
    ALLEGRO_BITMAP* get(const std::string& identifier, size_t index);

    // Print info about number of sprites
    void printInfo();

    // Deinit the bitmaps
    void deinit();
};

#endif // GAME_SPRITE_H

