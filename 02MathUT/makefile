CC = gcc
# markdown to c preprocessor
SLCPP = node ../99Tools/slcpp.js
INCDIR = ../include
INCFLAGS = -I$(INCDIR)
DEBUG_CCFLAGS = $(INCFLAGS) -g -c
RELEASE_CCFLAGS = $(INCFLAGS) -O3 -c
BINDIR = ../bin
DEBUG_BINDIR = $(BINDIR)/debug
RELEASE_BINDIR = $(BINDIR)/release
DEBUG_OBJDIR = $(DEBUG_BINDIR)/o
RELEASE_OBJDIR = $(RELEASE_BINDIR)/o
# testfixture objects
DEBUG_OBJECTS = $(DEBUG_OBJDIR)/02MathUT.o $(DEBUG_OBJDIR)/MiniBLASUT.o $(DEBUG_OBJDIR)/MiniLAUT.o \
	$(DEBUG_OBJDIR)/Geom3DUT.o
# test target objects
DEBUG_TEST_OBJECTS = \
	$(DEBUG_OBJDIR)/LinePlane.o \
	$(DEBUG_OBJDIR)/MiniLA.o $(DEBUG_OBJDIR)/MiniBLAS.o $(DEBUG_OBJDIR)/Geom3D.o \
	$(DEBUG_OBJDIR)/Numbers.o $(DEBUG_OBJDIR)/NumbersCopy.o $(DEBUG_OBJDIR)/Log.o \
	$(DEBUG_OBJDIR)/DLink.o $(DEBUG_OBJDIR)/Utils.o
# testfixture objects
RELEASE_OBJECTS = $(RELEASE_OBJDIR)/02MathUT.o $(RELEASE_OBJDIR)/MiniBLASUT.o $(RELEASE_OBJDIR)/MiniLAUT.o \
	$(RELEASE_OBJDIR)/Geom3DUT.o
# test target objects
RELEASE_TEST_OBJECTS = \
	$(RELEASE_OBJDIR)/LinePlane.o \
	$(RELEASE_OBJDIR)/MiniLA.o $(RELEASE_OBJDIR)/MiniBLAS.o $(RELEASE_OBJDIR)/Geom3D.o \
	$(RELEASE_OBJDIR)/Numbers.o $(RELEASE_OBJDIR)/NumbersCopy.o $(RELEASE_OBJDIR)/Log.o \
	$(RELEASE_OBJDIR)/DLink.o $(RELEASE_OBJDIR)/Utils.o
DEBUG_TARGET = $(DEBUG_BINDIR)/02MathUT.exe
RELEASE_TARGET = $(RELEASE_BINDIR)/02MathUT.exe

.PHONY	:	debug
.PHONY	:	clean_debug
debug	:	$(DEBUG_TARGET)

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS) $(DEBUG_TEST_OBJECTS)
	mkdir -p $(DEBUG_BINDIR)
	$(CC) -o $@ $^ -lm -lpthread

$(DEBUG_OBJDIR)/02MathUT.o	:	02MathUT.c
	mkdir -p $(DEBUG_BINDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/MiniBLASUT.o	:	MiniBLASUT.c
	mkdir -p $(DEBUG_BINDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/MiniLAUT.o	:	MiniLAUT.c
	mkdir -p $(DEBUG_BINDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/Geom3DUT.o	:	Geom3DUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

.PHONY	:	release
.PHONY	:	clean_release
release	:	$(RELEASE_TARGET)

$(RELEASE_TARGET)	:	$(RELEASE_OBJECTS) $(RELEASE_TEST_OBJECTS)
	mkdir -p $(RELEASE_BINDIR)
	$(CC) -o $@ $^ -lm -lpthread

$(RELEASE_OBJDIR)/02MathUT.o	:	02MathUT.c
	mkdir -p $(RELEASE_BINDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/MiniBLASUT.o	:	MiniBLASUT.c
	mkdir -p $(RELEASE_BINDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/MiniLAUT.o	:	MiniLAUT.c
	mkdir -p $(RELEASE_BINDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/Geom3DUT.o	:	Geom3DUT.c
	mkdir -p $(RELEASE_BINDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

MiniBLASUT.c	:	MiniBLASUT.c.md
	$(SLCPP) $<

MiniLAUT.c	:	MiniLAUT.c.md
	$(SLCPP) $<

Geom3DUT.c	:	Geom3DUT.c.md
	$(SLCPP) $<

clean_debug	:
	rm -f $(DEBUG_TARGET)
	rm -f $(DEBUG_OBJECTS)
	rm -f MiniBLASUT.c MiniLAUT.c Geom3DUT.c

clean_release	:
	rm -f $(RELEASE_TARGET)
	rm -f $(RELEASE_OBJECTS)
	rm -f MiniBLASUT.c MiniLAUT.c Geom3DUT.c

clean	:	clean_debug clean_release