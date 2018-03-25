CC = gcc -Wall -Wextra
CCUNIT = -lcunit

SRCDIR = src
OBJDIR = obj
BINDIR = bin
TESTDIR = tests

all: $(BINDIR)/honshu $(BINDIR)/test
	
#Fichier Objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $^

$(OBJDIR)/%.o: $(TESTDIR)/%.c
	$(CC) -c -o $@ $^

#Fichier BIN
$(BINDIR)/honshu: $(OBJDIR)/main.o $(OBJDIR)/game.o
	$(CC) -o $@ $^

$(BINDIR)/test : $(OBJDIR)/test.o $(OBJDIR)/game.o
	$(CC) -o $@ $^ $(CCUNIT)

clean:
	rm $(OBJDIR)/*.o
	rm $(BINDIR)/honshu
	rm $(TESTDIR)/test
