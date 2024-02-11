### makefile ########################################################
HOME 		= .
SRC			= $(HOME)
INCLUDE		= $(HOME)

C_FILES   = $(wildcard $(SRC)/*.c)
ASM_FILES = $(wildcard $(SRC)/*.asm)
OBJ_FILES = $(patsubst %.c, %.o, $(C_FILES)) interrupt.o
HEADERS	  = $(wildcard $(INCLUDE)/*.h)

all: os_image
	@echo "[+] done!"

test: all clean

boot_sector.bin: boot_sector.asm
	@echo "compiling...             $@"
	@nasm -f bin boot_sector.asm -o boot_sector.bin

kernel.bin: $(OBJ_FILES)
	@echo "linking...               $@"
	@nasm -f elf kernel_entry.asm -o kernel_entry.o
	@i386-elf-ld -o kernel.bin -Ttext 0x1000 kernel_entry.o $^ --oformat binary 

%.o: %.asm
	@echo "compiling...             $@"
	@nasm -f elf $< -o $@

%.o: $(SRC)/%.c $(HEADERS)
	@echo "compiling...             $@"
	@i386-elf-gcc -nostdlib -ffreestanding -c $< -o $@ -I$(INCLUDE)

os_image: boot_sector.bin kernel.bin
	@cat boot_sector.bin kernel.bin > os_image.bin

run: os_image
	@qemu-system-i386 -fda os_image.bin

clean:
	@echo "[-] cleaning..."
	@rm -rf *.o *.bin
