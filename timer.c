// timer.c -- Initialises the PIT, and handles clock updates.
//            Written for JamesM's kernel development tutorials.

#include "timer.h"
#include "isr.h"
#include "monitor.h"
#include "keyboard.h"


u32int tick = 0;

static void timer_callback(registers_t regs)
{ 

char k=vrati();
 
//if (k=='1')
monitor_put(k);
//monitor_write("+"); 
 // else 
   // monitor_write("-"); 

    //monitor_write_dec(tick);
   // monitor_write("\n");
//tick++;

  





}

void init_timer(u32int frequency)
{
    // Firstly, register our timer callback.
char k=vrati();
monitor_put(k);
	if (k=='0')
monitor_write("+"); 
  //register_interrupt_handler(IRQ1, keyboard_handler);
    register_interrupt_handler(IRQ0, &timer_callback);




	
	//monitor_write("IRQ");
    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    u32int divisor = 1193180 / frequency;

    // Send the command byte.
    outb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    u8int l = (u8int)(divisor & 0xFF);
    u8int h = (u8int)( (divisor>>8) & 0xFF );

    // Send the frequency divisor.
    outb(0x40, l);
    outb(0x40, h);
}
