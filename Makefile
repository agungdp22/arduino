# @author: lintang, vektor
# REF: http://www.ashleymills.com/node/327
# For board-specific setting see: https://github.com/arduino/Arduino/blob/master/hardware/arduino/boards.txt
CC=avr-gcc
CXX=avr-g++

MASTER_MCU=-mmcu=atmega328p #: atmega2560, atmega328p 
MASTER_MCU_TAG=m328p #: m2560, m328p
MASTER_UPLOAD_PROTOCOL=arduino #: arduino (for atmega328p), wiring (for atmega2560), avr109
MASTER_BOARD=arduino
MASTER_CPU_SPEED=-DF_CPU=16000000UL
MASTER_CFLAGS=$(MASTER_MCU) $(MASTER_CPU_SPEED) -Os -w -Wl,--gc-sections -ffunction-sections -fdata-sections
MASTER_LIBNAME=lib$(MASTER_BOARD)-master.a
MASTER_UPLOAD_BAUDRATE=115200 #(for promini m328p), 115200 (for mega m2560, uno m328p)
MASTER_PORT=/dev/ttyACM0

TARGET_INCDIR=./include
TARGET_LIBDIR=./lib
TARGET_BUILDDIR=./build

# the word ARDUINO refers to the core arduino library and/or anything related to building it
ARDUINO_SRC= ./src/arduino/
ARDUINO_INC=-I $(ARDUINO_SRC)
ARDUINO_OBJ=$(ARDUINO_SRC)pins_arduino.o $(ARDUINO_SRC)wiring.o $(ARDUINO_SRC)wiring_analog.o $(ARDUINO_SRC)wiring_digital.o \
			$(ARDUINO_SRC)wiring_pulse.o $(ARDUINO_SRC)wiring_shift.o $(ARDUINO_SRC)Stream.h $(ARDUINO_SRC)HardwareSerial.o  $(ARDUINO_SRC)Print.o   \
			$(ARDUINO_SRC)Tone.o $(ARDUINO_SRC)WMath.o $(ARDUINO_SRC)WString.o $(ARDUINO_SRC)WInterrupts.o $(ARDUINO_SRC)new.o \
			$(ARDUINO_SRC)twi.o $(ARDUINO_SRC)Wire.o 

# NOTICE: the library linking order does matter 
# see: http://stackoverflow.com/questions/11111966/eclipse-arduino-linker-trouble
MASTER_OBJ= ./main/main.cc 
MASTER_LIBS= $(TARGET_LIBDIR) -larduino-master -lm
MASTER_INCFLAGS = -I $(TARGET_INCDIR) -I $(TARGET_INCDIR)/arduino

default: master_main

master_main: 
	mkdir -p $(TARGET_BUILDDIR)
	$(CC) $(MASTER_CFLAGS) $(MASTER_INCFLAGS) $^ -o $(TARGET_BUILDDIR)/main.elf $(MASTER_OBJ) -L $(MASTER_LIBS)
	avr-objcopy -O ihex $(TARGET_BUILDDIR)/main.elf $(TARGET_BUILDDIR)/main.hex

master_arduino: ARDUINO_CFLAGS=$(MASTER_MCU) $(MASTER_CPU_SPEED) -Os -w
master_arduino: $(ARDUINO_OBJ) 
	mkdir -p $(TARGET_BUILDDIR)
	avr-ar rcs $(TARGET_BUILDDIR)/$(MASTER_LIBNAME) $^
	mkdir -p $(TARGET_INCDIR)/arduino
	mkdir -p $(TARGET_LIBDIR)
	cp $(ARDUINO_SRC)*.h $(TARGET_INCDIR)/arduino
	cp $(TARGET_BUILDDIR)/$(MASTER_LIBNAME) $(TARGET_LIBDIR)
	rm $(ARDUINO_SRC)*.o

.PHONY: master_upload
master_upload:
	avrdude -V -F -D -p $(MASTER_MCU_TAG) -c $(MASTER_UPLOAD_PROTOCOL) -b $(MASTER_UPLOAD_BAUDRATE) -Uflash:w:$(TARGET_BUILDDIR)/main.hex -P$(MASTER_PORT)

.PHONY: clean
clean:
	# $(shell rm $(TARGET_INCDIR)/*.h 2> /dev/null)
	rm -rf $(TARGET_INCDIR)
	rm -rf $(TARGET_LIBDIR)
	rm -rf $(TARGET_BUILDDIR)

%.o : %.c
	$(CC) $< $(ARDUINO_CFLAGS) $(ARDUINO_INC) -c -o $@
    
%.o : %.cpp
	$(CXX) $< $(ARDUINO_CFLAGS) $(ARDUINO_INC) -c -o $@
