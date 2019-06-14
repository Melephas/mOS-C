#ifndef _MOS_HARDWARE_VGA_H
#define _MOS_HARDWARE_VGA_H

#include <common/types.h>

// TODO: Document
enum VGAColour {
  Black = 0,
  Blue,
  Green,
  Cyan,
  Red,
  Magenta,
  Brown,
  LightGrey,
  DarkGrey,
  LightBlue,
  LightGreen,
  LightCyan,
  LightRed,
  LightMagenta,
  LightBrown,
  White
};

// TODO: Document
struct VGADriver {
  u8 row;
  u8 column;
  u8 colourDouble;

  void (*clear)(struct VGADriver*);
  void (*fillScreen)(struct VGADriver*);
  void (*setColours)(struct VGADriver*, enum VGAColour, enum VGAColour);
  void (*setForeground)(struct VGADriver*, enum VGAColour);
  void (*setBackground)(struct VGADriver*, enum VGAColour);

  void (*move)(struct VGADriver*, u8, u8);

  void (*putchar)(struct VGADriver*, char);
  void (*putcharxy)(struct VGADriver*, u8, u8, char);

  void (*puts)(struct VGADriver*, char*);
  void (*putsxy)(struct VGADriver*, u8, u8, char*);
};

struct VGADriver* vgaDriver;

u8 initVGADriver(struct VGADriver*);

#endif
