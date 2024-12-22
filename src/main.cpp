#include <iostream>
#include <fmt/core.h>
#include <string>

#include "HelperTools.h"
#include "Hud.h"
#include "Keyboard.h"
#include "DrawOrders.h"
#include "Player.h"
#include "Cat.h"
#include "Tiles.h"
#include "Barrier.h"
#include "Animation.h"
#include "UnanimatedObjects.h"

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "allegro5/allegro_ttf.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

// -- global variables ---

long int frames;
const int BUFFER_W=352;
const int BUFFER_H=352;

const int WORLD_W = 1536;
const int WORLD_H = 1536;

// --- display ---

const int  DISP_SCALE=2;
const int  DISP_W = BUFFER_W * DISP_SCALE;
const int  DISP_H = BUFFER_H * DISP_SCALE;

// -- objectives --
bool muis_pet = false;
bool nala_pet = false;
bool chest_opened = false;
int donuts_eaten = 0;

ALLEGRO_DISPLAY* disp;
ALLEGRO_BITMAP* buffer;

void disp_init()
{
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

    // // Set bitmap flags to disable linear filtering
    // al_set_new_bitmap_flags(0); // This disables all filtering
    // al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);

    disp = al_create_display(DISP_W, DISP_H);
    must_init(disp, "display");

    buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
    must_init(buffer, "bitmap buffer");
}

void disp_deinit()
{
    al_destroy_bitmap(buffer);
    al_destroy_display(disp);
}

void disp_pre_draw()
{
    al_set_target_bitmap(buffer);
}

void disp_post_draw()
{
    al_set_target_backbuffer(disp);
    al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);

    al_flip_display();
}

// --- main ---

int main()
{

    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer");

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    disp_init();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    must_init(al_init_image_addon(), "image addon");

    must_init(al_init_font_addon(), "font addon");
    must_init(al_init_ttf_addon(), "ttf addon");

    Keyboard* keyboard = Keyboard::init();
    
    HUD* hud = HUD::init();
    hud->readSpriteSheet();

    Player player(96, 1304);
    // Player player(1426, 264);
  
    player.readSpriteSheet();

    Cat::readSpriteSheet();
    Cat* cat1 = new Cat(416, 1064, 2, "Muis");
    Cat* cat2 = new Cat(656, 824, 3, "Nala");

    Donut::readSpriteSheet();

    new Donut(416, 1224, 0);
    new Donut(1376, 1384, 1);
    new Donut(176, 664, 2);
    new Donut(976, 664, 3);
    new Donut(976, 1304, 4);
    new Donut(1216, 424, 5);
    new Donut(1056, 904, 6);
    new Donut(656, 344, 7);

    Tiles tiles;
    tiles.readSpriteSheet();
    tiles.gridInitRandom(WORLD_W/16, WORLD_H/16);

    LoveAnimation::readSpriteSheet();

    // Barriers
    Barrier::readSpriteSheet();
    std::vector<Barrier> barriers = Barrier::readBarrierFile("./levels/labyrinth_barrier_setup_16.txt");

    // Bushes
    Bush::readSpriteSheet();
    std::vector<Bush> bushes;
    for (int i=0; i<8; i++){
        bushes.emplace_back(i*16+8, WORLD_H - 12*16);
        bushes.emplace_back(i*16+8, WORLD_H - 17*16);        
    }

    // Chest
    Chest::readSpriteSheet();
    Chest chest(1456, 264);
    // Chest chest(36, 1304);

    frames = 0;

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);

    while(1)
    {
        al_wait_for_event(queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:

                player.update();

                // hud.update();
                // hud.writeDebugText(fmt::format("Collision {}", player.collision()));
                // hud.writePanelMessage("This is a test message");

                if(keyboard->get(ALLEGRO_KEY_ESCAPE))
                    done = true;

                redraw = true;
                frames++;
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        keyboard->update(&event);

        if(redraw && al_is_event_queue_empty(queue))
        {
            disp_pre_draw();

            tiles.draw();

            DrawOrder::reset_all();

            player.draw();
            cat1->draw();
            cat2->draw();
            
            Donut::drawAll();

            for (auto & b : barriers)
                b.draw();

            for (auto & b : bushes)
                b.draw();

            chest.draw();

            Animation::drawAllAnimations();

            DrawOrder::execute_all();
            
            hud->draw();

            disp_post_draw();
            redraw = false;
        }
    }

    player.deinit_sprites();
    Cat::deInitSpriteSheet();
    Barrier::deInitSpriteSheet();
    Donut::deInitSpriteSheet();
    LoveAnimation::deinitSprite();

    hud->deinit();
    // audio_deinit();
    disp_deinit();
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}
