##   makefile   ##

# --- macros
# dirs
# BOOT	= boot
ARCH	= i386
ARCHDIR = arch/$(ARCH)
BOOT	= $(ARCHDIR)/boot
KERNEL	= kernel
BIN		= bin

# tools
AS		= i386-elf-as
CC		= i386-elf-gcc
LD		= i386-elf-ld
EMU		= qemu-system-i386

# flags
ASFLAGS =
CCFLAGS = -Wall -I$(KERNEL)/include -I$(ARCHDIR)/include
LDFLAGS =

# arch-dependent files
ARCH_S_SRC		= $(wildcard $(ARCHDIR)/*.S)
ARCH_C_SRC		= $(wildcard $(ARCHDIR)/*.c)
ARCH_OBJ		= $(patsubst $(ARCHDIR)/%.S,$(ARCHDIR)/obj/%.o, $(ARCH_S_SRC))
ARCH_OBJ	   += $(patsubst $(ARCHDIR)/%.c,$(ARCHDIR)/obj/%.o, $(ARCH_C_SRC))

# kernel files
KERNEL_S_SRC	= $(wildcard $(KERNEL)/*.S)
KERNEL_C_SRC	= $(wildcard $(KERNEL)/*.c)
KERNEL_OBJ		= $(patsubst $(KERNEL)/%.S,$(KERNEL)/obj/%.o, $(KERNEL_S_SRC))
KERNEL_OBJ	   += $(patsubst $(KERNEL)/%.c,$(KERNEL)/obj/%.o, $(KERNEL_C_SRC))
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
	@rm -rf */obj **/*/obj **/**/*/obj $(BIN) $(BOOTIMG)


# --- bootloader
$(BIN)/boot.bin: $(BOOT)/obj/boot.o
	@echo "LD - boot.bin"
	@mkdir -p $(BIN)
	@$(LD) -o $(BIN)/boot.bin $(BOOT)/obj/boot.o -Ttext 0x7C00 --oformat=binary $(LDFLAGS)

$(BOOT)/obj/boot.o: $(BOOT)/boot.S
	@echo "AS - $<"
	@mkdir -p $(BOOT)/obj
	@$(AS) -o $@ -c $< $(ASFLAGS)


# --- kernel binary
$(BIN)/kernel.bin: $(KERNEL_OBJ) $(ARCH_OBJ)
	@echo "LD - kernel.bin"
	@$(LD) -o $(BIN)/kernel.bin $^ -Tlink.ld $(LDFLAGS)


# --- kernel files
$(KERNEL)/obj/%.o: $(KERNEL)/%.c
	@echo "CC - $<"
	@mkdir -p $(KERNEL)/obj
	@$(CC) -o $@ -c $< $(CCFLAGS)

$(KERNEL)/obj/%.o: $(KERNEL)/%.S
	@echo "AS - $<"
	@mkdir -p $(KERNEL)/obj
	@$(AS) -o $@ -c $< $(ASFLAGS)


# --- architecture files
$(ARCHDIR)/obj/%.o: $(ARCHDIR)/%.c
	@echo "CC - $<"
	@mkdir -p $(ARCHDIR)/obj
	@$(CC) -o $@ -c $< $(CCFLAGS)

$(ARCHDIR)/obj/%.o: $(ARCHDIR)/%.S
	@echo "AS - $<"
	@mkdir -p $(ARCHDIR)/obj
	@$(AS) -o $@ -c $< $(ASFLAGS)

# --- boot image
$(BOOTIMG): $(BIN_FILES)
	@echo "creating $(BOOTIMG)..."
	@dd if=/dev/zero of=$(BOOTIMG) bs=512 count=4096 status=none
	@dd if=$(BIN)/boot.bin of=$(BOOTIMG)   conv=notrunc status=none seek=0 bs=512 count=1
	@dd if=$(BIN)/kernel.bin of=$(BOOTIMG) conv=notrunc status=none seek=1 bs=512 count=2048
