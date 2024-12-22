#include <cstdlib>
#include <ctime>

#include "Tiles.h"
#include "DrawOrders.h"

void Tiles::readSpriteSheet(){

    // Read the sprite sheet file
    std::string sprite_file = "./sprites/Tileset/Grass.png";

    // Instantiate a new SpriteSheet object
    sprites = new SpriteSheet;
    sprites->readSpriteSheetFile(16, 16, sprite_file);

    // Grabbing the sprites
    std::vector<ALLEGRO_BITMAP*> grass_sprites; // 4 directions

    grass_sprites.push_back(sprites->grabSprite(1, 1));
    grass_sprites.push_back(sprites->grabSprite(0, 5));
    grass_sprites.push_back(sprites->grabSprite(1, 5));
    grass_sprites.push_back(sprites->grabSprite(2, 5));
    grass_sprites.push_back(sprites->grabSprite(3, 5));
    grass_sprites.push_back(sprites->grabSprite(4, 5));
    grass_sprites.push_back(sprites->grabSprite(5, 5));
    grass_sprites.push_back(sprites->grabSprite(0, 6));
    grass_sprites.push_back(sprites->grabSprite(1, 6));
    grass_sprites.push_back(sprites->grabSprite(2, 6));
    grass_sprites.push_back(sprites->grabSprite(3, 6));
    grass_sprites.push_back(sprites->grabSprite(4, 6));
    grass_sprites.push_back(sprites->grabSprite(5, 6));

    sprites->add(std::string("grass"), grass_sprites);
}

void Tiles::gridInitRandom(int n_rows, int n_cols) {

    // Set grid size and initialize to zero 
    grid.resize(n_rows, std::vector<int>(n_cols, 0));

    // Populate some grid cells with one of the 12 variations of grass
    // a grid has 1/24 chance of having each of these types
    std::srand(std::time(nullptr));
    for (int i=0; i < n_cols; i++){
        for (int j=0; j < n_rows; j++){
            int k = std::rand() % 24;
            if (k < 13)
                grid[i][j] = k;
        }
    }
}

void Tiles::draw(){
    // get buffer coordinates
    int buffer_x, buffer_y;
    std::tie(buffer_x, buffer_y) = DrawOrder::getBufferCoordinates();
    // get tiles to plot
    int i_min = buffer_x / sprites->width;
    int i_max = (buffer_x + BUFFER_W) / sprites->width;
    int j_min = buffer_y / sprites->width;
    int j_max = (buffer_y + BUFFER_W) / sprites->width;

    // Ensure we're not out of the domain
    if (i_min < 0) i_min = 0;
    if (j_min < 0) j_min = 0;

    // Assuming a square grid
    int n_rows = grid.size();
    if (i_max >= n_rows) i_max = n_rows - 1;
    if (j_max >= n_rows) j_max = n_rows - 1;

    // loop over them
    for (int i=i_min; i<=i_max; i++) {
        for (int j=j_min; j<=j_max; j++) {
            al_draw_bitmap(sprites->get("grass", grid[i][j]), i*sprites->width - buffer_x, j*sprites->width - buffer_y, 0);
        }
    }
}