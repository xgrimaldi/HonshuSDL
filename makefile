CC = gcc -Wall -Wextra
CCUNIT = -lcunit

SRCDIR = src
OBJDIR = obj
BINDIR = bin
TESTDIR = tests

all: $(BINDIR)/honshu_V2 $(BINDIR)/test
	
#Fichier Objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $^

$(OBJDIR)/%.o: $(TESTDIR)/%.c
	$(CC) -c -o $@ $^

#Fichier BIN
$(BINDIR)/honshu_V2: $(OBJDIR)/main.o $(OBJDIR)/game.o
	$(CC) -o $@ $^

$(BINDIR)/test : $(OBJDIR)/test.o $(OBJDIR)/game.o
	$(CC) -o $@ $^ $(CCUNIT)

clean:
	rm $(OBJDIR)/*.o
	rm $(BINDIR)/honshu_V2
	rm $(TESTDIR)/test

