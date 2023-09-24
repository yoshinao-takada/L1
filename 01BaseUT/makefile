CC = gcc
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
DEBUG_OBJECTS = $(DEBUG_OBJDIR)/01BaseUT.o $(DEBUG_OBJDIR)/ExecuteArrayUT.o \
	$(DEBUG_OBJDIR)/ExecuteDLinkUT.o $(DEBUG_OBJDIR)/ExecuteLogUT.o \
	$(DEBUG_OBJDIR)/ExecuteNumbersUT.o $(DEBUG_OBJDIR)/ExecuteNumbersCopyUT.o \
	$(DEBUG_OBJDIR)/ExecuteUtilsUT.o
DEBUG_TEST_OBJECTS = $(DEBUG_OBJDIR)/Numbers.o $(DEBUG_OBJDIR)/NumbersCopy.o $(DEBUG_OBJDIR)/Log.o \
	$(DEBUG_OBJDIR)/DLink.o $(DEBUG_OBJDIR)/Utils.o
RELEASE_OBJECTS = $(RELEASE_OBJDIR)/01BaseUT.o $(RELEASE_OBJDIR)/ExecuteArrayUT.o \
	$(RELEASE_OBJDIR)/ExecuteDLinkUT.o $(RELEASE_OBJDIR)/ExecuteLogUT.o \
	$(RELEASE_OBJDIR)/ExecuteNumbersUT.o $(RELEASE_OBJDIR)/ExecuteNumbersCopyUT.o \
	$(RELEASE_OBJDIR)/ExecuteUtilsUT.o
RELEASE_TEST_OBJECTS = $(RELEASE_OBJDIR)/Numbers.o $(RELEASE_OBJDIR)/NumbersCopy.o $(RELEASE_OBJDIR)/Log.o \
	$(RELEASE_OBJDIR)/DLink.o $(DEBUG_OBJDIR)/Utils.o
DEBUG_TARGET = $(DEBUG_BINDIR)/01BaseUT.exe
RELEASE_TARGET = $(RELEASE_BINDIR)/01BaseUT.exe

.PHONY	:	debug
.PHONY	:	release
.PHONY	:	clean_debug
.PHONY	:	clean_release

debug	:	$(DEBUG_TARGET)

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS) $(DEBUG_TEST_OBJECTS)
	mkdir -p $(DEBUG_BINDIR)
	$(CC) -o $@ $^ -lm -lpthread

$(DEBUG_OBJDIR)/01BaseUT.o	:	01BaseUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/ExecuteArrayUT.o	:	ExecuteArrayUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/ExecuteDLinkUT.o	:	ExecuteDLinkUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/ExecuteLogUT.o	:	ExecuteLogUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/ExecuteNumbersUT.o	:	ExecuteNumbersUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/ExecuteNumbersCopyUT.o	:	ExecuteNumbersCopyUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/ExecuteUtilsUT.o	:	ExecuteUtilsUT.c
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

release	:	$(RELEASE_TARGET)

$(RELEASE_TARGET)	:	$(RELEASE_OBJECTS) $(RELEASE_TEST_OBJECTS)
	$(CC) -o $@ $^ -lm -lpthread

$(RELEASE_OBJDIR)/01BaseUT.o	:	01BaseUT.c
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/ExecuteArrayUT.o	:	ExecuteArrayUT.c
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/ExecuteDLinkUT.o	:	ExecuteDLinkUT.c
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/ExecuteLogUT.o	:	ExecuteLogUT.c
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/ExecuteNumbersUT.o	:	ExecuteNumbersUT.c
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/ExecuteNumbersCopyUT.o	:	ExecuteNumbersCopyUT.c
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/ExecuteUtilsUT.o	:	ExecuteUtilsUT.c
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

ExecuteNumbersCopyUT.c	:	ExecuteNumbersCopyUT.c.md
	$(SLCPP) $<

ExecuteLogUT.c	:	ExecuteLogUT.c.md
	$(SLCPP) $<

clean_debug	:
	rm -f $(DEBUG_OBJECTS)
	rm -f ExecuteNumbersCopyUT.c ExecuteLogUT.c

clean_release	:
	rm -f $(RELEASE_OBJECTS)
	rm -f ExecuteNumbersCopyUT.c ExecuteLogUT.c

clean	:
	rm -f $(DEBUG_OBJECTS)
	rm -f $(RELEASE_OBJECTS)
	rm -f ExecuteNumbersCopyUT.c ExecuteLogUT.c
