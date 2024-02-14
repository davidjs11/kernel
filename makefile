### makefile ########################################################
HOME 		= .
SRC			= $(HOME)
INCLUDE		= $(HOME)
BUILD		= $(HOME)/build
OBJ			= $(HOME)/obj
BOOT		= $(SRC)/boot
CPU			= $(SRC)/cpu
KERNEL		= $(SRC)/kernel
LIBC		= $(SRC)/libc
DRIVERS		= $(SRC)/drivers
DIRS		= $(BUILD) $(BOOT) $(CPU) $(KERNEL) $(LIBC) $(DRIVERS)
ALL_FILES	= $(patsubst %, %/*, $(DIRS))

C_FILES   	= $(wildcard $(KERNEL)/*.c)\
			  $(wildcard $(CPU)/*.c)\
			  $(wildcard $(LIBC)/*.c)\
			  $(wildcard $(DRIVERS)/*.c)

ASM_FILES 	= $(wildcard $(CPU)/*.asm)

OBJ_FILES 	= $(patsubst %.c, %.o, $(C_FILES))\
			  $(patsubst %.asm, %.o, $(ASM_FILES))
BIN_FILES 	= $(wildcard $(BUILD)/*.bin)
HEADERS   	= $(wildcard $(KERNEL)/*.h)\
			  $(wildcard $(CPU)/*.h)\
			  $(wildcard $(LIBC)/*.h)\
			  $(wildcard $(DRIVERS)/*.h)
OS_IMAGE 	= os_image.bin

# OBJ_FILES_*	= $(patsubst %, %.o, $(ALL_FILES))
# BIN_FILES_*	= $(patsubst %, %.bin, $(ALL_FILES))

LD			= i386-elf-ld
CC			= i386-elf-gcc
CC_FLAGS	= -nostdlib -ffreestanding\
			  $(patsubst %, -I%, $(DIRS))

all: os_image
	@echo "[+] done!"

folders:
	@mkdir -p build

$(BUILD)/boot_sector.bin: $(BOOT)/boot_sector.asm
	@echo "compiling...             $@"
	@nasm -f bin $(BOOT)/boot_sector.asm -o $(BUILD)/boot_sector.bin

$(BUILD)/kernel.bin: $(OBJ_FILES)
	@echo "linking...               $@"
	@nasm -f elf $(KERNEL)/kernel_entry.asm -o $(KERNEL)/kernel_entry.o
	@$(LD) -o $(BUILD)/kernel.bin -Ttext 0x1000 $(KERNEL)/kernel_entry.o $^ --oformat binary 

%.o: %.asm
	@echo "compiling...             $@"
	@nasm -f elf $< -o $@

%.o: $(SRC)/%.c $(HEADERS)
	@echo "compiling...             $@"
	@$(CC) -c $< -o $@ $(CC_FLAGS)

os_image: folders $(BUILD)/boot_sector.bin $(BUILD)/kernel.bin
	@cat $(BUILD)/boot_sector.bin $(BUILD)/kernel.bin > $(HOME)/os_image.bin

run: os_image
	@echo "[+] launching..."
	@qemu-system-i386 -drive file=os_image.bin,index=0,if=floppy,format=raw -m 1024

clean:
	@echo "[-] cleaning..."
	@rm -rf $(OBJ_FILES) build $(OS_IMAGE) 
