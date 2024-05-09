#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

#include "Game.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (proj_main_loop)(int argc, char *argv[]) {
  if (initialize_frame_buffer(0x115) != 0) {
    return 1;
  }

  if (graphic_mode(0x115) != 0) {
    return 1;
  }

  bool running = true;
  GameState gameState = MENU;

  while(running){
    switch(gameState){

      case MENU:
        if (menuLogic(&gameState, &running)!= 0) return 1;
      break;

      case GAME: 
        if (gameLogic(&gameState, &running)!= 0) return 1;
      break;

      case ABOUTUS:
        //if (aboutUsLogic(&running)!= 0) return 1;
      break;

      case EXIT:
        running = false;
      break;
      }
      //gameState = GAME;
  }

  if (vg_exit() != 0) {
    return 1;
  }

  return 0;

}
