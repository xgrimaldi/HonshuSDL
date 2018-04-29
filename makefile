CC = gcc -Wall -Wextra -g
CCUNIT = -lcunit
CCSDL = `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer

SRCDIRSDL= src/SDL
SRCDIR = src
OBJDIR = obj
BINDIR = .
TESTDIR = tests

all: $(BINDIR)/honshu $(BINDIR)/test $(BINDIR)/honshuSDL
	
#Fichier Objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -c -o $@ $^

#Fichier Objets
$(OBJDIR)/%.o: $(TESTDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -c -o $@ $^

#Fichier Objets
$(OBJDIR)/%.o: $(SRCDIRSDL)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -c $(CCSDL) -o $@ $^

#Fichier BIN
$(BINDIR)/honshu: $(OBJDIR)/main.o $(OBJDIR)/game.o $(OBJDIR)/tuile.o  $(OBJDIR)/plateau.o $(OBJDIR)/score.o $(OBJDIR)/SolvNaif.o
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $^

$(BINDIR)/honshuSDL: $(OBJDIR)/mainSDL.o $(OBJDIR)/SDL.o $(OBJDIR)/game.o $(OBJDIR)/tuile.o $(OBJDIR)/plateau.o $(OBJDIR)/score.o $(OBJDIR)/SolvNaif.o  
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CCSDL) 

$(BINDIR)/test : $(OBJDIR)/test.o $(OBJDIR)/game.o $(OBJDIR)/tuile.o  $(OBJDIR)/plateau.o $(OBJDIR)/score.o $(OBJDIR)/SolvNaif.o
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CCUNIT)
clean:
	rm $(OBJDIR)/*.o
	rm $(BINDIR)/honshu
	rm $(BINDIR)/honshuSDL
	rm $(BINDIR)/test

