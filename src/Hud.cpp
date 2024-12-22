#include <fmt/core.h>
#include <string>

#include "allegro5/allegro_ttf.h"

#include "Hud.h"
#include "HelperTools.h"
#include "Keyboard.h"


// Singleton instance declaration
HUD* HUD::instance = nullptr;

HUD* HUD::init(){
    instance = new HUD;

    // Base font 
    instance->font = al_create_builtin_font();
    must_init(instance->font, "font");

    // Custom font
    instance->panel_font = al_load_font("./fonts/8x8-pixel.ttf", 10, 0);
    must_init(instance->panel_font, "Custom font");


    instance->display_debug_message = false;
    instance->display_panel_message = false;
    instance->display_chest_message = false;
    return instance;
}

void HUD::deinit(){
    al_destroy_font(font);
    al_destroy_font(panel_font);
}

void HUD::writeDebugText(std::string text){
    display_debug_message = true;
    debug_text = text;
}

void HUD::writePanelMessage(std::string text){
    display_panel_message = true;
    panel_text = text;
}

void HUD::writeChestMessage(std::vector<std::string> message, Chest* chest){
    display_chest_message = true;
    chest_message = message;
    chest_pointer = chest;
}

void HUD::closeChestMessage(){
    display_chest_message = false;
    chest_pointer->setOpened(false);
}

void HUD::draw() {

    Keyboard& keyboard = Keyboard::getKeyboard();

    // Debug text area
    if (display_debug_message){
        const char * debug_text_c = debug_text.c_str();
        al_draw_text(
            font,
            al_map_rgb_f(1,1,1),
            1, 1,
            0,
            debug_text_c
        );
    }

    // Message in Panel
    if (display_panel_message){

        // Panel width (exclusing the sides)
        int panel_width = 18;
        int panel_unit_w = sprites->width;

        // Left side
        al_draw_bitmap(sprites->get("panel_top_left"), panel_unit_w, BUFFER_H - 4*panel_unit_w, 0);
        al_draw_bitmap(sprites->get("panel_center_left"), panel_unit_w, BUFFER_H - 3*panel_unit_w, 0);
        al_draw_bitmap(sprites->get("panel_bottom_left"), panel_unit_w, BUFFER_H - 2*panel_unit_w, 0);
        // Center part
        for (int i=0; i<panel_width; i++){
            al_draw_bitmap(sprites->get("panel_top"), panel_unit_w*(i+2), BUFFER_H - 4*panel_unit_w, 0);
            al_draw_bitmap(sprites->get("panel_center"), panel_unit_w*(i+2), BUFFER_H - 3*panel_unit_w, 0);
            al_draw_bitmap(sprites->get("panel_bottom"), panel_unit_w*(i+2), BUFFER_H - 2*panel_unit_w, 0);
        }
        // RIght side
        al_draw_bitmap(sprites->get("panel_top_right"), panel_unit_w*(panel_width+2), BUFFER_H - 4*panel_unit_w, 0);
        al_draw_bitmap(sprites->get("panel_center_right"), panel_unit_w*(panel_width+2), BUFFER_H - 3*panel_unit_w, 0);
        al_draw_bitmap(sprites->get("panel_bottom_right"), panel_unit_w*(panel_width+2), BUFFER_H - 2*panel_unit_w, 0);

        // Message on top of it
        const char * panel_text_c = panel_text.c_str();
        al_draw_text(
            panel_font,
            al_map_rgb_f(1,1,1),
            2*panel_unit_w, BUFFER_H-3*panel_unit_w+2,
            ALLEGRO_ALIGN_INTEGER,
            panel_text_c
        );
    }

    // Objectives
    al_draw_text( panel_font, al_map_rgb_f(0,0,0), 16, 16, ALLEGRO_ALIGN_INTEGER, "Objectives : ");
    if (muis_pet){
        al_draw_text( panel_font, al_map_rgb_f(0,0,0), 16, 16+12*1, ALLEGRO_ALIGN_INTEGER, " - Pet Muis (done)");
    } else {
        al_draw_text( panel_font, al_map_rgb_f(0,0,0), 16, 16+12*1, ALLEGRO_ALIGN_INTEGER, " - Pet Muis");
    }

    if (nala_pet){
        al_draw_text( panel_font, al_map_rgb_f(0,0,0), 16, 16+12*2, ALLEGRO_ALIGN_INTEGER, " - Pet Nala (done)");
    } else {
        al_draw_text( panel_font, al_map_rgb_f(0,0,0), 16, 16+12*2, ALLEGRO_ALIGN_INTEGER, " - Pet Nala");
    }
    
    if (donuts_eaten < 8) {
        std::string donut_string = fmt::format(" - Eat the 8 donuts ({}/8)", donuts_eaten);
        al_draw_text( panel_font, al_map_rgb_f(0,0,0), 16, 16+12*3, ALLEGRO_ALIGN_INTEGER, donut_string.c_str());
    } else {
        al_draw_text( panel_font, al_map_rgb_f(0,0,0), 16, 16+12*3, ALLEGRO_ALIGN_INTEGER, " - Eat the 8 donuts (done)");
    }

    if (chest_opened) {
        al_draw_text( panel_font, al_map_rgb_f(0,0,0), 16, 16+12*4, ALLEGRO_ALIGN_INTEGER, " - Open the chest (done)");
    } else {
        al_draw_text( panel_font, al_map_rgb_f(0,0,0), 16, 16+12*4, ALLEGRO_ALIGN_INTEGER, " - Open the chest");
    }

    // Chest message
    if (display_chest_message) {

        // Draw the panel
        int panel_width = 18;
        int panel_height = chest_message.size()+1;
        int panel_unit_w = sprites->width;

        // Left side
        al_draw_bitmap(sprites->get("panel_top_left"), panel_unit_w, panel_unit_w, 0);
        for (int j=0; j<panel_height; j++)
            al_draw_bitmap(sprites->get("panel_center_left"), panel_unit_w, panel_unit_w*(2+j), 0);
        al_draw_bitmap(sprites->get("panel_bottom_left"), panel_unit_w, panel_unit_w*(2+panel_height), 0);

        // Center part
        for (int i=0; i<panel_width; i++){
            al_draw_bitmap(sprites->get("panel_top"), panel_unit_w*(i+2), panel_unit_w, 0);
            for (int j=0; j<panel_height; j++)
                al_draw_bitmap(sprites->get("panel_center"), panel_unit_w*(i+2), panel_unit_w*(2+j), 0);
            al_draw_bitmap(sprites->get("panel_bottom"), panel_unit_w*(i+2), panel_unit_w*(2+panel_height), 0);
        }
        // RIght side
        al_draw_bitmap(sprites->get("panel_top_right"), panel_unit_w*(panel_width+2), panel_unit_w, 0);
        for (int j=0; j<panel_height; j++)
            al_draw_bitmap(sprites->get("panel_center_right"), panel_unit_w*(panel_width+2), panel_unit_w*(2+j), 0);
        al_draw_bitmap(sprites->get("panel_bottom_right"), panel_unit_w*(panel_width+2), panel_unit_w*(2+panel_height), 0);

        // Message on top of it
        int i = 0;
        for (auto & line : chest_message) {
            al_draw_text(
                panel_font,
                al_map_rgb_f(1,1,1),
                2*panel_unit_w, panel_unit_w*(2+i),
                ALLEGRO_ALIGN_INTEGER,
                line.c_str()
            );
            i++;
        }

        // Last time : press to close
        al_draw_text(
            panel_font,
            al_map_rgb_f(1,1,1),
            2*panel_unit_w, panel_unit_w*(2+panel_height-1),
            ALLEGRO_ALIGN_INTEGER,
            "Press ENTER to close"
        );

        // Closing the chest if space is pressed
        if (keyboard.get(ALLEGRO_KEY_ENTER)){
            this->closeChestMessage();
        }

    }

    // Reinit booleans
    display_debug_message = false;
    display_panel_message = false;
}

// Read the sprite sheet file for UI
void HUD::readSpriteSheet(){

    std::string sprite_file = "./sprites/UI/pixel_ui_pack.png";
    sprites = new SpriteSheet;
    sprites->readSpriteSheetFile(16, 16, sprite_file);

    // Messsage panel
    ALLEGRO_BITMAP* panel_top_left = sprites->grabSprite(0, 0);
    ALLEGRO_BITMAP* panel_top = sprites->grabSprite(1, 0);
    ALLEGRO_BITMAP* panel_top_right = sprites->grabSprite(2, 0);
    ALLEGRO_BITMAP* panel_center_left = sprites->grabSprite(0, 1);
    ALLEGRO_BITMAP* panel_center = sprites->grabSprite(1, 1);
    ALLEGRO_BITMAP* panel_center_right = sprites->grabSprite(2, 1);
    ALLEGRO_BITMAP* panel_bottom_left = sprites->grabSprite(0, 2);
    ALLEGRO_BITMAP* panel_bottom = sprites->grabSprite(1, 2);
    ALLEGRO_BITMAP* panel_bottom_right = sprites->grabSprite(2, 2);

    sprites->add("panel_top_left", panel_top_left);
    sprites->add("panel_top", panel_top);
    sprites->add("panel_top_right", panel_top_right);
    sprites->add("panel_center_left", panel_center_left);
    sprites->add("panel_center", panel_center);
    sprites->add("panel_center_right", panel_center_right);
    sprites->add("panel_bottom_left", panel_bottom_left);
    sprites->add("panel_bottom", panel_bottom);
    sprites->add("panel_bottom_right", panel_bottom_right);

    // Objectices panel
    // ALLEGRO_BITMAP* objectives_top_left = sprites->grabSprite(3, 0);
    // ALLEGRO_BITMAP* objectives_top = sprites->grabSprite(4, 0);
    // ALLEGRO_BITMAP* objectives_top_right = sprites->grabSprite(5, 0);
    // ALLEGRO_BITMAP* objectives_center_left = sprites->grabSprite(3, 1);
    // ALLEGRO_BITMAP* objectives_center = sprites->grabSprite(4, 1);
    // ALLEGRO_BITMAP* objectives_center_right = sprites->grabSprite(5, 1);
    // ALLEGRO_BITMAP* objectives_bottom_left = sprites->grabSprite(3, 2);
    // ALLEGRO_BITMAP* objectives_bottom = sprites->grabSprite(4, 2);
    // ALLEGRO_BITMAP* objectives_bottom_right = sprites->grabSprite(5, 2);

    // ALLEGRO_BITMAP* objectives_top_left = sprites->grabSprite(6, 0);
    // ALLEGRO_BITMAP* objectives_top = sprites->grabSprite(7, 0);
    // ALLEGRO_BITMAP* objectives_top_right = sprites->grabSprite(8, 0);
    // ALLEGRO_BITMAP* objectives_center_left = sprites->grabSprite(6, 1);
    // ALLEGRO_BITMAP* objectives_center = sprites->grabSprite(7, 1);
    // ALLEGRO_BITMAP* objectives_center_right = sprites->grabSprite(8, 1);
    // ALLEGRO_BITMAP* objectives_bottom_left = sprites->grabSprite(6, 2);
    // ALLEGRO_BITMAP* objectives_bottom = sprites->grabSprite(7, 2);
    // ALLEGRO_BITMAP* objectives_bottom_right = sprites->grabSprite(8, 2);

    // sprites->add("objectives_top_left", objectives_top_left);
    // sprites->add("objectives_top", objectives_top);
    // sprites->add("objectives_top_right", objectives_top_right);
    // sprites->add("objectives_center_left", objectives_center_left);
    // sprites->add("objectives_center", objectives_center);
    // sprites->add("objectives_center_right", objectives_center_right);
    // sprites->add("objectives_bottom_left", objectives_bottom_left);
    // sprites->add("objectives_bottom", objectives_bottom);
    // sprites->add("objectives_bottom_right", objectives_bottom_right);

    // Checked mark 
    ALLEGRO_BITMAP* mark_unchecked = sprites->grabSprite(3, 4);
    ALLEGRO_BITMAP* mark_checked = sprites->grabSprite(4, 4);

    sprites->add("mark_unchecked", mark_unchecked);
    sprites->add("mark_checked", mark_checked);
}