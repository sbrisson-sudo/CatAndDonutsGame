#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <string>
#include <vector>
#include <algorithm> 

#include "HelperTools.h"
#include "Sprite.h"

class Object {
protected:
    int x;
    int y;
    std::string id;
    SpriteSheet* sprites;
    enum Direction direction;

    // Collision related
    int collision_width;
    int collision_height;
    Object* is_facing;

    static std::vector<Object*> objects_list;

public:
    // Constructor
    Object() : x(0), y(0), sprites(nullptr), is_facing(nullptr){
        objects_list.push_back(this);
    };
    Object(int x, int y, std::string id) 
        : x(x), y(y), id(id), sprites(nullptr), is_facing(nullptr){
            objects_list.push_back(this);
        }

    // Copy constructor
    Object(const Object& other) 
        : x(other.x), y(other.y), id(other.id), 
          sprites(other.sprites), collision_width(other.collision_width), collision_height(other.collision_height),is_facing(nullptr){
        objects_list.push_back(this);
    }

    // Virtual destructor
    virtual ~Object() {
        // Remove this from objects_list
        auto it = std::find(objects_list.begin(), objects_list.end(), this);
        if (it != objects_list.end()) {
            objects_list.erase(it);
        }
    }

    // Pure virtual methods to be implemented by derived classes
    virtual void update() = 0;   // Update object state
    virtual void draw() = 0;     // Render the object

    // Check that the object is not colliding with another object 
    bool collision();
    bool checkId(std::string checked_id);

    // Set collision width and height
    void setCollisionWidth(int width) { collision_width = width; };
    void setCollisionHeight(int height) { collision_height = height; };    
    void setDirection(Direction dir) { direction = dir; };

    // Getters for coordinates and dimensions
    int getX() const { return x; };
    int getY() const { return y; };

    void deinit_sprites();

};

#endif // GAME_OBJECT_H