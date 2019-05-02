#ifndef SSD1306_MINIMAL_H
#define SSD1306_MINIMAL_H

unsigned char SSD1306_MINIMAL_framebuffer[1024];
#define SSD1306_MINIMAL_SLAVE_ADDR 0x3c

/* Transfers the entire framebuffer in 64 I2C data messages */
void SSD1306_MINIMAL_transferFramebuffer() {
  unsigned char *p = SSD1306_MINIMAL_framebuffer;
  for (int i = 0; i < 64; i++) {
        I2C_WRAPPER_beginTransmission(SSD1306_MINIMAL_SLAVE_ADDR);
        I2C_WRAPPER_write(0x40);
        for(int i = 0; i < 16; i++) {
          I2C_WRAPPER_write(*p);
          p++;
        }
        I2C_WRAPPER_endTransmission();
  }  
}

/* Horizontal addressing mode maps to linear framebuffer */
void SSD1306_MINIMAL_setPixel(unsigned int x, unsigned int y) {
  x &= 0x7f;
  y &= 0x3f;
  SSD1306_MINIMAL_framebuffer[((y & 0xf8) << 4) + x] |= 1 << (y & 7);
}

void SSD1306_MINIMAL_init() {
  unsigned char initialization[] = {
    /* Enable charge pump regulator (RESET = ) */
    0x8d,
    0x14,
    /* Display On (RESET = ) */
    0xaf,
    /* Set Memory Addressing Mode to Horizontal Addressing Mode (RESET = Page Addressing Mode) */
    0x20,
    0x0,
    /* Reset Column Address (for horizontal addressing) */
    0x21,
    0,
    127,
    /* Reset Page Address (for horizontal addressing) */
    0x22,
    0,
    7
  };

  I2C_WRAPPER_beginTransmission(SSD1306_MINIMAL_SLAVE_ADDR);
  for (int i = 0; i < sizeof(initialization); i++) {
    I2C_WRAPPER_write(0x80);
    I2C_WRAPPER_write(initialization[i]);
  }
  I2C_WRAPPER_endTransmission();
}

#endif
