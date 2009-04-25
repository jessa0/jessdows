#include "printf.h"

#define VGA_BASE 0xB8000

static const int vga_rows=25, vga_cols=80;
static int vga_ypos=0, vga_xpos=0;

void putchar(char c) {
  if (c == '\n') {
    vga_ypos++;
    vga_xpos = 0;

    // scroll if necessary
    if (vga_ypos >= vga_rows) {
      for (vga_ypos = 1; vga_ypos < vga_rows; vga_ypos++)
        for (vga_xpos = 0; vga_xpos < vga_cols; vga_xpos++)
          *((short *) VGA_BASE + (vga_ypos-1) * vga_cols + vga_xpos) = 
            *((short *) VGA_BASE + vga_ypos * vga_cols + vga_xpos);
          
    }
  } else if (c != '\r') {
    *((char *) VGA_BASE + vga_ypos * vga_cols + 2 * vga_xpos) = c;
    *((char *) VGA_BASE + vga_ypos * vga_cols + 2 * vga_xpos + 1) = 7;
    
    // increment current position and do newline if necessary
    if (++vga_xpos >= vga_cols)
      putchar('\n');
  }
}

void puts(char *str) {
  while (*str != 0)
    putchar(*str++);
  putchar('\n');
}
