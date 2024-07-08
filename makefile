##   makefile   ##

# --- macros
# dirs
BOOT	= boot
KERNEL	= kernel
BIN		= bin

# tools
AS		= i386-elf-as
CC		= i386-elf-gcc
LD		= i386-elf-ld
EMU		= qemu-system-i386

# flags
ASFLAGS =
CCFLAGS =
LDFLAGS =

# kernel files
KERNEL_S_SRC	= $(wildcard $(KERNEL)/*.S)
KERNEL_C_SRC	= $(wildcard $(KERNEL)/*.c)
KERNEL_OBJ		= $(patsubst $(KERNEL)/%.S,$(KERNEL)/obj/%.o, $(KERNEL_S_SRC))
KERNEL_OBJ		+= $(patsubst $(KERNEL)/%.c,$(KERNEL)/obj/%.o, $(KERNEL_C_SRC))
BOOTIMG			= sys.img

# binaries
BIN_FILES		= $(BIN)/boot.bin $(BIN)/kernel.bin


# --- routines
.PHONY: all clean run
all: $(BOOTIMG)

run: all
	@$(EMU) -drive format=raw,file=$(BOOTIMG)

debug:
	@$(EMU) $(BOOTIMG) -s -S

clean:
	@echo "cleaning..."
	@rm -rf */obj $(BIN) $(BOOTIMG)


# --- bootloader
$(BIN)/boot.bin: $(BOOT)/obj/boot.o
	@echo "LD - boot.bin"
	@mkdir -p $(BIN)
	@$(LD) -o $(BIN)/boot.bin $(BOOT)/obj/boot.o -Ttext 0x7C00 --oformat=binary $(LDFLAGS)

$(BOOT)/obj/boot.o: $(BOOT)/boot.S
	@echo "AS - $<"
	@mkdir -p $(BOOT)/obj
	@$(AS) -o $@ -c $< $(ASFLAGS)


# --- kernel
$(BIN)/kernel.bin: $(KERNEL_OBJ)
	@echo "LD - kernel.bin"
	@$(LD) -o $(BIN)/kernel.bin $^ -T$(KERNEL)/link.ld $(LDFLAGS)

$(KERNEL)/obj/%.o: $(KERNEL)/%.c
	@echo "CC - $<"
	@mkdir -p $(KERNEL)/obj
	@$(CC) -o $@ -c $< $(CCFLAGS)

$(KERNEL)/obj/%.o: $(KERNEL)/%.S
	@echo "AS - $<"
	@mkdir -p $(KERNEL)/obj
	@$(AS) -o $@ -c $< $(ASFLAGS)


# --- boot image
$(BOOTIMG): $(BIN_FILES)
	@echo "creating boot image"
	@dd if=/dev/zero of=$(BOOTIMG) bs=512 count=4096 status=none
	@dd if=$(BIN)/boot.bin of=$(BOOTIMG)   conv=notrunc status=none seek=0 bs=512 count=1
	@dd if=$(BIN)/kernel.bin of=$(BOOTIMG) conv=notrunc status=none seek=1 bs=512 count=2048
