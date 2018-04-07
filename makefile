CC = gcc -Wall -Wextra -g
CCUNIT = -lcunit

SRCDIR = src
OBJDIR = obj
BINDIR = bin
TESTDIR = tests

all: $(BINDIR)/honshu $(BINDIR)/test


#Fichier Objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -c -o $@ $^

$(OBJDIR)/%.o: $(TESTDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) -c -o $@ $^

#Fichier BIN
$(BINDIR)/honshu: $(OBJDIR)/main.o $(OBJDIR)/game.o $(OBJDIR)/tuile.o  $(OBJDIR)/plateau.o 
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $^

$(BINDIR)/test : $(OBJDIR)/test.o $(OBJDIR)/game.o $(OBJDIR)/tuile.o  $(OBJDIR)/plateau.o
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CCUNIT)

clean:
	rm $(OBJDIR)/*.o
	rm $(BINDIR)/honshu
	rm $(TESTDIR)/test
