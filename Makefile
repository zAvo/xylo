INCDIR			= ./include
SRCDIR			= ./src
OBJDIR			= ./obj
PROGDIR			= .

CC      		= gcc
CFLAGS			= -Wall
LFLAGS			= `allegro-config --libs` -lwiiuse
OPTFLAGS	        = -O3
PROG			= Xylo
RM			= rm -f


all: $(PROG)


$(PROG): title xylophone
	@echo
	@echo Compilazione avvenuta con successo.
	@echo Per lanciare il programma digitare sh start.sh

title:
	@echo ======================
	@echo Making Xylo executable
	@echo ======================

xylophone: main single credits init ingame icon
	@echo linking...
	$(CC) $(CFLAGS) $(OPTFLAGS) -o $(PROGDIR)/$(PROG) $(OBJDIR)/main.o $(OBJDIR)/single_buffer.o $(OBJDIR)/credits.o \
	$(OBJDIR)/triple_buffer.o $(OBJDIR)/initialization.o $(OBJDIR)/ingame.o $(OBJDIR)/allegro_icon.o $(LFLAGS)

main: $(SRCDIR)/main.c
	@echo compiling main.c...
	$(CC) $(CFLAGS) $(OPTFLAGS) -o $(OBJDIR)/main.o -c $(SRCDIR)/main.c

single: $(SRCDIR)/single_buffer.c
	@echo compiling single_buffer.c...
	$(CC) $(CFLAGS) $(OPTFLAGS) -o $(OBJDIR)/single_buffer.o -c $(SRCDIR)/single_buffer.c

credits: $(SRCDIR)/credits.c
	@echo compiling credits.c...
	$(CC) $(CFLAGS) $(OPTFLAGS) -o $(OBJDIR)/credits.o -c $(SRCDIR)/credits.c

init: $(SRCDIR)/initialization.c
	@echo compiling initialization.c...
	$(CC) $(CFLAGS) $(OPTFLAGS) -o $(OBJDIR)/initialization.o -c $(SRCDIR)/initialization.c

ingame: $(SRCDIR)/ingame.c
	@echo compiling ingame.c...
	$(CC) $(CFLAGS) $(OPTFLAGS) -o $(OBJDIR)/ingame.o -c $(SRCDIR)/ingame.c

icon: $(SRCDIR)/allegro_icon.c
	@echo compiling allegro_icon.c...
	$(CC) $(CFLAGS) $(OPTFLAGS) -o $(OBJDIR)/allegro_icon.o -c $(SRCDIR)/allegro_icon.c


main single credits init ingame: $(INCDIR)/constants.h $(INCDIR)/macros.h $(INCDIR)/header.h


clean:
	$(RM) $(OBJDIR)/*.o $(PROGDIR)/$(PROG)