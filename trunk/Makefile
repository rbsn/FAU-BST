#.PHONY: all clean

# --------------------------------------------------------------------------- #
#																			  #
# 								M A K E F I L E 							  #
# 																			  #
# --------------------------------------------------------------------------- #

# ---------------------------------------------------------------------------
# Liste der Quelltexte:

CC_SOURCES = $(shell find . -name "*.cc")



# ---------------------------------------------------------------------------
# Liste der Makros:
# 		CXX: 		Zu benutzender C++-Compiler
# 		CXXFLAGS: 	Flags fuer den C++-Compileraufruf
# 		LD: 		Zu benutzender Linker
# 		LDFLAGS: 	Flags fuer den Linkeraufruf
# 		OBJDIR: 	Verzeichnis, in dem die Objektdateien abgelegt werden


CXX = g++
CXXFLAGS = -c -Wall -g -O3

LD = 
LDFLAGS =

OBJDIR = ./build


# ---------------------------------------------------------------------------


OBJECTS=$(CC_SOURCES:.cc=.o)

TARGET=a.out


all: $(TARGET) 

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@
	mkdir -p $(OBJDIR)
	mv *.o $(OBJDIR)


#.cc.o:
#	$(CXX) $(CXXFLAGS) $< -o $@



# ---------------------------------------------------------------------------
# Clean loescht die erzeugten Dateien

clean:
	rm -rf $(OBJDIR) 
	rm -rf $(TARGET)
