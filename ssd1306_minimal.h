#ifndef SSD1306_MINIMAL_H
#define SSD1306_MINIMAL_H

unsigned char framebuffer[1024];
#define SSD1306_MINIMAL_SLAVE_ADDR 0x3c

void SSD1306_MINIMAL_command(unsigned char command) {
  I2C_WRAPPER_beginTransmission(SSD1306_MINIMAL_SLAVE_ADDR);
  I2C_WRAPPER_write(0x80);
  I2C_WRAPPER_write(command);
  I2C_WRAPPER_endTransmission();
}

/* Transfers the entire framebuffer in 64 I2C data messages */
void SSD1306_MINIMAL_transferFramebuffer() {
  unsigned char *p = framebuffer;
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
  framebuffer[((y & 0xf8) << 4) + x] |= 1 << (y & 7);
}

void SSD1306_MINIMAL_init() {
  /* Enable charge pump regulator (RESET = ) */
  SSD1306_MINIMAL_command(0x8d);
  SSD1306_MINIMAL_command(0x14);

  /* Display On (RESET = ) */
  SSD1306_MINIMAL_command(0xaf);

  /* Set Memory Addressing Mode to Horizontal Addressing Mode (RESET = Page Addressing Mode) */
  SSD1306_MINIMAL_command(0x20);
  SSD1306_MINIMAL_command(0x00);

  /* Reset Column Address (for horizontal addressing) */
  SSD1306_MINIMAL_command(0x21);
  SSD1306_MINIMAL_command(0);
  SSD1306_MINIMAL_command(127);

  /* Reset Page Address (for horizontal addressing) */
  SSD1306_MINIMAL_command(0x22);
  SSD1306_MINIMAL_command(0);
  SSD1306_MINIMAL_command(7);
}

#endif
