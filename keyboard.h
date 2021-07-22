#ifndef _KERNEL_KEYBOARD_H
#define _KERNEL_KEYBOARD_H

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60
#include "isr.h"
char vrati();
void kb_init();
void keyboard_handler(registers_t);

#endif
