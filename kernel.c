#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "isr.h"
#include "common.h"
#include "keyboard.h"
#include "monitor.h"





/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif


#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

extern void pause();
extern char _binary_f32_disk_start;



void kernel_main(struct multiboot_info *mi)
{
  monitor_write("Hello, CEDOMIRE\n");
   
  init_gdt();
remap_pic();
  init_idt();


 //kb_init();
/*
struct time_t;
  time_t *a;
monitor_write(a->minute);*/

init_timer(10);

/*gettime(a);
a->hour=5;
a->second=6;
a->minute=7;
a->year=8;
gettime(a);
monitor_write_dec(a->hour);
monitor_write_dec(a->second);
monitor_write_dec(a->minute);
monitor_write_dec(a->year);*/


  
//monitor_write(", d: ");
   //monitor_newline();

   
    // Write a number in decimal
   // monitor_write_dec(42);
    monitor_newline();
    // gettime(time_t);
   // monitor_write("0x");
    //monitor_write_hex(0xdeadbeef);
  //  monitor_newline();

    //asm volatile("int $0x3"); //ovdje zovem isr
   // asm volatile("int $0x4"); /// zovem isr 
  
asm volatile("sti"); //ovdje sam stavio set interrupt flag 
    while(1) {
       // char c = get_ascii_char();
       // printf("%c", c);
    };
    //printf("Halting.\n");

}
