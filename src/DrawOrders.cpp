#include <utility>

#include "DrawOrders.h"
#include "HelperTools.h"

// Draw orders list
std::vector<DrawOrder*> DrawOrder::drawOrders;

// Buffer's coordinates
int DrawOrder::buffer_x = 0;
int DrawOrder::buffer_y = 0;

void DrawOrder::execute_all() {
    // Sort the draw orders by z_order (ascending)
    std::sort(drawOrders.begin(), drawOrders.end(),
        [](DrawOrder* a, DrawOrder* b) {
            return a->z_order < b->z_order;
        });

    // Execute the draw calls in sorted order
    for (DrawOrder* order : drawOrders) {
        al_draw_bitmap(order->bitmap, order->x_draw - buffer_x, order->y_draw - buffer_y, 0);
    }
}

void DrawOrder::reset_all() {
    // Delete all DrawOrder objects
    for (DrawOrder* order : drawOrders) {
        delete order;
    }
    drawOrders.clear();
}

void DrawOrder::set_buffer_coordinates(int x, int y){

    // Ensure it respects world boundaries
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > WORLD_W - BUFFER_W) x = WORLD_W - BUFFER_W;
    if (y > WORLD_H - BUFFER_H) y = WORLD_H - BUFFER_H; 

    DrawOrder::buffer_x = x;
    DrawOrder::buffer_y = y;
}

std::pair<int, int> DrawOrder::getBufferCoordinates(){
    return std::make_pair(buffer_x, buffer_y);
}