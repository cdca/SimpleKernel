#include "gdt.h"
#include "common.h"
#include <stdint.h>
#define MASTER_COMMAND 0x20
#define MASTER_DATA 0x21
#define SLAVE_COMMAND 0xA0
#define SLAVE_DATA 0xA1

// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.
struct gdt_entry_struct
{
    u16int limit_low;           // The lower 16 bits of the limit.
    u16int base_low;            // The lower 16 bits of the base.
    u8int  base_middle;         // The next 8 bits of the base.
    u8int  access;              // Access flags, determine what ring this segment can be used in.
    u8int  granularity;         // low 4 bits are high 4 bits of limit
    u8int  base_high;           // The last 8 bits of the base.
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct
{
    u16int limit;               // The upper 16 bits of all selector limits.
    u32int base;                // The address of the first gdt_entry_t struct.
}
    __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

// Lets us access our ASM functions from our C code.
//extern void load_gdt(uint32_t);
extern void load_gdt(gdt_ptr_t * gdt_ptr);

// Internal function prototypes.
static void gdt_set_gate(s32int,u32int,u32int,u8int,u8int);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;
//idt_entry_t idt_entries[256];
//idt_ptr_t   idt_ptr;


void init_gdt()
{monitor_write("GDT\n");
    gdt_ptr.limit = (sizeof(gdt_entry_t)*5) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;

    /*
      Pr  Priv  1   Ex  DC   RW   Ac
      0x9A == 1001 1010  == 1   00    1   1   0    1    0
      0x92 == 1001 0010  == 1   00    1   0   0    1    0
      0xFA == 1111 1010  == 1   11    1   1   0    1    0
      0xF2 == 1111 0010  == 1   11    1   0   0    1    0

      We have page-granularity and 32-bit mode
      G   D   0   Av
      0xCF == 1100 1111  == 1   1   0   0  ~
    */

    gdt_set_gate(0,0,0,0,0);                    //Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); //Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); //Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); //User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); //User mode data segment

    //terminal_writestring("Flushing GDT.\n");
    load_gdt(&gdt_ptr);
}

static void gdt_set_gate(s32int entry, u32int base, u32int limit, u8int access, u8int gran)
{
    gdt_entries[entry].base_low = (base & 0xFFFF);
    gdt_entries[entry].base_middle = (base >> 16) & 0xFF;
    gdt_entries[entry].base_high = (base >> 24) & 0xFF;

    gdt_entries[entry].limit_low = (limit & 0xFFFF);
    gdt_entries[entry].granularity = (limit >> 16) & 0x0F;

    gdt_entries[entry].granularity |= gran & 0xF0;
    gdt_entries[entry].access = access;
}
