#ifndef OV7670_H
#define OV7670_H

// OV7670 pin definitions
#define OV7670_MCLK_PIN 20  // Pin for MCLK
#define OV7670_RESET_PIN 10 // Pin for RESET
#define OV7670_PCLK_PIN 11  // Enable OV7670 PCLK pin control
#define OV7670_HREF_PIN 21  // Enable OV7670 HREF pin control
#define OV7670_VSYNC_PIN 7  // Enable OV7670 VSYNC pin control
#define OV7670_PWDN_PIN -1  // Pin for PWDN, -1 if not used

// Supported color formats
#define OV7670_COLOR_RGB 0 // RGB565 big-endian
#define OV7670_COLOR_YUV 1 // YUV/YCbCr 422 big-endian

// Supported sizes (VGA division factor) for OV7670_set_size()
#define OV7670_SIZE_DIV1 0  //"""640 x 480"""
#define OV7670_SIZE_DIV2 1  //"""320 x 240"""
#define OV7670_SIZE_DIV4 2  //"""160 x 120"""
#define OV7670_SIZE_DIV8 3  //"""80 x 60"""
#define OV7670_SIZE_DIV16 4 //"""40 x 30"""

// Test patterns
#define OV7670_TEST_PATTERN_NONE 0 // Normal operation mode (no test pattern)
#define OV7670_TEST_PATTERN_SHIFTING_1 1     //""""Shifting 1" pattern"""
#define OV7670_TEST_PATTERN_COLOR_BAR 2      //"""8 color bars"""
#define OV7670_TEST_PATTERN_COLOR_BAR_FADE 3 //"""Color bars w/fade to white"""

// table of night mode settings
#define OV7670_NIGHT_MODE_OFF 0        //"""Disable night mode"""
#define OV7670_NIGHT_MODE_2 0b10100000 //"""Night mode 1/2 frame rate"""]
#define OV7670_NIGHT_MODE_4 0b11000000 //"""Night mode 1/4 frame rate"""
#define OV7670_NIGHT_MODE_8 0b11100000 //"""Night mode 1/8 frame rate"""

//"""Default I2C address if unspecified"""
#define OV7670_ADDR 0x21 // ov7670 address

// i2c define pins
#define _OV7670_I2C_SDA_PIN 8 // SDA pin
#define _OV7670_I2C_SCL_PIN 9 // SCL pin

// OV7670 MCLK frequency
#define OV7670_MCLK_FREQUENCY 16 // MCLK frequention selection in MHz

// start ov7670 register defines
#define _OV7670_REG_GAIN 0x00               // AGC gain bits 7:0 (9:8 in VREF)
#define _OV7670_REG_BLUE 0x01               // AWB blue channel gain
#define _OV7670_REG_RED 0x02                // AWB red channel gain
#define _OV7670_REG_VREF 0x03               // Vert frame control bits
#define _OV7670_REG_COM1 0x04               // Common control 1
#define _OV7670_COM1_R656 0x40              // COM1 enable R656 format
#define _OV7670_REG_BAVE 0x05               // U/B average level
#define _OV7670_REG_GbAVE 0x06              // Y/Gb average level
#define _OV7670_REG_AECHH 0x07              // Exposure value - AEC 15:10 bits
#define _OV7670_REG_RAVE 0x08               // V/R average level
#define _OV7670_REG_COM2 0x09               // Common control 2
#define _OV7670_COM2_SSLEEP 0x10            // COM2 soft sleep mode
#define _OV7670_REG_PID 0x0A                // Product ID MSB (read-only)
#define _OV7670_REG_VER 0x0B                // Product ID LSB (read-only)
#define _OV7670_REG_COM3 0x0C               // Common control 3
#define _OV7670_COM3_SWAP 0x40              // COM3 output data MSB/LSB swap
#define _OV7670_COM3_SCALEEN 0x08           // COM3 scale enable
#define _OV7670_COM3_DCWEN 0x04             // COM3 DCW enable
#define _OV7670_REG_COM4 0x0D               // Common control 4
#define _OV7670_REG_COM5 0x0E               // Common control 5
#define _OV7670_REG_COM6 0x0F               // Common control 6
#define _OV7670_REG_AECH 0x10               // Exposure value 9:2
#define _OV7670_REG_CLKRC 0x11            // Internal clock          
#define _OV7670_CLK_EXT 0x40                // CLKRC Use ext clock directly
#define _OV7670_CLK_SCALE 0x3F              // CLKRC Int clock prescale mask
#define _OV7670_REG_COM7 0x12               // Common control 7
#define _OV7670_COM7_RESET 0x80             // COM7 SCCB register reset
#define _OV7670_COM7_SIZE_MASK 0x38         // COM7 output size mask
#define _OV7670_COM7_PIXEL_MASK 0x05        // COM7 output pixel format mask
#define _OV7670_COM7_SIZE_VGA 0x00          // COM7 output size VGA
#define _OV7670_COM7_SIZE_CIF 0x20          // COM7 output size CIF
#define _OV7670_COM7_SIZE_QVGA 0x10         // COM7 output size QVGA
#define _OV7670_COM7_SIZE_QCIF 0x08         // COM7 output size QCIF
#define _OV7670_COM7_RGB 0x04               // COM7 pixel format RGB
#define _OV7670_COM7_YUV 0x00               // COM7 pixel format YUV
#define _OV7670_COM7_BAYER 0x01             // COM7 pixel format Bayer RAW
#define _OV7670_COM7_PBAYER 0x05            // COM7 pixel fmt proc Bayer RAW
#define _OV7670_COM7_COLORBAR 0x02          // COM7 color bar enable
#define _OV7670_REG_COM8 0x13               // Common control 8
#define _OV7670_COM8_FASTAEC 0x80           // COM8 Enable fast AGC/AEC algo,
#define _OV7670_COM8_AECSTEP 0x40           // COM8 AEC step size unlimited
#define _OV7670_COM8_BANDING 0x20           // COM8 Banding filter enable
#define _OV7670_COM8_AGC 0x04               // COM8 AGC (auto gain) enable
#define _OV7670_COM8_AWB 0x02               // COM8 AWB (auto white balance)
#define _OV7670_COM8_AEC 0x01               // COM8 AEC (auto exposure) enable
#define _OV7670_REG_COM9 0x14               // Common control 9 - max AGC value
#define _OV7670_REG_COM10 0x15              // Common control 10
#define _OV7670_COM10_HSYNC 0x40            // COM10 HREF changes to HSYNC
#define _OV7670_COM10_PCLK_HB 0x20          // COM10 Suppress PCLK on hblank
#define _OV7670_COM10_HREF_REV 0x08         // COM10 HREF reverse
#define _OV7670_COM10_VS_EDGE 0x04          // COM10 VSYNC chg on PCLK rising
#define _OV7670_COM10_VS_NEG 0x02           // COM10 VSYNC negative
#define _OV7670_COM10_HS_NEG 0x01           // COM10 HSYNC negative
#define _OV7670_REG_HSTART 0x17             // Horiz frame start high bits
#define _OV7670_REG_HSTOP 0x18              // Horiz frame end high bits
#define _OV7670_REG_VSTART 0x19             // Vert frame start high bits
#define _OV7670_REG_VSTOP 0x1A              // Vert frame end high bits
#define _OV7670_REG_PSHFT 0x1B              // Pixel delay select
#define _OV7670_REG_MIDH 0x1C               // Manufacturer ID high byte
#define _OV7670_REG_MIDL 0x1D               // Manufacturer ID low byte
#define _OV7670_REG_MVFP 0x1E               // Mirror / vert-flip enable
#define _OV7670_MVFP_MIRROR 0x20            // MVFP Mirror image
#define _OV7670_MVFP_VFLIP 0x10             // MVFP Vertical flip
#define _OV7670_REG_LAEC 0x1F               // Reserved
#define _OV7670_REG_ADCCTR0 0x20            // ADC control
#define _OV7670_REG_ADCCTR1 0x21            // Reserved
#define _OV7670_REG_ADCCTR2 0x22            // Reserved
#define _OV7670_REG_ADCCTR3 0x23            // Reserved
#define _OV7670_REG_AEW 0x24                // AGC/AEC upper limit
#define _OV7670_REG_AEB 0x25                // AGC/AEC lower limit
#define _OV7670_REG_VPT 0x26                // AGC/AEC fast mode op region
#define _OV7670_REG_BBIAS 0x27              // B channel signal output bias
#define _OV7670_REG_GbBIAS 0x28             // Gb channel signal output bias
#define _OV7670_REG_EXHCH 0x2A              // Dummy pixel insert MSB
#define _OV7670_REG_EXHCL 0x2B              // Dummy pixel insert LSB
#define _OV7670_REG_RBIAS 0x2C              // R channel signal output bias
#define _OV7670_REG_ADVFL 0x2D              // Insert dummy lines MSB
#define _OV7670_REG_ADVFH 0x2E              // Insert dummy lines LSB
#define _OV7670_REG_YAVE 0x2F               // Y/G channel average value
#define _OV7670_REG_HSYST 0x30              // HSYNC rising edge delay
#define _OV7670_REG_HSYEN 0x31              // HSYNC falling edge delay
#define _OV7670_REG_HREF 0x32               // HREF control
#define _OV7670_REG_CHLF 0x33               // Array current control
#define _OV7670_REG_ARBLM 0x34              // Array ref control - reserved
#define _OV7670_REG_ADC 0x37                // ADC control - reserved
#define _OV7670_REG_ACOM 0x38               // ADC & analog common - reserved
#define _OV7670_REG_OFON 0x39               // ADC offset control - reserved
#define _OV7670_REG_TSLB 0x3A               // Line buffer test option
#define _OV7670_TSLB_NEG 0x20               // TSLB Negative image enable
#define _OV7670_TSLB_YLAST 0x04             // TSLB UYVY or VYUY, see COM13
#define _OV7670_TSLB_AOW 0x01               // TSLB Auto output window
#define _OV7670_REG_COM11 0x3B              // Common control 11
#define _OV7670_COM11_NIGHT 0x80            // COM11 Night mode
#define _OV7670_COM11_NMFR 0x60             // COM11 Night mode frame rate mask
#define _OV7670_COM11_HZAUTO 0x10           // COM11 Auto detect 50/60 Hz
#define _OV7670_COM11_BAND 0x08             // COM11 Banding filter val select
#define _OV7670_COM11_EXP 0x02              // COM11 Exposure timing control
#define _OV7670_REG_COM12 0x3C              // Common control 12
#define _OV7670_COM12_HREF 0x80             // COM12 Always has HREF
#define _OV7670_REG_COM13 0x3D              // Common control 13
#define _OV7670_COM13_GAMMA 0x80            // COM13 Gamma enable
#define _OV7670_COM13_UVSAT 0x40            // COM13 UV saturation auto adj
#define _OV7670_COM13_UVSWAP 0x01           // COM13 UV swap, use w TSLB[3]
#define _OV7670_REG_COM14 0x3E              // Common control 14
#define _OV7670_COM14_DCWEN 0x10            // COM14 DCW & scaling PCLK enable
#define _OV7670_REG_EDGE 0x3F               // Edge enhancement adjustment
#define _OV7670_REG_COM15 0x40              // Common control 15
#define _OV7670_COM15_RMASK 0xC0            // COM15 Output range mask
#define _OV7670_COM15_R10F0 0x00            // COM15 Output range 10 to F0
#define _OV7670_COM15_R01FE 0x80            // COM15              01 to FE
#define _OV7670_COM15_R00FF 0xC0            // COM15              00 to FF
#define _OV7670_COM15_RGBMASK 0x30          // COM15 RGB 555/565 option mask
#define _OV7670_COM15_RGB 0x00              // COM15 Normal RGB out
#define _OV7670_COM15_RGB565 0x10           // COM15 RGB 565 output
#define _OV7670_COM15_RGB555 0x30           // COM15 RGB 555 output
#define _OV7670_REG_COM16 0x41              // Common control 16
#define _OV7670_COM16_AWBGAIN 0x08          // COM16 AWB gain enable
#define _OV7670_REG_COM17 0x42              // Common control 17
#define _OV7670_COM17_AECWIN 0xC0           // COM17 AEC window must match COM4
#define _OV7670_COM17_CBAR 0x08             // COM17 DSP Color bar enable
#define _OV7670_REG_AWBC1 0x43              // Reserved
#define _OV7670_REG_AWBC2 0x44              // Reserved
#define _OV7670_REG_AWBC3 0x45              // Reserved
#define _OV7670_REG_AWBC4 0x46              // Reserved
#define _OV7670_REG_AWBC5 0x47              // Reserved
#define _OV7670_REG_AWBC6 0x48              // Reserved
#define _OV7670_REG_REG4B 0x4B              // UV average enable
#define _OV7670_REG_DNSTH 0x4C              // De-noise strength
#define _OV7670_REG_MTX1 0x4F               // Matrix coefficient 1
#define _OV7670_REG_MTX2 0x50               // Matrix coefficient 2
#define _OV7670_REG_MTX3 0x51               // Matrix coefficient 3
#define _OV7670_REG_MTX4 0x52               // Matrix coefficient 4
#define _OV7670_REG_MTX5 0x53               // Matrix coefficient 5
#define _OV7670_REG_MTX6 0x54               // Matrix coefficient 6
#define _OV7670_REG_BRIGHT 0x55             // Brightness control
#define _OV7670_REG_CONTRAS 0x56            // Contrast control
#define _OV7670_REG_CONTRAS_CENTER 0x57     // Contrast center
#define _OV7670_REG_MTXS 0x58               // Matrix coefficient sign
#define _OV7670_REG_LCC1 0x62               // Lens correction option 1
#define _OV7670_REG_LCC2 0x63               // Lens correction option 2
#define _OV7670_REG_LCC3 0x64               // Lens correction option 3
#define _OV7670_REG_LCC4 0x65               // Lens correction option 4
#define _OV7670_REG_LCC5 0x66               // Lens correction option 5
#define _OV7670_REG_MANU 0x67               // Manual U value
#define _OV7670_REG_MANV 0x68               // Manual V value
#define _OV7670_REG_GFIX 0x69               // Fix gain control
#define _OV7670_REG_GGAIN 0x6A              // G channel AWB gain
#define _OV7670_REG_DBLV 0x6B               // PLL & regulator control
#define _OV7670_REG_AWBCTR3 0x6C            // AWB control 3
#define _OV7670_REG_AWBCTR2 0x6D            // AWB control 2
#define _OV7670_REG_AWBCTR1 0x6E            // AWB control 1
#define _OV7670_REG_AWBCTR0 0x6F            // AWB control 0
#define _OV7670_REG_SCALING_XSC 0x70        // Test pattern X scaling
#define _OV7670_REG_SCALING_YSC 0x71        // Test pattern Y scaling
#define _OV7670_REG_SCALING_DCWCTR 0x72     // DCW control
#define _OV7670_REG_SCALING_PCLK_DIV 0x73   // DSP scale control clock divide
#define _OV7670_REG_REG74 0x74              // Digital gain control
#define _OV7670_REG_REG76 0x76              // Pixel correction
#define _OV7670_REG_SLOP 0x7A               // Gamma curve highest seg slope
#define _OV7670_REG_GAM_BASE 0x7B           // Gamma register base (1 of 15)
#define _OV7670_GAM_LEN 0x0F                // Number of gamma registers
#define _OV7670_R76_BLKPCOR 0x80            // REG76 black pixel corr enable
#define _OV7670_R76_WHTPCOR 0x40            // REG76 white pixel corr enable
#define _OV7670_REG_RGB444 0x8C             // RGB 444 control
#define _OV7670_R444_ENABLE 0x02            // RGB444 enable
#define _OV7670_R444_RGBX 0x01              // RGB444 word format
#define _OV7670_REG_DM_LNL 0x92             // Dummy line LSB
#define _OV7670_REG_LCC6 0x94               // Lens correction option 6
#define _OV7670_REG_LCC7 0x95               // Lens correction option 7
#define _OV7670_REG_HAECC1 0x9F             // Histogram-based AEC/AGC ctrl 1
#define _OV7670_REG_HAECC2 0xA0             // Histogram-based AEC/AGC ctrl 2
#define _OV7670_REG_SCALING_PCLK_DELAY 0xA2 // Scaling pixel clock delay
#define _OV7670_REG_BD50MAX 0xA5            // 50 Hz banding step limit
#define _OV7670_REG_HAECC3 0xA6             // Histogram-based AEC/AGC ctrl 3
#define _OV7670_REG_HAECC4 0xA7             // Histogram-based AEC/AGC ctrl 4
#define _OV7670_REG_HAECC5 0xA8             // Histogram-based AEC/AGC ctrl 5
#define _OV7670_REG_HAECC6 0xA9             // Histogram-based AEC/AGC ctrl 6
#define _OV7670_REG_HAECC7 0xAA             // Histogram-based AEC/AGC ctrl 7
#define _OV7670_REG_BD60MAX 0xAB            // 60 Hz banding step limit
#define _OV7670_REG_ABLC1 0xB1              // ABLC enable
#define _OV7670_REG_THL_ST 0xB3             // ABLC target
#define _OV7670_REG_SATCTR 0xC9             // Saturation control

#define _OV7670_REG_LAST _OV7670_REG_SATCTR // Maximum register address
// -- // end ov7670 register defines

extern const uint8_t OV7670_DATA_PINS[8]; // Enable OV7670 DATA pins control
extern int _window[5][4];                 // Enable OV7670 DATA pins control
extern int WIDTH;
extern int HEIGHT;

int ov7670_capture(uint8_t *buf, size_t len, int width,
                   int height); // needs to implement

int ov7670_mclk_config(void);

int ov7670_i2c_config(void);

int ov7670_reset(void);

int ov7670_shutdown(void);

int ov7670_config(void);

int ov7670_pins_config(void);

int ov7670_product_version(void);

int ov7670_product_id(void);

int ov7670_write_register(uint8_t OV7670_I2C_REG_ADDR,
                          uint8_t OV7670_I2C_REG_VALUE);

int ov7670_read_register(uint8_t reg);

int ov7670_register_test(void);

int ov7670_register_writelist(void);

int ov7670_frame_control(uint8_t size, uint16_t vstart, uint16_t hstart,
                         uint8_t edge_offset, uint8_t pclk_delay);

#endif