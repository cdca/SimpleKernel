[bits 32]

MALIGN   equ 1<<0
MEMINFO  equ 1<<1
FLAGS    equ MALIGN | MEMINFO
MAGIC    equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
dd MAGIC
dd FLAGS
dd CHECKSUM


section .bootstrap_stack nobits write align=16
align 16
stack_bottom:
resb 32768
stack_top:

extern kernel_main
section .text
global _start:function (_start.end - _start)
_start:
    mov esp, stack_top
    ;sti
    push ebx
    call kernel_main
.end

global halt
halt:
    cli
    hlt
.Lhang:
    jmp halt
.end

section .text
global pause
pause:
    hlt
    ret

section .text
global sys_cli
sys_cli:
    hlt
    ret


section .text
global sys_sti
sys_sti:
    hlt
    ret

section .kend
global end_of_kernel
end_of_kernel:

[bits 32]

section .text
global load_gdt

load_gdt:
    mov     eax, DWORD [esp + 4]
    lgdt    [eax]

    mov     ax, 10h
    mov     ds, ax
    mov     es, ax
    mov     fs, ax
    mov     gs, ax
    mov     ss, ax
    jmp    08h:flush
flush:
    ret


[bits 32]
section .text
global load_idt

load_idt:
    mov    eax, [esp + 4]
    lidt   [eax]
    ret

;; num %1
%macro isr_noerr 1
global isr%1
isr%1:
    cli
    push 0
    push %1
    jmp isr_stub
%endmacro


%macro isr_err 1
global isr%1
isr%1:
    cli
    push %1
    jmp isr_stub
%endmacro

isr_noerr 0
isr_noerr 1
isr_noerr 2
isr_noerr 3
isr_noerr 4
isr_noerr 5
isr_noerr 6
isr_noerr 7
isr_err 8
isr_noerr 9
isr_err 10
isr_err 11
isr_err 12
isr_err 13
isr_err 14
isr_noerr 15
isr_noerr 16
isr_noerr 17
isr_noerr 18
isr_noerr 19
isr_noerr 20
isr_noerr 21
isr_noerr 22
isr_noerr 23
isr_noerr 24
isr_noerr 25
isr_noerr 26
isr_noerr 27
isr_noerr 28
isr_noerr 29
isr_noerr 30
isr_noerr 31

extern isr_handler
isr_stub:
    pusha

    mov     ax, ds
    push	eax
    mov     esi, eax

    mov 	ax, 10h
    mov 	ds, ax
    mov 	es, ax
    mov 	fs, ax
    mov 	gs, ax

    call	isr_handler

    pop	    eax
    mov		eax, esi

    mov	    ds, ax
    mov 	ds, ax
    mov 	es, ax
    mov 	fs, ax
    mov 	gs, ax

    popa
    add	    esp, 8
    sti
    iret

;; num %1 map %2
%macro irq 2
global irq%1
irq%1:
    cli
    push    0
    push    %2
    jmp     irq_stub
%endmacro

irq 0, 32
irq 1, 33
irq 2, 34
irq 3, 35
irq 4, 36
irq 5, 37
irq 6, 38
irq 7, 39
irq 8, 40
irq 9, 41
irq 10, 42
irq 11, 43
irq 12, 44
irq 13, 45
irq 14, 46
irq 15, 47

    
extern irq_handler
irq_stub:
    pusha

    mov	    ax, ds
    push	eax
    mov 	esi, eax

    mov 	ax, 10h
    mov 	ds, ax
    mov 	es, ax
    mov 	fs, ax
    mov 	gs, ax

    call	irq_handler

    pop	    ebx
    mov 	ebx, esi

    mov 	ds, bx
    mov 	es, bx
    mov 	fs, bx
    mov 	gs, bx

    popa
    add     esp, 8
    sti
    iret
