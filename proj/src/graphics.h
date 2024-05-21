#ifndef _LCOM_GRAPHICS_H_
#define _LCOM_GRAPHICS_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include "images/maze1.xpm"

typedef struct Frame {
    uint8_t *buffer;
    unsigned int res_x, res_y, size, bytesPerPixel;
} Frame; 


Frame frame;
uint8_t *draw_buffer;  
uint8_t *background_buffer;
vbe_mode_info_t mode_info;

int (graphic_mode)(uint16_t mode);
int (initialize_frame_buffer) (uint16_t mode);

int (draw_pixel_to_buffer) (uint16_t x, uint16_t y, uint32_t color);
int (make_xpm)(xpm_map_t xpm, uint16_t xi, uint16_t yi);
uint32_t (return_color)(xpm_map_t xpm, uint16_t xi, uint16_t yi, int base_width, int base_height);
int (drawing_xpm)(xpm_map_t xpm, uint16_t xi, uint16_t yi);

void (initialize_buffers)();
void (free_buffers)();
void (update_frame)();
void (clear_frame)();
void (clear_drawing)();

int (background_drawing)(xpm_map_t xpm, uint16_t xi, uint16_t yi);
void (update_frame_with_background)();

#endif
