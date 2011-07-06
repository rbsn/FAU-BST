.PHONY: all clean tar xconfig transform

  # -------------------------------------------------------------------------- ##
 #                                                                            # #
# -------------------------------------------------------------------------- #  #
#                                                                            #  #
#                               M A K E F I L E                              #  #
#                                                                            # #
# -------------------------------------------------------------------------- ##

# ---------------------------------------------------------------------------
# Liste der Quelltexte:

ASM_SOURCES = $(shell find . -name "*.asm")
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

CXX = /proj/i4bst/bin/ag++
CXXFLAGS = -c --keep_woven -Wall -g -O3 -include "../include/autoconf.h" 
LD = 
LDFLAGS =
ASM = nasm
ASMOBJFORMAT = elf

OBJDIR = ./build

ARCHIV = FAU-BST.tar.gz
VPATH = $(sort $(dir $(STARTUP_SOURCE) $(CC_SOURCES)$(ASM_SOURCES)))

# ---------------------------------------------------------------------------


CC_OBJECTS=$(notdir $(CC_SOURCES:.cc=.o))
ASM_OBJECTS = $(patsubst %.asm,_%.o, $(notdir $(ASM_SOURCES)))         
OBJPRE = $(addprefix $(OBJDIR)/,$(ASM_OBJECTS) $(CC_OBJECTS))


TARGET=a.out


all: $(TARGET) 

$(OBJDIR)/%.o: %.cc
	@if test \( ! \( -d $(@D) \) \) ;then mkdir -p $(@D);fi
	$(CXX) -c $(CXXFLAGS) -o $@ $<
#	mv *.o $(OBJDIR)
$(OBJDIR)/_%.o : %.asm                                                                                                                                                                                                                   
	@echo "ASM      $@"
	@if test \( ! \( -d $(@D) \) \) ;then mkdir -p $(@D);fi
	$(ASM) -f $(ASMOBJFORMAT) -o $@ $<


$(TARGET): $(OBJPRE)
	$(CXX) $(LDFLAGS) -o $@ $(OBJPRE)


# ---------------------------------------------------------------------------
# Clean loescht die erzeugten Dateien

clean:
	rm -rf *.o
	rm -rf $(OBJDIR) 
	rm -rf $(TARGET)
	rm -rf $(ARCHIV)
	rm -rf outdir
	rm -rf include
	rm -rf .config

# ---------------------------------------------------------------------------
# Tar erzeugt ein Archiv

tar:
	tar -vcf $(ARCHIV) $(CC_SOURCES) $(H_SOURCES)


# ---------------------------------------------------------------------------
# Mconf erzeugt startet Kconfig

xconfig: FAU-BST.fm
	#/proj/i4bst/tools/bst-config/mconf FAU-BST.fm
	/proj/i4bst/tools/bst-config/qconf FAU-BST.fm
	mkdir -p include
	/proj/i4bst/tools/bst-config/conf -s FAU-BST.fm
	



# ---------------------------------------------------------------------------

transform: xconfig FAU-BST.cmp
	mkdir -p outdir
	perl /proj/i4bst/tools/bst-config/transform.pl -f .config -m FAU-BST.cmp -o outdir -i .
	cp Makefile outdir/Makefile

dbg: FAU-BST.cmp
	mkdir -p outdir
	perl /proj/i4bst/tools/bst-config/transform.pl -f .config -m FAU-BST.cmp -o outdir -i .
	cp Makefile outdir/Makefile
