
#include "Game.h"

uint8_t k_index = 0;
uint8_t k_bytes[2];
extern uint8_t k_scancode;

extern int m_index;
extern uint8_t m_bytes[3];
extern struct packet m_packet;
extern vbe_mode_info_t mode_info;

extern bool gameState_change;
extern GameState gameState;


extern Sprite *menu_bg, *title_, *start, *quit, *cursor, *level1_, *level2_, *level3_, *num, *player, *life;

void (draw_menu)(){
  drawing_bg(menu_bg);
  drawing_sprite(start);
  drawing_sprite(quit);
  drawing_sprite(cursor);
  drawing_sprite(title_);
  update_flip_frames(); 
}


void (update_menu)(){
  drawing_bg(menu_bg);

  if(collision(cursor,start)){
    Sprite* hover_start_sp = create_sprite((xpm_map_t)hover_start, 295, 293, 0);
    drawing_sprite(hover_start_sp);
    
  }
  else drawing_sprite(start);
  if(collision(cursor,quit)){
    Sprite* hover_quit_sp = create_sprite((xpm_map_t)hover_quit, 315, 373, 0);
    drawing_sprite(hover_quit_sp);
    
  }
  else drawing_sprite(quit);
  drawing_sprite(cursor);

  update_flip_frames();
}


int (collision)(Sprite * sp1, Sprite * sp2){
  if(sp1->x < sp2->x || sp1 -> x > sp2->x + sp2->width) return 0;
  if(sp1->y < sp2->y || sp1 -> y > sp2->y + sp2->height) return 0;
  return 1;
}

void (draw_life_bar)( Sprite **bar, int total_seconds) {
    switch(total_seconds){
        case 30:
            *bar = create_sprite((xpm_map_t)life5, 610, 5, 0);
            drawing_sprite(*bar);
            break;
        case 60:
            *bar = create_sprite((xpm_map_t)life4, 610, 5, 0);
            drawing_sprite(*bar);
            break;
        case 90:
            *bar = create_sprite((xpm_map_t)life3, 610, 5, 0);
            drawing_sprite(*bar);
            break;
        case 140:
            *bar = create_sprite((xpm_map_t)life2, 610, 5, 0);
            drawing_sprite(*bar);
            break;
        default:
            return;
    }
    clear_drawing();
    drawing_sprite(*bar);
    //update_frame_with_background();
}

void drawLevel( int x, int y, int width, int height) {
  uint8_t hours, minutes, seconds;
  get_game_time(&hours, &minutes, &seconds);

  switch (gameState) {
    case LEVEL1:
      if (hours >= 6 && hours < 14) {
        //background_drawing((xpm_map_t) mazeDay1, x, y, width, height);
      } else if (hours >= 20 || hours < 6) {
        //background_drawing((xpm_map_t) mazeDark1, x, y, width, height);
      } else {
        //background_drawing((xpm_map_t) maze1, x, y, width, height);
      }
      break;
    case LEVEL2:
      if (hours >= 6 && hours < 14) {
        //background_drawing((xpm_map_t) mazeDay2, x, y, width, height);
      } else if (hours >= 20 || hours < 6) {
        //background_drawing((xpm_map_t) mazeDark2, x, y, width, height);
      } else {
        //background_drawing((xpm_map_t) maze2, x, y, width, height);
      }
      break;
    case LEVEL3:
      if (hours >= 6 && hours < 14) {
        //background_drawing((xpm_map_t) mazeDay3, x, y, width, height);
      } else if (hours >= 20 || hours < 6) {
        //background_drawing((xpm_map_t) mazeDark3, x, y, width, height);
      } else {
        //background_drawing((xpm_map_t) maze3, x, y, width, height);
      }
      break;
    default:
      return;
  }
}

void (draw_game_menu)() {
  //update_frame_with_background();
  clear_drawing();
  drawing_sprite(menu_bg);
  level1_ = create_sprite((xpm_map_t)level1, 315, 260, 0);
  level2_ = create_sprite((xpm_map_t)level2, 315, 340, 0);
  level3_ = create_sprite((xpm_map_t)level3, 315, 420, 0);
  num = create_sprite((xpm_map_t)ar, 30, 530, 0);
  drawing_sprite(level1_);
  drawing_sprite(level2_);
  drawing_sprite(level3_);
  drawing_sprite(num);
}

void (draw_game)(){
  //update_frame_with_background();
  clear_drawing();
  cursor = create_sprite((xpm_map_t)hand, 315, 200, 0);
  player = create_sprite((xpm_map_t)right1, 20, 20, 0);
  life = create_sprite((xpm_map_t)life1, 610, 5, 0);
  drawing_sprite(player);
  drawing_sprite(life);
  drawing_sprite(cursor);
}




void (draw_win)() {
  //drawing_xpm((xpm_map_t) win,1,1);
  display_game_time();
}

void (draw_lost)() {
  //drawing_xpm((xpm_map_t) win,1,1);
}


xpm_map_t get_next_sprite(xpm_map_t current_state, uint8_t scancode) {
    switch (scancode) {
        case A_KEY_MK:
            return (xpm_map_t)left1;
        case D_KEY_MK:
            return (xpm_map_t)right1;
        case W_KEY_MK:
            return (xpm_map_t)up1;
        case S_KEY_MK:
            return (xpm_map_t)down1;
        case A_KEY_BRK:
            return (xpm_map_t)left2;
        case D_KEY_BRK:
            return (xpm_map_t)right2;
        case W_KEY_BRK:
            return (xpm_map_t)up2;
        case S_KEY_BRK:
            return (xpm_map_t)down2;
        default:
            return (xpm_map_t)current_state;
    }
}


void handle_ingame_scancode( uint8_t scancode, Sprite *player) {
    
    switch (scancode) {
        case D_KEY_MK:
            player->x = player->x + 5;
            player=create_sprite((xpm_map_t)get_next_sprite((xpm_map_t)player->map, D_KEY_MK), player->x, player->y, player->speed);
            update_game_frame(player);
            break;

        case A_KEY_MK:
            player->x = player->x - 5;
            player=create_sprite((xpm_map_t)get_next_sprite((xpm_map_t)player->map, A_KEY_MK), player->x, player->y, player->speed);
            update_game_frame(player);
            break;

        case W_KEY_MK:
            player->y = player->y- 5;
            player=create_sprite((xpm_map_t)get_next_sprite((xpm_map_t)player->map, W_KEY_MK), player->x, player->y, player->speed);
            update_game_frame(player);
            break;
        
        case S_KEY_MK:
            player->y = player->y + 5;
            player=create_sprite((xpm_map_t)get_next_sprite((xpm_map_t)player->map, S_KEY_MK), player->x, player->y, player->speed);
            update_game_frame(player);
            break;

        case A_KEY_BRK:
            player=create_sprite((xpm_map_t)get_next_sprite((xpm_map_t)player->map, A_KEY_BRK), player->x, player->y, player->speed);
            update_game_frame(player);
            break;

        case D_KEY_BRK:
            player=create_sprite((xpm_map_t)get_next_sprite((xpm_map_t)player->map, D_KEY_BRK), player->x, player->y, player->speed);
            update_game_frame(player);
            break;

        case S_KEY_BRK:
            player=create_sprite((xpm_map_t)get_next_sprite((xpm_map_t)player->map, S_KEY_BRK), player->x, player->y, player->speed);
            update_game_frame(player);
            break;

        case W_KEY_BRK:
            player=create_sprite((xpm_map_t)get_next_sprite((xpm_map_t)player->map, W_KEY_BRK), player->x, player->y, player->speed);
            update_game_frame(player);
            break;

        default:
            return;
    }


}


void (handle_mouse_movement)(Sprite * cursor){
  if(!(cursor->x + m_packet.delta_x <= 0)) cursor->x += m_packet.delta_x;
  if(!(cursor->y - m_packet.delta_y <= 0)) cursor->y -= m_packet.delta_y;
  if(cursor->x + cursor->width >= mode_info.XResolution)cursor->x = mode_info.XResolution - cursor->width;
  if(cursor->y + cursor->height >= mode_info.YResolution)cursor->y = mode_info.YResolution - cursor->height;
  if(cursor->x + cursor->width >= 785)cursor->x = 785 - cursor->width;
  if(cursor->y + cursor->height >= 575)cursor->y = 575 - cursor->height;
}

void(update_game_frame)(Sprite * player){
  clear_drawing();
  drawLevel (player->x, player->y, player->width, player->width);
  drawLevel (cursor->x, cursor->y, cursor->height, cursor->width);
  drawing_sprite(player);
  drawing_sprite(life);
  drawing_sprite(cursor);
  update_flip_frames();
}

void(update_game_menu)(){
  clear_drawing();
  //drawing_xpm((xpm_map_t) menu,1,1);
  drawing_sprite(menu_bg);
  drawing_sprite(level1_);
  drawing_sprite(level2_);
  drawing_sprite(level3_);
  drawing_sprite(num);

  update_flip_frames();
}



