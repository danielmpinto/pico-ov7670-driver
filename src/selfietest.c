#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "gfx.h"
#include "ili9341.h"
#include "ov7670.h"
#include "touch_resistive.h"

void draw_frame(uint8_t *buf, int width, int height) {
  // for each item inside buffer
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      


      // defining offset for RGB565
      size_t offset = (y * width + x) * 2; 
      // takes most significant byte from offset (Red and half Green)
      uint8_t high_byte = buf[offset];  
      // takes less significant byte from offset + 1 (half Green and Blue)
      uint8_t low_byte = buf[offset + 1];   

      // concatenates into a 16bit variable called color
      uint16_t color = (high_byte << 8) | low_byte;

      // draw in LCD
      GFX_drawPixel(x, y, color);
    }
  }
  GFX_flush(); /// send to display
}

int main() {
  stdio_init_all();
  // ov7670 shutdown, theorically not needed
  ov7670_shutdown();
  ov7670_config();

  // defines size
  // OV7670_SIZE_DIV1            0  //"""640 x 480"""
  // OV7670_SIZE_DIV2            1  //"""320 x 240"""
  // OV7670_SIZE_DIV4            2  //"""160 x 120"""
  // OV7670_SIZE_DIV8            3  //"""80 x 60"""
  // OV7670_SIZE_DIV16           4  //"""40 x 30"""
  int size = OV7670_SIZE_DIV2; // 320x240
  WIDTH = 320;
  HEIGHT = 240;

  // WIDTH * HEIGHT 'cause is RGB565 (needs to bytes per pixel)                      
  uint8_t buf[WIDTH * HEIGHT * 2];  

  ov7670_frame_control(size, _window[size][0], _window[size][1],
                       _window[size][2], _window[size][3]);



  stdio_init_all();

  // inilitializations display and touch
  LCD_initDisplay();
  LCD_setRotation(1);
  GFX_createFramebuf();
  configure_touch();

  while (true) {
    // transfers image to buffer
    ov7670_capture(buf, sizeof(buf), WIDTH, HEIGHT);
    // reproduces image using display
    draw_frame(buf, WIDTH, HEIGHT);
  }
}
