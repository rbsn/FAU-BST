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

#TIP = Fliessband
TIP = Zusteller

CXX = g++
CXXFLAGS = -c -Wall -g -O3 -D$(TIP)

LD = 
LDFLAGS =

OBJDIR = ./build

ARCHIV = FAU-BST.tar.gz


# ---------------------------------------------------------------------------


CC_OBJECTS=$(notdir $(CC_SOURCES:.cc=.o))
OBJPRE		= $(addprefix $(OBJDIR)/,$(CC_OBJECTS))

TARGET=a.out


all: $(TARGET) 

$(OBJDIR)/%.o: %.cc
	@if test \( ! \( -d $(@D) \) \) ;then mkdir -p $(@D);fi
	$(CXX) -c $(CXXFLAGS) -o $@ $<
#	mv *.o $(OBJDIR)

$(TARGET): $(OBJPRE)
	$(CXX) $(LDFLAGS) -o $@ $(OBJPRE)


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
