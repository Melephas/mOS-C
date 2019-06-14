#include <hardware/vga.h>
#include <common/types.h>


static const u8 VGA_WIDTH = 80;
static const u8 VGA_HEIGHT = 25;
static u16* VGA_BUFFER = 0xB8000;

static void clear(struct VGADriver*);
static void fillScreen(struct VGADriver*);
static void setColours(struct VGADriver*, enum VGAColour, enum VGAColour);
static void setForeground(struct VGADriver*, enum VGAColour);
static void setBackground(struct VGADriver*, enum VGAColour);

static void putchar(struct VGADriver*, char);
static void putcharxy(struct VGADriver*, u8, u8, char);

static void puts(struct VGADriver*, char*);
static void putsxy(struct VGADriver*, u8, u8, char*);

static void move(struct VGADriver*, u8, u8);


// TODO: Document
u8 initVGADriver(struct VGADriver* driver) {
  driver->row = 0;
  driver->column = 0;
  driver->colourDouble = 0x07;

  driver->clear = clear;
  driver->fillScreen = fillScreen;
  driver->setColours = setColours;
  driver->setForeground = setForeground;
  driver->setBackground = setBackground;

  driver->putchar = putchar;
  driver->putcharxy = putcharxy;

  driver->puts = puts;
  driver->putsxy = putsxy;

  driver->move = move;

  return 1;
}


// TODO: Document
static void putchar(struct VGADriver* driver, char c) {
  if (c != '\n') {
    VGA_BUFFER[driver->row * VGA_WIDTH + driver->column] = (u16) driver->colourDouble << 8 | c;
  }

  if (++driver->column == VGA_WIDTH || c == '\n') {
    driver->column = 0;
    if (++driver->row == VGA_HEIGHT) {
      --driver->row;
      int i;
      for (i = 80; i < VGA_HEIGHT * VGA_WIDTH; ++i) {
        VGA_BUFFER[i-80] = VGA_BUFFER[i];
      }
      for (i = 0; i < VGA_WIDTH; ++i) {
        VGA_BUFFER[i + (VGA_WIDTH * (VGA_HEIGHT - 1))] = (u16) driver->colourDouble << 8 | ' ';
      }
    }
  }
}

static void putcharxy(struct VGADriver* driver, u8 x, u8 y, char c) {
  move(driver, x, y);
  putchar(driver, c);
}

static void puts(struct VGADriver* driver, char* string) {
  while (*string) {
    putchar(driver, *string);
    ++string;
  }
}

static void putsxy(struct VGADriver* driver, u8 x, u8 y, char* string) {}


static void clear(struct VGADriver* driver) {
  fillScreen(driver);
  move(driver, 0, 0);
}

static void fillScreen(struct VGADriver* driver) {
  int x, y;
  for (x = 0; x < VGA_WIDTH; ++x) {
    for (y = 0; y < VGA_HEIGHT; ++y) {
      putcharxy(driver, x, y, ' ');
    }
  }
}

static void setColours(struct VGADriver* driver, enum VGAColour foreground, enum VGAColour background) {}

static void setForeground(struct VGADriver* driver, enum VGAColour colour) {}

static void setBackground(struct VGADriver* driver, enum VGAColour colour) {}

static void move(struct VGADriver* driver, u8 x, u8 y) {
  driver->column = x;
  driver->row = y;
}

