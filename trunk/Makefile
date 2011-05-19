#.PHONY: all clean

# --------------------------------------------------------------------------- #
#																			  #
#								M A K E F I L E								  #
#																			  #
# --------------------------------------------------------------------------- #

# ---------------------------------------------------------------------------
# Liste der Quelltexte:

#CC_SOURCES = $(shell find . -name "*.cc")


# ---------------------------------------------------------------------------
# Liste der Makros:
#		CXX:		Zu benutzender C++-Compiler
#		CXXFLAGS:	Flags fuer den C++-Compileraufruf
#		LD:			Zu benutzender Linker
#		LDFLAGS:	Flags fuer den Linkeraufruf
#		OBJDIR:	 	Verzeichnis, in dem die Objektdateien abgelegt werden

CXX = g++	
CXXFLAGS = -Wall -g -O3 

LD = 
LDFLAGS =


#OBJDIR = ./build

#(OBJDIR)/%.o : %.cc	
#	$(VERBOSE) $(CXX) $(CXXFLAGS) $(OBJDIR)/$*.o $@ $<

SOURCES= main.cc o_stream.cc irq.cc cpu.cc

OBJECTS=$(SOURCES:.cc=.o)

TARGET=test

all: .cc $(TARGET)

.cc:
	$(CXX) $(SOURCES)

$(TARGET): $(OBJECTS)
		$(CXX) $(LDFLAGS) $(OBJECTS) -o $@


.cc.o:
		$(CXX) $(CXXFLAGS) $< -o $@


clean:
	rm -rf $(OBJECTS)
#	rm -rf $(OBJDIR)/*.o
	rm -rf a.out
