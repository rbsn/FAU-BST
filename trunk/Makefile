.PHONY: all clean tar

  # -------------------------------------------------------------------------- ##
 #                                                                            # #
# -------------------------------------------------------------------------- #  #
#                                                                            #  #
#                               M A K E F I L E                              #  #
#                                                                            # #
# -------------------------------------------------------------------------- ##

# ---------------------------------------------------------------------------
# Liste der Quelltexte:

CC_SOURCES = $(shell find . -name "*.cc")
H_SOURCES = $(shell find . -name "*.h")


# ---------------------------------------------------------------------------
# Liste der Makros:
#		ARCHIV:		tar.gz-Archiv
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

ARCHIV = FAU-BST.tar.gz


# ---------------------------------------------------------------------------


CC_OBJECTS=$(notdir $(CC_SOURCES:.cc=.o))

TARGET=a.out


all: $(TARGET) 

$(TARGET): $(CC_OBJECTS)
	$(CXX) $(LDFLAGS) $(CC_OBJECTS) -o $@
	mkdir -p $(OBJDIR)
	mv *.o $(OBJDIR)



# ---------------------------------------------------------------------------
# Clean loescht die erzeugten Dateien

clean:
	rm -rf *.o
	rm -rf $(OBJDIR) 
	rm -rf $(TARGET)
	rm -rf $(ARCHIV)

# ---------------------------------------------------------------------------
# Tar erzeugt ein Archiv

tar:
	tar -vcf $(ARCHIV) $(CC_SOURCES) $(H_SOURCES)
