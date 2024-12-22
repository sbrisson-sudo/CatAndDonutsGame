#ifndef DRAW_ORDERS_H
#define DRAW_ORDERS_H

#include <vector>
#include <algorithm>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

class DrawOrder {
private : 
    int x_draw, y_draw;
    int z_order;
    ALLEGRO_BITMAP* bitmap;

    // TO store all the draw orders asked for one frame
    static std::vector<DrawOrder*> drawOrders;

    // To store the coordinates of the current buffer
    // Relative to the player's position
    static int buffer_x, buffer_y;

public :
    DrawOrder(int x_draw, int y_draw, int z_order, ALLEGRO_BITMAP* bitmap)
        : x_draw(x_draw), y_draw(y_draw), z_order(z_order), bitmap(bitmap) {
            drawOrders.push_back(this);
        }

    static void set_buffer_coordinates(int x, int y);
    static std::pair<int, int> getBufferCoordinates();
    static void execute_all();
    static void reset_all();
};


#endif // DRAW_ORDERS_H