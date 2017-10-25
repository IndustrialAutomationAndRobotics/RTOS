###############################################################################
# Makefile for the project FreeRTOS
###############################################################################

## General Flags
PROJECT = FreeRTOS
MCU = atmega169
TARGET = FreeRTOS.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -lm            -DF_CPU=1000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=FreeRTOS.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"D:\Workspace\MFI\Sem5\RTOS\Lab\messageQueue\FreeRTOS\Source" -I"D:\Workspace\MFI\Sem5\RTOS\Lab\messageQueue\FreeRTOS\Source\portable\GCC\ATMega169" -I"D:\Workspace\MFI\Sem5\RTOS\Lab\messageQueue\." -I"D:\Workspace\MFI\Sem5\RTOS\Lab\messageQueue\FreeRTOS\Source\include" -I"D:\Workspace\MFI\Sem5\RTOS\Lab\messageQueue\include" 

## Objects that must be built in order to link
OBJECTS = croutine.o list.o queue.o tasks.o heap_1.o port.o Main_Prog.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) FreeRTOS.hex FreeRTOS.eep FreeRTOS.lss size

## Compile
croutine.o: ../FreeRTOS/Source/croutine.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

list.o: ../FreeRTOS/Source/list.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

queue.o: ../FreeRTOS/Source/queue.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

tasks.o: ../FreeRTOS/Source/tasks.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

heap_1.o: ../FreeRTOS/Source/portable/MemMang/heap_1.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

port.o: ../FreeRTOS/Source/portable/GCC/ATMega169/port.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Main_Prog.o: ../Main_Prog.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) FreeRTOS.elf dep/* FreeRTOS.hex FreeRTOS.eep FreeRTOS.lss FreeRTOS.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

