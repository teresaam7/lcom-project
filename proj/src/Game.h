#ifndef GAME_H
#define GAME_H

#include <lcom/lcf.h>

#include "keyboard.h"
#include "mouse.h"
#include "graphics.h"
#include "sprite.h"

#include "images/teste.xpm"
#include "images/maze1.xpm"
#include "images/maze2.xpm"
#include "images/maze3.xpm"
#include "images/menu.xpm"

#include "images/right1.xpm"
#include "images/right2.xpm"
#include "images/left1.xpm"
#include "images/left2.xpm"
#include "images/up1.xpm"
#include "images/up2.xpm"
#include "images/down1.xpm"
#include "images/down2.xpm"

#include "images/hand.xpm"
#include "images/start_button.xpm"
#include "images/hover_start.xpm"

/*enum SpriteState {
    RIGHT1,
    RIGHT2,
    LEFT1,
    LEFT2,
    UP1,
    UP2,
    DOWN1,
    DOWN2
};*/

typedef enum {
    MENU,
    GAME,
    ABOUTUS,
    EXIT
} GameState;

int (menuLogic) (GameState *gameState, bool *running);
int (gameLogic) (GameState *gameState, bool *running);

void (draw_game)();
void (draw_menu)();


//enum SpriteState get_next_state(enum SpriteState current_state, uint8_t scancode) ;

xpm_map_t get_next_sprite(xpm_map_t current_state, uint8_t scancode); 

void (handle_ingame_scancode)(uint8_t scancode, Sprite *player);
void (handle_mouse_movement)(Sprite * cursor);
void (update_menu_frame)(Sprite * start, Sprite * cursor);

#endif

