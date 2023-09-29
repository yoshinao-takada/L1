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
DEBUG_OBJECTS = $(DEBUG_OBJDIR)/Numbers.o $(DEBUG_OBJDIR)/NumbersCopy.o $(DEBUG_OBJDIR)/Log.o \
	$(DEBUG_OBJDIR)/DLink.o $(DEBUG_OBJDIR)/Utils.o
RELEASE_OBJECTS = $(RELEASE_OBJDIR)/Numbers.o $(RELEASE_OBJDIR)/NumbersCopy.o $(RELEASE_OBJDIR)/Log.o \
	$(RELEASE_OBJDIR)/DLink.o $(DEBUG_OBJDIR)/Utils.o
DEBUG_TARGET = $(DEBUG_BINDIR)/01BaseDone
RELEASE_TARGET = $(RELEASE_BINDIR)/01BaseDone

.PHONY	:	debug
.PHONY	:	release
.PHONY	:	clean_debug
.PHONY	:	clean_release

debug	:	$(DEBUG_TARGET) $(INCDIR)/SLC/ExIO.h

$(DEBUG_TARGET)	:	$(DEBUG_OBJECTS)
	mkdir -p $(DEBUG_BINDIR)
	touch $@

$(DEBUG_OBJDIR)/Numbers.o	:	Numbers.c $(INCDIR)/SLC/Numbers.h $(INCDIR)/SLC/Array.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/NumbersCopy.o	:	NumbersCopy.c $(INCDIR)/SLC/NumbersCopy.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/Log.o	:	Log.c $(INCDIR)/SLC/Log.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/DLink.o	:	DLink.c $(INCDIR)/SLC/DLink.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

$(DEBUG_OBJDIR)/Utils.o	:	Utils.c $(INCDIR)/SLC/Utils.h
	mkdir -p $(DEBUG_OBJDIR)
	$(CC) $(DEBUG_CCFLAGS) -o $@ $<

release	:	$(RELEASE_TARGET) $(INCDIR)/SLC/ExIO.h

$(RELEASE_TARGET)	:	$(RELEASE_OBJECTS)
	mkdir -p $(RELEASE_BINDIR)
	touch $@

$(RELEASE_OBJDIR)/Numbers.o	:	Numbers.c $(INCDIR)/SLC/Numbers.h $(INCDIR)/SLC/Array.h
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/NumbersCopy.o	:	NumbersCopy.c $(INCDIR)/SLC/NumbersCopy.h
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/Log.o	:	Log.c $(INCDIR)/SLC/Log.h
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/DLink.o	:	DLink.c $(INCDIR)/SLC/DLink.h
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(RELEASE_OBJDIR)/Utils.o	:	Utils.c $(INCDIR)/SLC/Utils.h
	mkdir -p $(RELEASE_OBJDIR)
	$(CC) $(RELEASE_CCFLAGS) -o $@ $<

$(INCDIR)/SLC/Numbers.h	:	Numbers.h
	mkdir -p $(INCDIR)/SLC
	cp $< $@

$(INCDIR)/SLC/NumbersCopy.h	:	NumbersCopy.h.md
	mkdir -p $(INCDIR)
	$(SLCPP) $<

$(INCDIR)/SLC/Log.h	:	Log.h.md $(INCDIR)/SLC/errno.h
	mkdir -p $(INCDIR)
	$(SLCPP) $<

$(INCDIR)/SLC/errno.h	:	errno.h
	mkdir -p $(INCDIR)/SLC
	cp $< $@

$(INCDIR)/SLC/DLink.h	:	DLink.h
	mkdir -p $(INCDIR)/SLC
	cp $< $@

NumbersCopy.c	:	NumbersCopy.c.md
	$(SLCPP) $<

$(INCDIR)/SLC/Array.h	:	Array.h
	cp $< $@

$(INCDIR)/SLC/Utils.h	:	Utils.h
	cp $< $@

$(INCDIR)/SLC/ExIO.h	:	ExIO.h
	cp $< $@
	
clean_debug	:
	rm -f $(DEBUG_OBJECTS) $(DEBUG_TARGET)
	rm -f NumbersCopy.c
	rm -f $(INCDIR)/SLC/Numbers.h
	rm -f $(INCDIR)/SLC/NumbersCopy.h
	rm -f $(INCDIR)/SLC/Log.h
	rm -f $(INCDIR)/SLC/Array.h $(INCDIR)/SLC/Utils.h $(INCDIR)/SLC/ExIO.h

clean_release	:
	rm -f $(RELEASE_OBJECTS) $(RELEASE_TARGET)
	rm -f NumbersCopy.c
	rm -f $(INCDIR)/SLC/Numbers.h
	rm -f $(INCDIR)/SLC/NumbersCopy.h
	rm -f $(INCDIR)/SLC/Log.h
	rm -f $(INCDIR)/SLC/Array.h $(INCDIR)/SLC/Utils.h $(INCDIR)/SLC/ExIO.h

clean	:
	rm -f $(DEBUG_OBJECTS) $(DEBUG_TARGET)
	rm -f $(RELEASE_OBJECTS) $(RELEASE_TARGET)
	rm -f NumbersCopy.c
	rm -f $(INCDIR)/SLC/Numbers.h
	rm -f $(INCDIR)/SLC/NumbersCopy.h
	rm -f $(INCDIR)/SLC/Log.h
	rm -f $(INCDIR)/SLC/Array.h $(INCDIR)/SLC/Utils.h $(INCDIR)/SLC/ExIO.h
