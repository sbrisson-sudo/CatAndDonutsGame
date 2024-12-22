#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <iostream>
#include "allegro5/allegro5.h"

static const int KEY_SEEN = 1;
static const int KEY_RELEASED = 2;

class Keyboard {
private : 
    unsigned char key[ALLEGRO_KEY_MAX];
    // Singleton instance
    static Keyboard* instance;

public : 
    static Keyboard* init();
    void update(ALLEGRO_EVENT* event);
    int get(int key_id);

    // Global access point
    static Keyboard& getKeyboard() {
        if (instance == nullptr) {
            std::cout << "Keyboard not initialized\n";
            exit(1);
        }
        return *instance;
    }
};


#endif // KEYBOARD_H