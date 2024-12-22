#include "UnanimatedObjects.h"
#include "DrawOrders.h"

std::vector<Donut*> Donut::donut_list;

SpriteSheet* Donut::sprite_sheet = nullptr;

void Donut::readSpriteSheet() {
    if (!sprite_sheet) {
        std::string sprite_file = "./sprites/Objects/DonutSpriteSheet.png";
        sprite_sheet = new SpriteSheet;
        sprite_sheet->readSpriteSheetFile(14, 10, sprite_file);
        std::vector<ALLEGRO_BITMAP*> donut_sprites;
        for (int i=0; i<8; i++) {
            donut_sprites.push_back(sprite_sheet->grabSprite(i/4, i%4));
        }
        sprite_sheet->add("donuts", donut_sprites);
    }
}

void Donut::deInitSpriteSheet() {
    if (sprite_sheet){
        sprite_sheet->deinit();
        sprite_sheet = nullptr;
    }
}

void Donut::update() {
    return;
}

void Donut::draw() {
    int x_draw = this->x - sprites->width/2;
    int y_draw = this->y - sprites->height;
    int z_order = this->y;
    ALLEGRO_BITMAP* bitmap = sprites->get("donuts", color);
    new DrawOrder(x_draw, y_draw, z_order, bitmap); 
}

void Donut::drawAll() {
    for (auto& donut : donut_list) 
        donut->draw();
}

// Bush

SpriteSheet* Bush::sprite_sheet = nullptr;

void Bush::readSpriteSheet() {
    if (!sprite_sheet) {
        std::string sprite_file = "./sprites/Objects/Basic_Grass_Biom_things.png";
        sprite_sheet = new SpriteSheet;
        sprite_sheet->readSpriteSheetFile(16, 16, sprite_file);
        ALLEGRO_BITMAP* bush_bitmap = sprite_sheet->grabSprite(1, 3);
        sprite_sheet->add("bush", bush_bitmap);
    }
}

void Bush::deInitSpriteSheet() {
    if (sprite_sheet){
        sprite_sheet->deinit();
        sprite_sheet = nullptr;
    }
}

void Bush::update() {
    return;
}

void Bush::draw() {
    int x_draw = this->x - sprites->width/2;
    int y_draw = this->y - sprites->height;
    int z_order = this->y;
    ALLEGRO_BITMAP* bitmap = sprites->get("bush");
    new DrawOrder(x_draw, y_draw, z_order, bitmap); 
}


// CHest

SpriteSheet* Chest::sprite_sheet = nullptr;

void Chest::readSpriteSheet() {
    if (!sprite_sheet) {
        std::string sprite_file = "./sprites/Objects/Chest.png";
        sprite_sheet = new SpriteSheet;
        sprite_sheet->readSpriteSheetFile(16, 20, sprite_file);

        ALLEGRO_BITMAP* closed = sprite_sheet->grabSprite(0, 0);
        sprite_sheet->add("closed", closed);
        ALLEGRO_BITMAP* opened = sprite_sheet->grabSprite(1, 0);
        sprite_sheet->add("opened", opened);
    }
}

void Chest::deInitSpriteSheet() {
    if (sprite_sheet){
        sprite_sheet->deinit();
        sprite_sheet = nullptr;
    }
}

void Chest::update() {
    return;
}

void Chest::draw() {
    int x_draw = this->x - sprites->width/2;
    int y_draw = this->y - sprites->height;
    int z_order = this->y;
    ALLEGRO_BITMAP* bitmap;
    if (opened) {
        bitmap = sprites->get("opened");
    }  else {
        bitmap = sprites->get("closed");
    }
    new DrawOrder(x_draw, y_draw, z_order, bitmap); 
}