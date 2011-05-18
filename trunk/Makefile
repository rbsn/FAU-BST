#.PHONY all clean

# --- MAKROS ---

# Set up Compiler
CC=g++	
CFLAGS=-c -Wall -g -O3 

LDFLAGS=

SOURCES=main.cc o_stream.cc cpu.cc

OBJECTS=$(SOURCES:.cc=.o)

TARGET=test


all: .cc $(TARGET)

.cc:
	$(CC) $(SOURCES)

$(TARGET): $(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@


.cc.o:
		$(CC) $(CFLAGS) $< -o $@


clean:
		rm -rf *.o $(TARGET)
