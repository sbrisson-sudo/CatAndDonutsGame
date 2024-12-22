#include "Keyboard.h"

Keyboard* Keyboard::instance = nullptr;

Keyboard* Keyboard::init() {
    instance = new Keyboard();
    memset(instance->key, 0, sizeof(instance->key));
    return instance;
}

int Keyboard::get(int key_id) {
    return key[key_id];
}

void Keyboard::update(ALLEGRO_EVENT* event) {
    switch(event->type)
    {
        case ALLEGRO_EVENT_TIMER:
            for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event->keyboard.keycode] &= KEY_RELEASED;
            break;
    }
}