#ifndef GAME_HUD_H
#define GAME_HUD_H

#include <iostream>
#include <string>
#include <allegro5/allegro_font.h> 

#include "Sprite.h"
#include "UnanimatedObjects.h"

class HUD {
private:
    ALLEGRO_FONT* font;
    ALLEGRO_FONT* panel_font;

    // Debuging text 
    bool display_debug_message;
    std::string debug_text;

    // Message text
    bool display_panel_message;
    std::string panel_text;
    SpriteSheet* sprites;

    // Chest message text
    bool display_chest_message;
    std::vector<std::string> chest_message;
    Chest* chest_pointer;

    // Single instance
    static HUD* instance;

public:
    // Global access point
    static HUD& getHUD() {
        if (instance == nullptr) {
            std::cout << "HUD not initialized\n";
            exit(1);
        }
        return *instance;
    }

    static HUD* init();

    void readSpriteSheet();
    void writeDebugText(std::string text);
    void writePanelMessage(std::string message);
    void writeChestMessage(std::vector<std::string> message, Chest* chest);
    void closeChestMessage();
    void draw();
    void deinit();

};

#endif // GAME_HUD_H