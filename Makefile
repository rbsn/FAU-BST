#.PHONY all clean

# --- MAKROS ---

# Set up Compiler
CXX=g++	


SOURCES=main.cc hal.cc

OBJECTS=$(SOURCES:.cc=.o)

TARGET=test


all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cc.o:
	#(CC) $< -o $@


clean:
	rm -rf *.o $(TARGET)
