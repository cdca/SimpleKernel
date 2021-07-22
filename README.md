# CDCA SimpleKernel
CDCA SimpleKernel is a simple operating system kernel for research, teaching, and fun.  
   
This kernel reads input from keyboard and then repeats that key infinitely.  
This kernel needs to be compiled with a ix86-elf compiler.  


## Dependencies:  
* i686-elf toolchain (GCC, Binutils)  
* GRUB, for the grub-mkrescue command, along with the appropriate runtime files.  
* Xorriso, the .iso creation engine used by grub-mkrescue.  
* Qemu, optionally for testing the operating system.  


# Build:
sh build.sh  

## Demo:
![](https://media.giphy.com/media/luNkfFj53AHB2HGlSQ/giphy.gif)

## Resources
You can find more information here:  
https://wiki.osdev.org/Bare_Bones  
https://wiki.osdev.org/Meaty_Skeleton  
https://wiki.osdev.org/GDT_Tutorial  
https://wiki.osdev.org/Keyboard
