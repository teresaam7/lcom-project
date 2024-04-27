// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include "graphics.h"
#include "keyboard.c"
#include "utils.c"

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int hook_id_keyboard=1;
int (ESC_break)() {
  int ipc_status;
  message msg;
  uint8_t irq_keyboard;
  irq_keyboard=BIT(hook_id_keyboard);
  if(sys_irqsetpolicy(1, IRQ_EXCLUSIVE|IRQ_REENABLE, &hook_id_keyboard)!= 0) return 1;

  while (scancode != 0x81){
    if (driver_receive(ANY, &msg, &ipc_status) != 0) { 
      printf("driver_receive failed");
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & irq_keyboard) 
            kbc_ih();
            break;
        default:
          break; 
      }
    }
  }

  if (sys_irqrmpolicy(&hook_id_keyboard) != 0) return 1;
  return 0;
}

//When this function is invoked, your program should change to the video mode specified in its mode argument.
//After delay seconds, it should go back to Minix's default text mode.
int(video_test_init)(uint16_t mode, uint8_t delay) {
  if(graphics_mode(mode)!=0){return 1;}
  
  //tickdelay(micros_to_ticks(delay));//para unidades inferior ao segundo
  sleep(delay);//para segundos

  //Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
  if(vg_exit()!=0){
    return 1;
  }
  return 0;
}

// Draw a rectangle on the screen in the desired mode
int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {

    if(frame_buffer_func(mode)!=0){return 1;}
    if(graphics_mode(mode)!=0){return 1;}
    
    if(vg_draw_rectangle(x, y, width, height, color)!=0){
        return 1;
    }

    if(ESC_break()!=0){return 1;}//acaba quando esc break pressionado

    if(vg_exit()!=0){
    return 1;
    }
  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  /* To be completed */
  printf("%s(0x%03x, %u, 0x%08x, %d): under construction\n", __func__,
         mode, no_rectangles, first, step);

  return 1;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  /* To be completed */
  printf("%s(%8p, %u, %u): under construction\n", __func__, xpm, x, y);

  return 1;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

//nao fazer
int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
