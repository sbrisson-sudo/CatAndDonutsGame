#ifndef GAME_HELPERS_H
#define GAME_HELPERS_H

#include <iostream>

// Shared variables
extern long int frames;

extern const int BUFFER_W;
extern const int BUFFER_H;

extern const int WORLD_W;
extern const int WORLD_H;

// Objectives 
extern bool muis_pet;
extern bool nala_pet;
extern bool chest_opened;
extern int donuts_eaten;

inline void must_init(bool test, const char *description)
{
    if(test) return;

    std::cout << "Couldn't initialize " << description << "\n";
    exit(1);
}

enum Direction {
    FRONT,
    BACK,
    RIGHT,
    LEFT
};


#endif //GAME_HELPERS_H
