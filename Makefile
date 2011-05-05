#.PHONY all clean

# --- MAKROS ---

# Set up Compiler
CXX=g++	


SOURCES=main.cc hal.cc

OBJECTS=$(SOURCES:.cc=.o)

TARGET=test


all: .cc $(TARGET)

.cc:
	$(CC) $(SOURCES)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cc.o:
	#(CC) $< -o $@


clean:
	rm -rf *.o $(TARGET)
