
#include "Game.h"

uint8_t k_index = 0;
uint8_t k_bytes[2];
extern uint8_t k_scancode;

extern int m_index;
extern uint8_t m_bytes[3];
extern struct packet m_packet;
extern vbe_mode_info_t mode_info;

int (collision)(Sprite * sp1, Sprite * sp2){
  if(sp1->x < sp2->x || sp1 -> x > sp2->x + sp2->width) return 0;
  if(sp1->y < sp2->y || sp1 -> y > sp2->y + sp2->height) return 0;
  return 1;
}

int (menuLogic) (GameState *gameState, bool * running) {
    initialize_buffers();

    if (write_mouse(ENABLE_DATA_MODE) != 0)
      return 1;

    uint8_t irq_set_keyboard;
    if (keyboard_subscribe_int(&irq_set_keyboard) != 0)
        return 1;

    uint8_t irq_set_mouse;
    if (mouse_subscribe_int(&irq_set_mouse) != 0)
      return 1;
    
    int r;
    message msg;
    int ipc_status;

    make_xpm((xpm_map_t) menu,1,1);

   Sprite *start, *cursor;
    cursor = create_sprite((xpm_map_t)right1, 200, 200, 0, 0);
    start = create_sprite((xpm_map_t)start_button, 315, 300, 0, 0);
    drawing_sprite(start);
    drawing_sprite(cursor);


    update_frame();
    clear_drawing();

    
    while (k_scancode != SCAN_BREAK_ESC && *gameState == MENU ) { 

      printf("Estou onde nao devia");   
     
      if( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
        printf("driver_receive failed with: %d", r);
        continue;
      }

      int count = 0;
      
      if (is_ipc_notify(ipc_status)) {      
        switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE:    
            if (msg.m_notify.interrupts & irq_set_keyboard) { 
                count++;
                kbc_ih();
                printf("ENTREI onde nao devia");   

                //handle_ingame_scancode(k_scancode,cursor);
                if (k_scancode == SCAN_FIRST_TWO) {
                    k_bytes[k_index] = k_scancode; k_index++;
                } else {
                    k_bytes[k_index] = k_scancode;
                    // kbd_print_scancode(!(scancode & MAKE_OR_BREAK), i == 0? 1: 2 , bytes);
                    k_index = 0;
                }

            }

            if (msg.m_notify.interrupts & irq_set_mouse) { 
                count++;
                mouse_ih();
                store_bytes_packet();

                if (m_index == 3) {
                    m_index = 0;
                    mouse_print_packet(&m_packet);
                    handle_mouse_movement(cursor);
                    update_menu_frame(start, cursor);
                  
                    if (m_packet.lb) {
                      if(collision(cursor, start))
                        *gameState = GAME;
                    }
                }
            }
            break;

          default:
            break; 
        }
      }
    }
 
    if (keyboard_unsubscribe_int() != 0)
        return 1;

    if (mouse_unsubscribe_int() != 0)
      return 1;

    if (write_mouse(DISABLE_DATA_MODE) != 0)
      return 1;
    free_buffers();
    if(k_scancode == SCAN_BREAK_ESC)
    *running = false;
  

    return 0;

}

int (gameLogic) (GameState *gameState, bool * running) {
    initialize_buffers();

    if (write_mouse(ENABLE_DATA_MODE) != 0)
      return 1;

    uint8_t irq_set_keyboard;
    if (keyboard_subscribe_int(&irq_set_keyboard) != 0)
        return 1;

    uint8_t irq_set_mouse;
    if (mouse_subscribe_int(&irq_set_mouse) != 0)
      return 1;
    
    int r;
    message msg;
    int ipc_status;

    Sprite *sp,*start, *cursor;

    if(*gameState == GAME){
    make_xpm((xpm_map_t) maze2,1,1);
    sp = create_sprite((xpm_map_t)right1, 20, 20, 0, 0);
    drawing_sprite(sp);
    }


    if(*gameState == MENU){
    make_xpm((xpm_map_t) menu,1,1);
    cursor = create_sprite((xpm_map_t)right1, 315, 200, 0, 0);
    start = create_sprite((xpm_map_t)start_button, 315, 300, 0, 0);
    drawing_sprite(start);
    drawing_sprite(cursor);
    }

    update_frame();
    clear_drawing();

    bool gameState_change = false;
    
    while (k_scancode != SCAN_BREAK_ESC) { 

      if(gameState_change){
            if(*gameState == GAME){
            make_xpm((xpm_map_t) maze2,1,1);
            sp = create_sprite((xpm_map_t)right1, 20, 20, 0, 0);
            drawing_sprite(sp);
            }


            if(*gameState == MENU){
            make_xpm((xpm_map_t) menu,1,1);
            cursor = create_sprite((xpm_map_t)right1, 315, 200, 0, 0);
            start = create_sprite((xpm_map_t)start_button, 315, 300, 0, 0);
            drawing_sprite(start);
            drawing_sprite(cursor);
            }
            update_frame();
    clear_drawing();
        gameState_change = false;
      }  
     
      if( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
        printf("driver_receive failed with: %d", r);
        continue;
      }

      int count = 0;
      
      if (is_ipc_notify(ipc_status)) {      
        switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE:    
            if (msg.m_notify.interrupts & irq_set_keyboard) { 
                count++;
                kbc_ih();
                if(*gameState == GAME){
                handle_ingame_scancode(k_scancode, sp);
                }

                if (k_scancode == SCAN_FIRST_TWO) {
                    k_bytes[k_index] = k_scancode; k_index++;
                } else {
                    k_bytes[k_index] = k_scancode;
                    // kbd_print_scancode(!(scancode & MAKE_OR_BREAK), i == 0? 1: 2 , bytes);
                    k_index = 0;
                }

            }

            if (msg.m_notify.interrupts & irq_set_mouse) { 
                mouse_ih();

                if (m_index == 3) {
                    store_bytes_packet();
                    mouse_print_packet(&m_packet);
                    m_index = 0;
                    if(*gameState == MENU){
                      mouse_print_packet(&m_packet);
                      handle_mouse_movement(cursor);
                      update_menu_frame(start, cursor);
                    
                      if (m_packet.lb) {
                        if(collision(cursor, start))
                          *gameState = GAME;
                          printf("SOFIA");  
                          gameState_change = true;                        
                      }
                    }
                }
            }
            break;

          default:
            break; 
        }
      }
    }
    if (keyboard_unsubscribe_int() != 0)
        return 1;

    if (mouse_unsubscribe_int() != 0)
      return 1;

    if (write_mouse(DISABLE_DATA_MODE) != 0)
      return 1;
    if(k_scancode == SCAN_BREAK_ESC)*running = false;

    free_buffers();

    return 0;
}

enum SpriteState get_next_sprite(enum SpriteState current_state, uint8_t scancode) {
    switch (scancode) {
        case A_KEY_MK:
            return LEFT1;
        case D_KEY_MK:
            return RIGHT1;
        case W_KEY_MK:
            return UP1;
        case S_KEY_MK:
            return DOWN1;
        case A_KEY_BRK:
            return LEFT2;
        case D_KEY_BRK:
            return RIGHT2;
        case W_KEY_BRK:
            return UP2;
        case S_KEY_BRK:
            return DOWN2;
        default:
            return current_state;
    }
}

/*A personagem pinta o fundo enquanto anda -- dar fix*/

void handle_ingame_scancode(uint8_t scancode, Sprite *player) {
    //static enum SpriteState current_state = RIGHT1;
    //enum SpriteState next_state = get_next_sprite(current_state, scancode);
    /*Falta trocar de sprite quando anda para o lado*/
    switch (scancode) {
        case D_KEY_MK:
            player->x = player->x + 1;
            break;

        case A_KEY_MK:
            player->x = player->x - 1;
            break;

        case W_KEY_MK:
            player->y = player->y- 1;
            break;
        
        case S_KEY_MK:
            player->y = player->y + 1;
            break;
        case A_KEY_BRK:
        case D_KEY_BRK:
           
            break;

        default:
            return;
    }
    clear_drawing();
    make_xpm((xpm_map_t) maze2,1,1);
    drawing_sprite(player);
    update_frame();
}


void (handle_mouse_movement)(Sprite * cursor){
  if(!(cursor->x + m_packet.delta_x <= 0)) cursor->x += m_packet.delta_x;
  if(!(cursor->y - m_packet.delta_y <= 0)) cursor->y -= m_packet.delta_y;
  if(cursor->x + cursor->width >= mode_info.XResolution)cursor->x = mode_info.XResolution - cursor->width;
  if(cursor->y + cursor->height >= mode_info.YResolution)cursor->y = mode_info.YResolution - cursor->height;
  if(cursor->x + cursor->width >= 785)cursor->x = 785 - cursor->width;
  if(cursor->y + cursor->height >= 575)cursor->y = 575 - cursor->height;
}

void(update_menu_frame)(Sprite * start, Sprite * cursor){
  clear_drawing();
  make_xpm((xpm_map_t) menu,1,1);
  if(collision(cursor,start)){
    Sprite* hover_start_sp = create_sprite((xpm_map_t)hover_start, 295, 293, 0, 0);
    drawing_sprite(hover_start_sp);
    
  }
  else drawing_sprite(start);
  drawing_sprite(cursor);
  update_frame();
}

