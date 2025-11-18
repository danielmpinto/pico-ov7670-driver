#include <stdio.h>
#include "pico/stdlib.h"
#include "ov7670.h"
#include "hardware/clocks.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"

// # ov7670_rgb array
// Manual output format, RGB, use RGB565 and full 0-255 output range
const uint8_t _OV7670_rgb[] = {
    _OV7670_REG_COM7,   _OV7670_COM7_RGB,
    _OV7670_REG_RGB444, 0x00,
    _OV7670_REG_COM15,  _OV7670_COM15_RGB565 | _OV7670_COM15_R00FF};

// # ov7670_yuv array
// Manual output format, YUV, use full output range
const uint8_t _OV7670_yuv[] = {_OV7670_REG_COM7, _OV7670_COM7_YUV,
                               _OV7670_REG_COM15, _OV7670_COM15_R00FF};

uint8_t _OV7670_inits[] = {
    _OV7670_REG_TSLB,
    _OV7670_TSLB_YLAST, // No auto window
    _OV7670_REG_COM10,
    //   _OV7670_COM10_VS_POS,  // -VSYNC (req by SAMD PCC)
    0x00, // VSYNC
    _OV7670_REG_SLOP, 0x20, _OV7670_REG_GAM_BASE, 0x1C,
    _OV7670_REG_GAM_BASE + 1, 0x28, _OV7670_REG_GAM_BASE + 2, 0x3C,
    _OV7670_REG_GAM_BASE + 3, 0x55, _OV7670_REG_GAM_BASE + 4, 0x68,
    _OV7670_REG_GAM_BASE + 5, 0x76, _OV7670_REG_GAM_BASE + 6, 0x80,
    _OV7670_REG_GAM_BASE + 7, 0x88, _OV7670_REG_GAM_BASE + 8, 0x8F,
    _OV7670_REG_GAM_BASE + 9, 0x96, _OV7670_REG_GAM_BASE + 10, 0xA3,
    _OV7670_REG_GAM_BASE + 11, 0xAF, _OV7670_REG_GAM_BASE + 12, 0xC4,
    _OV7670_REG_GAM_BASE + 13, 0xD7, _OV7670_REG_GAM_BASE + 14, 0xE8,
    _OV7670_REG_COM8,
    _OV7670_COM8_FASTAEC | _OV7670_COM8_AECSTEP | _OV7670_COM8_BANDING,
    _OV7670_REG_GAIN, 0x00, _OV7670_COM2_SSLEEP, 0x00, _OV7670_REG_COM4, 0x00,
    _OV7670_REG_COM9,
    0x20, // Max AGC value
    _OV7670_REG_BD50MAX, 0x05, _OV7670_REG_BD60MAX, 0x07, _OV7670_REG_AEW, 0x75,
    _OV7670_REG_AEB, 0x63, _OV7670_REG_VPT, 0xA5, _OV7670_REG_HAECC1, 0x78,
    _OV7670_REG_HAECC2, 0x68, 0xA1,
    0x03, // Reserved register?
    _OV7670_REG_HAECC3,
    0xDF, // Histogram-based AEC/AGC setup
    _OV7670_REG_HAECC4, 0xDF, _OV7670_REG_HAECC5, 0xF0, _OV7670_REG_HAECC6,
    0x90, _OV7670_REG_HAECC7, 0x94, _OV7670_REG_COM8,
    _OV7670_COM8_FASTAEC | _OV7670_COM8_AECSTEP | _OV7670_COM8_BANDING |
        _OV7670_COM8_AGC | _OV7670_COM8_AEC,
    _OV7670_REG_COM5, 0x61, _OV7670_REG_COM6, 0x4B, 0x16,
    0x02, // Reserved register?
    _OV7670_REG_MVFP,
    0x07, // 0x07,
    _OV7670_REG_ADCCTR1, 0x02, _OV7670_REG_ADCCTR2, 0x91, 0x29,
    0x07, // Reserved register?
    _OV7670_REG_CHLF, 0x0B, 0x35,
    0x0B, // Reserved register?
    _OV7670_REG_ADC, 0x1D, _OV7670_REG_ACOM, 0x71, _OV7670_REG_OFON, 0x2A,
    _OV7670_REG_COM12, 0x78, 0x4D,
    0x40, // Reserved register?
    0x4E,
    0x20, // Reserved register?
    _OV7670_REG_GFIX, 0x5D, _OV7670_REG_REG74, 0x19, 0x8D,
    0x4F, // Reserved register?
    0x8E,
    0x00, // Reserved register?
    0x8F,
    0x00, // Reserved register?
    0x90,
    0x00, // Reserved register?
    0x91,
    0x00, // Reserved register?
    _OV7670_REG_DM_LNL, 0x00, 0x96,
    0x00, // Reserved register?
    0x9A,
    0x80, // Reserved register?
    0xB0,
    0x84, // Reserved register?
    _OV7670_REG_ABLC1, 0x0C, 0xB2,
    0x0E, // Reserved register?
    _OV7670_REG_THL_ST, 0x82, 0xB8,
    0x0A, // Reserved register?
    _OV7670_REG_AWBC1, 0x14, _OV7670_REG_AWBC2, 0xF0, _OV7670_REG_AWBC3, 0x34,
    _OV7670_REG_AWBC4, 0x58, _OV7670_REG_AWBC5, 0x28, _OV7670_REG_AWBC6, 0x3A,
    0x59,
    0x88, // Reserved register?
    0x5A,
    0x88, // Reserved register?
    0x5B,
    0x44, // Reserved register?
    0x5C,
    0x67, // Reserved register?
    0x5D,
    0x49, // Reserved register?
    0x5E,
    0x0E, // Reserved register?
    _OV7670_REG_LCC3, 0x04, _OV7670_REG_LCC4, 0x20, _OV7670_REG_LCC5, 0x05,
    _OV7670_REG_LCC6, 0x04, _OV7670_REG_LCC7, 0x08, _OV7670_REG_AWBCTR3, 0x0A,
    _OV7670_REG_AWBCTR2, 0x55, _OV7670_REG_MTX1, 0x80, _OV7670_REG_MTX2, 0x80,
    _OV7670_REG_MTX3, 0x00, _OV7670_REG_MTX4, 0x22, _OV7670_REG_MTX5, 0x5E,
    _OV7670_REG_MTX6,
    0x80, // 0x40?
    _OV7670_REG_AWBCTR1, 0x11, _OV7670_REG_AWBCTR0,
    0x9F, // Or use 0x9E for advance AWB
    _OV7670_REG_BRIGHT, 0x00, _OV7670_REG_CONTRAS, 0x40,
    _OV7670_REG_CONTRAS_CENTER,
    0x80, // 0x40?
    _OV7670_REG_CLKRC,
    0x02, // limitating pclk (internal clock) for using pooling //best for high
          // resolution, but more delay to generate img
};

// defining data pins
const uint8_t OV7670_DATA_PINS[8] = {12, 13, 14, 15, 16, 17, 18, 19};
int HEIGHT = 0; // height of the image
int WIDTH = 0;  // width of the image
// verified
// window settings for different sizes
// 640x480, 320x240, 160x120, 80x60, 40x30
int _window[5][4] = {
    {9, 162, 2, 2},  // SIZE_DIV1  640x480 VGA
    {10, 174, 0, 2}, // SIZE_DIV2  320x240 QVGA
    {11, 186, 2, 2}, // SIZE_DIV4  160x120 QQVGA
    {12, 210, 0, 2}, // SIZE_DIV8  80x60   ...
    {15, 252, 3, 2}, // SIZE_DIV16 40x30
};                   // window settings for different sizes

// defined all constants and registers

// principal function
int ov7670_capture(uint8_t *buf, size_t len, int width, int height) {
  size_t count = 0;

  // waits for start of frame
  while (gpio_get(OV7670_VSYNC_PIN))
    ;
  while (!gpio_get(OV7670_VSYNC_PIN))
    ;
  while (gpio_get(OV7670_VSYNC_PIN))
    ;

  for (int y = 0; y < height && count < len; y++) {
    // wait for start of line
    while (!gpio_get(OV7670_HREF_PIN)) {
      if (gpio_get(OV7670_VSYNC_PIN))
        return count;
    }

    for (int x = 0; x < width && count < len; x++) {
      // Byte 0: Y
      while (!gpio_get(OV7670_PCLK_PIN))
        ;
      uint8_t y_byte = 0;
      for (int i = 0; i < 8; i++) {
        if (gpio_get(OV7670_DATA_PINS[i]))
          y_byte |= (1 << i); // parallel pins reading
      }
      buf[count++] = y_byte;
      while (gpio_get(OV7670_PCLK_PIN))
        ;

      // Byte 1: U/V (doesnt uses U/V)
      while (!gpio_get(OV7670_PCLK_PIN))
        ;
      for (int i = 0; i < 8; i++) {
        if (gpio_get(OV7670_DATA_PINS[i])) {
          // not used
          // theoraccalyl takes UV byte
        }
      }
      while (gpio_get(OV7670_PCLK_PIN))
        ;
    }

    // wait for end of line
    while (gpio_get(OV7670_HREF_PIN))
      ;
  }

  return count;
}

// get product version from camera
int ov7670_product_version() { return ov7670_read_register(_OV7670_REG_VER); }
//

// get product id from camera
int ov7670_product_id() { return ov7670_read_register(_OV7670_REG_PID); }
// product_id -- ok

// write a register to ov7670
int ov7670_write_register(uint8_t OV7670_I2C_REG_ADDR,
                          uint8_t OV7670_I2C_REG_VALUE) {
  // i2c write blocking
  uint8_t buf[2];
  buf[0] = OV7670_I2C_REG_ADDR;
  buf[1] = OV7670_I2C_REG_VALUE;
  i2c_write_blocking(i2c0, OV7670_ADDR, buf, 2, false);
  // i2c write blocking -- ok
  return 1;
}
// write_register -- ok

// verified
// read a register from ov7670
int ov7670_read_register(uint8_t reg) {
  uint8_t buf;
  // i2c write blocking -- needs to use nostop false, idont know why yet, prob.
  // SCCB doesnt accept repeated start
  i2c_write_blocking(i2c0, OV7670_ADDR, &reg, 1, false);
  // i2c reads
  i2c_read_blocking(i2c0, OV7670_ADDR, &buf, 1, false);

  return buf;
}
// read_register -- ok

int ov7670_pins_config() {
  for (int i = 0; i < 8; i++) {
    gpio_init(OV7670_DATA_PINS[i]);
    gpio_set_dir(OV7670_DATA_PINS[i], GPIO_IN);
  }

  gpio_init(OV7670_PCLK_PIN);
  gpio_set_dir(OV7670_PCLK_PIN, GPIO_IN);

  gpio_init(OV7670_HREF_PIN);
  gpio_set_dir(OV7670_HREF_PIN, GPIO_IN);

  gpio_init(OV7670_VSYNC_PIN);
  gpio_set_dir(OV7670_VSYNC_PIN, GPIO_IN);

  return 1;
}

int ov7670_mclk_config() {

  // define pins
  // mclk clocking generation 16MHz
  gpio_set_function(OV7670_MCLK_PIN, GPIO_FUNC_PWM);
  uint slice_num = pwm_gpio_to_slice_num(OV7670_MCLK_PIN);
  uint channel = pwm_gpio_to_channel(OV7670_MCLK_PIN);
  // get system clock frequency
  uint32_t f_sys = clock_get_hz(clk_sys);

  // calc pwm
  uint32_t wrap = (f_sys / (OV7670_MCLK_FREQUENCY * 1000000)) - 1; // 16 MHz
  pwm_set_clkdiv(slice_num, 1.0f);
  pwm_set_wrap(slice_num, wrap);
  pwm_set_chan_level(slice_num, channel, (wrap + 1) / 2);

  // enables pwm
  pwm_set_enabled(slice_num, true);

  // mclk clocking generation 16MHz - ok
  return 1;
}

int ov7670_i2c_config() {
  // i2c config
  i2c_init(i2c0, 100 * 1000);
  gpio_set_function(_OV7670_I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(_OV7670_I2C_SCL_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(_OV7670_I2C_SDA_PIN);
  gpio_pull_up(_OV7670_I2C_SCL_PIN);
  // i2c config - ok
  return 1;
}

int ov7670_reset() {
  // reset pin
  gpio_init(OV7670_RESET_PIN);
  gpio_set_dir(OV7670_RESET_PIN, GPIO_OUT);

  gpio_put(OV7670_RESET_PIN, 0);
  sleep_ms(1);
  gpio_put(OV7670_RESET_PIN, 1);
  // reseta camera - ok
}

int ov7670_shutdown() {
  // SHUTDOWN camera
  gpio_init(OV7670_PWDN_PIN);
  gpio_set_dir(OV7670_PWDN_PIN, GPIO_OUT);

  gpio_put(OV7670_PWDN_PIN, 1);
  sleep_ms(1);
  gpio_put(OV7670_PWDN_PIN, 0);
  // SHUTDOWN camera - ok
}

// configs camera, including i2c, reset and mclk pins
int ov7670_config() {
  ov7670_shutdown();
  ov7670_pins_config();
  ov7670_mclk_config();
  ov7670_i2c_config();
  ov7670_reset();
  // give time before testing registers
  sleep_ms(100);
  ov7670_register_test();
  ov7670_register_writelist();

  // defines rgb

  return 1;
}

// test camera basic registers
int ov7670_register_test() {
  uint8_t pid = ov7670_product_id();
  uint8_t ver = ov7670_product_version();
  printf("Product ID Number : %x\n", pid);
  printf("Product Version Number : %x\n", ver);


  

  if (pid == 0x76) {
    return 1;
  } else {
    return 0;
  }
}

// writes many values in registers at the same time
int ov7670_register_writelist() {
  int array_size = sizeof(_OV7670_inits) / sizeof(_OV7670_inits[0]);
  printf("Total registers to write: %d\n", array_size);
  printf("Writing init registers...\n");
  for (int i = 0; i < array_size; i += 2) {
    uint8_t reg = _OV7670_inits[i];
    uint8_t val = _OV7670_inits[i + 1];
    if (i == 0) {
      printf("Reg: 0x%02X, Val: 0x%02X\n...\n...\n...\n", reg, val);
    } else if (i == 192) {
      printf("Reg: 0x%02X, Val: 0x%02X\n", reg, val);
    }

    ov7670_write_register(reg, val);
    sleep_ms(1);
  }


  // defines format YUV or TGB
  int array_rgb_size = sizeof(_OV7670_rgb) / sizeof(_OV7670_rgb[0]);
  printf("Total registers to write: %d\n", array_rgb_size);
  printf("Writing init registers...\n");
  for (int i = 0; i < array_rgb_size; i += 2) {
    uint8_t reg = _OV7670_rgb[i];
    uint8_t val = _OV7670_rgb[i + 1];
    if (i == 0) {
      printf("Reg: 0x%02X, Val: 0x%02X\n...\n...\n...\n", reg, val);
    } else if (i == 192) {
      printf("Reg: 0x%02X, Val: 0x%02X\n", reg, val);
    }

    ov7670_write_register(reg, val);
    sleep_ms(1);
  }
  printf("Setup registers finished...\n");
}
// register_writelist -- ok

// frame_control -- ok
int ov7670_frame_control(uint8_t size, uint16_t vstart, uint16_t hstart,
                         uint8_t edge_offset, uint8_t pclk_delay) {
  // set frame control

  uint8_t value;
  if (size > OV7670_SIZE_DIV1) {
    value = _OV7670_COM3_DCWEN;
  } else {
    value = 0;
  }

  if (size == OV7670_SIZE_DIV16) {
    value |= _OV7670_COM3_SCALEEN;
  }
  ov7670_write_register(_OV7670_REG_COM3, value);

  if (size > OV7670_SIZE_DIV1) {
    value = (0x18 + size);
  } else {
    value = 0;
  }
  ov7670_write_register(_OV7670_REG_COM14, value);

  if (size <= OV7670_SIZE_DIV8) {
    value = size;
  } else {
    value = OV7670_SIZE_DIV8;
  }
  ov7670_write_register(_OV7670_REG_SCALING_DCWCTR, (value * 0x11));

  // Pixel clock divider if sub-VGA
  if (size > OV7670_SIZE_DIV1) {
    value = (0xF0 + size);
  } else {
    value = 0x08;
  }
  ov7670_write_register(_OV7670_REG_SCALING_PCLK_DIV, value);

  // Apply 0.5 digital zoom at 1:16 size (others are downsample only)
  // Pixel clock divider if sub-VGA
  if (size == OV7670_SIZE_DIV16) {
    value = 0x40;
  } else {
    value = 0x20;
  }

  // Read current SCALING_XSC and SCALING_YSC register values because
  // test pattern settings are also stored in those registers and we
  // don't want to corrupt anything there
  uint8_t xsc = ov7670_read_register(_OV7670_REG_SCALING_XSC);
  uint8_t ysc = ov7670_read_register(_OV7670_REG_SCALING_YSC);
  xsc = (xsc & 0x80) | value; // Modify only scaling bits (not test pattern)
  ysc = (ysc & 0x80) | value;

  // Write modified result back to SCALING_XSC and SCALING_YSC
  ov7670_write_register(_OV7670_REG_SCALING_XSC, xsc);
  ov7670_write_register(_OV7670_REG_SCALING_YSC, ysc);

  // Window size is scattered across multiple registers.
  // Horiz/vert stops can be automatically calc'd from starts.
  uint16_t vstop = vstart + 480;
  uint16_t hstop = (hstart + 640) % 784;

  ov7670_write_register(_OV7670_REG_HSTART, hstart >> 3);
  ov7670_write_register(_OV7670_REG_HSTOP, hstop >> 3);
  ov7670_write_register(_OV7670_REG_HREF, (edge_offset << 6) |
                                              ((hstop & 0b111) << 3) |
                                              (hstart & 0b111));

  ov7670_write_register(_OV7670_REG_VSTART, vstart >> 2);
  ov7670_write_register(_OV7670_REG_VSTOP, vstop >> 2);
  ov7670_write_register(_OV7670_REG_VREF,
                        ((vstop & 0b11) << 2) | (vstart & 0b11));
  ov7670_write_register(_OV7670_REG_SCALING_PCLK_DELAY, pclk_delay);

  return 1;
}
// frame_control -- ok
