#include <common/types.h>
#include <hardware/vga.h>

void kMain( void ) {
	struct VGADriver vga;
	initVGADriver(&vga);

	vga.clear(&vga);
	vga.puts(&vga, "mOS v0.1.0\n");

	while (1);
}
