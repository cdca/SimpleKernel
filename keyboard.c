#include "common.h"
#include "keyboard.h"
#include "monitor.h"
#include "isr.h"


#include <stdint.h>

static char k;
unsigned char keyboard_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};
char getScancode() {
    char c=0;
    do {
        if(inb(0x60)!=c) {
            c=inb(0x60);
            if(c>0)
                return c;
        }
    } while(1);
}
 char vrati()
{ return k;
}

void keyboard_handler(registers_t regs) {

    
    u8int status = inb(0x64);
    if (status & 0x01) {
        char keycode = inb(0x60); // do not forget to read the key.
        if (keycode < 0) {
            return;
        }
       u8int key = keyboard_map[keycode];
	
	k=key;
	//monitor_put(k);
      //  printf("Received keycode %d which is %d %c\n", keycode, key, key);
       // monitor_put(key);
    }
}

void kb_init() {
 monitor_write("Tastatura upaljena\n");
    // Enables irq1 which is the keyboard.
    // 11111101

  
	outb(0x21 , 0xFD);

    register_interrupt_handler(IRQ1, keyboard_handler);





}
