# Pico C SDK OV7670 Library !


Pico C SDK Driver for 0V7670 cameras raspberry pi Pico 1 and 2.

## Conteúdo

- [Dependencies](#dependencies)
- [Usage Example](#usage-example)
  - [Selfie camera example (ili9341 + OV7670)](#selfie-camera-example-using-ili9341-320x240-pixels-and-ov7670-camera)
    - [Output](#output-of-the-example)
- [Pinout](#pinout)
- [Notes](#notes)
- [My Setup](#my-setup-for-testing)
- [References](#references)
- [Functions](#functions)
- [License](#license)

## Dependencies

The driver needs:
- Pico C SDK


# Usage Example


Inside `src/` folder we have a example called `selfietest`.
- selfietest: an example that uses an ili9341 display to reproduce the image.

### Selfie camera example using ili9341 320x240 pixels and OV7670 camera:

```c
#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "gfx.h"
#include "ili9341.h"
#include "ov7670.h"
#include "touch_resistive.h"

void draw_frame(uint8_t *buf, int width, int height) {
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      size_t offset = (y * width + x) * 2; 
      uint8_t high_byte = buf[offset];  
      uint8_t low_byte = buf[offset + 1];   
      uint16_t color = (high_byte << 8) | low_byte;
      GFX_drawPixel(x, y, color);
    }
  }
  GFX_flush(); /// send to display
}

int main() {
  stdio_init_all();
  ov7670_shutdown();
  ov7670_config();

  int size = OV7670_SIZE_DIV2; 
  WIDTH = 320;
  HEIGHT = 240;

  uint8_t buf[WIDTH * HEIGHT * 2];  

  ov7670_frame_control(size, _window[size][0], _window[size][1],
                       _window[size][2], _window[size][3]);

  stdio_init_all();
  LCD_initDisplay();
  LCD_setRotation(1);
  GFX_createFramebuf();
  configure_touch();

  while (true) {
    ov7670_capture(buf, sizeof(buf), WIDTH, HEIGHT);
    draw_frame(buf, WIDTH, HEIGHT);
  }
}


```

### Output of the example

Pokemons:

![Output2 ](/imgs/output2.jpeg "Output 2")

See the video below:

[![Raspberry Pi Pico + OV7670 Camera](https://img.youtube.com/vi/tngEWj4gqWU/0.jpg)](https://www.youtube.com/shorts/tngEWj4gqWU)

## Pinout

| Signal (name)          | GPIO | Function / usage                       | Direction (RP2350) | Observações |
|-----------------------|------|------------------------------------|------------------|-------------|
| `OV7670_MCLK_PIN`     | 20   | MCLK (master clock, PWM)           | output (PWM)      | Frequency defined by `OV7670_MCLK_FREQUENCY` (MHz). |
| `OV7670_RESET_PIN`    | 10   | RESET do módulo OV7670             | output            | Drives the camera reset pin. |
| `OV7670_PCLK_PIN`     | 11   | PCLK (pixel clock da câmera)       | input          | Synchronizes reading of the 8-bit data bus. |
| `OV7670_HREF_PIN`     | 21   | HREF (start/end de linha)          | input          | Valid pixel data for each line. |
| `OV7670_VSYNC_PIN`    | 7    | VSYNC (start/end de frame)         | input          | Synchronizes the start and end of a frame. |
| `OV7670_PWDN_PIN`     | -1   | PWDN (power down) — **not used**  | —                | `-1` = Power-down pin (PWDN). Controls camera power on/off. Not connected by default.|
| `_OV7670_I2C_SDA_PIN` | 8    | I²C SDA (SCCB)                     | SDA (I²C)        | Must be set with `GPIO_FUNC_I2C` + pull-up. |
| `_OV7670_I2C_SCL_PIN` | 9    | I²C SCL (SCCB)                     | SCL (I²C)        | Must be set with `GPIO_FUNC_I2C` + pull-up. |
| `OV7670_DATA_PINS[0]` | 12   | Data bit 0 (LSB)                   | input          | Parallel data bus `{12..19}`. |
| `OV7670_DATA_PINS[1]` | 13   | Data bit 1                         | input          | — |
| `OV7670_DATA_PINS[2]` | 14   | Data bit 2                         | input          | — |
| `OV7670_DATA_PINS[3]` | 15   | Data bit 3                         | input          | — |
| `OV7670_DATA_PINS[4]` | 16   | Data bit 4                         | input          | — |
| `OV7670_DATA_PINS[5]` | 17   | Data bit 5                         | input          | — |
| `OV7670_DATA_PINS[6]` | 18   | Data bit 6                         | input          | — |
| `OV7670_DATA_PINS[7]` | 19   | Data bit 7 (MSB)                   | input          | — |

### Notes
- MCLK (GPIO 20) is generated through PWM, configured with the default 16MHz.  
- I²C (GPIO 8=SDA, GPIO 9=SCL) uses a `i2c0` at 100 kHz. Must use external pull-up 4.7kOhm resistors.  
- This version uses polling to retrieve data from the camera.

If you need to check the `lib_ili9341/` pins, look at the files in the lib_ili9341 folder.


### My setup for testing

![Setup ](/imgs/setup.jpeg "Setup")


## References

- This driver is an adaptation of the [CircuitPython driver for OV7670 cameras](https://github.com/adafruit/Adafruit_CircuitPython_OV7670/).
- [OV7670 2006 Datasheet](https://web.mit.edu/6.111/www/f2016/tools/OV7670_2006.pdf)


## License

MIT License

Copyright (c) 2025 Daniel Messias da Silva Pinto

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
