CC = gcc -Wall -Wextra -g
CCUNIT = -lcunit
CCSDL = `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer

SRCDIR = src
OBJDIR = obj
BINDIR = bin
TESTDIR = tests

all: $(BINDIR)/honshu $(BINDIR)/test


#Fichier Objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -c $(CCSDL) -o $@ $^

$(OBJDIR)/%.o: $(TESTDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -c $(CCSDL) -o $@ $^

#Fichier BIN
$(BINDIR)/honshu: $(OBJDIR)/main.o $(OBJDIR)/SDL.o $(OBJDIR)/game.o $(OBJDIR)/tuile.o  $(OBJDIR)/plateau.o $(OBJDIR)/score.o 
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CCSDL)

$(BINDIR)/test : $(OBJDIR)/test.o $(OBJDIR)/SDL.o $(OBJDIR)/game.o $(OBJDIR)/tuile.o  $(OBJDIR)/plateau.o $(OBJDIR)/score.o  
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CCUNIT) $(CCSDL)

clean:
	rm $(OBJDIR)/*.o
	rm $(BINDIR)/honshu
	rm $(TESTDIR)/test
