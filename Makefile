CC := i686-elf-gcc
CXX := i686-elf-g++
AS := nasm
LD := i686-elf-ld

BUILD_DIR := build
BINARY := $(BUILD_DIR)/microbe
DIRS := $(BUILD_DIR) $(BUILD_DIR)/kernel

CXXFLAGS := -std=c++20 \
			-nostdlib \
			-O2 \
			-Wall \
			-Wextra \
			-I. \
			-ffreestanding \
			-fno-rtti \
			-fno-exceptions \
			-fno-use-cxa-atexit \
			-fno-leading-underscore

ASFLAGS := -felf32

SOURCES_ASM := 	boot.o

SOURCES_CXX := 	Main.o VGA.o Libk.o Printk.o \
				GlobalDescriptorTable.o \
				SegmentDescriptor.o \
				TaskSegmentDescriptor.o

CRTBEGIN_OBJECT := $(shell $(CXX) $(CXXFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJECT := $(shell $(CXX) $(CXXFLAGS) -print-file-name=crtend.o)
CRTI_OBJECT := $(BUILD_DIR)/kernel/crti.o
CRTN_OBJECT := $(BUILD_DIR)/kernel/crtn.o
OBJECTS := $(addprefix $(BUILD_DIR)/kernel/, $(SOURCES_CXX) $(SOURCES_ASM))

# Verbose
verbose := 0
ifeq ($(verbose),0)
	Q := @
else
	Q := 
endif

# Create build tree structure
$(shell mkdir -p $(DIRS))

ECHO := $(Q) echo -e
RM := rm -rf

.PHONY: all run clean nm objdump

all: $(BINARY)

run: all
	$(Q) -qemu-system-i386 \
		-kernel $(BINARY) \
		-display sdl \
		-accel kvm \
		-monitor stdio

$(BINARY): $(OBJECTS) $(CRTI_OBJECT) $(CRTN_OBJECT)
	$(ECHO) "\tLD\t$^"
	$(Q) $(LD) $(CRTBEGIN_OBJECT) $(CRTI_OBJECT) $(OBJECTS) $(CRTN_OBJECT) $(CRTEND_OBJECT) -T linker.ld -o $@

build/kernel/%.o: kernel/%.cpp
	$(ECHO) "\tC++\t$^"
	$(Q) $(CXX) $(CXXFLAGS) $^ -c -o $@

build/kernel/%.o: kernel/%.asm
	$(ECHO) "\tASM\t$^"
	$(Q) $(AS) $(ASFLAGS) $^ -o $@

nm:
	nm -WC $(BINARY)

objdump:
	objdump -Mintel -EL -T -t -w -C -D $(BINARY) | less

clean:
	$(RM) $(BUILD_DIR)/