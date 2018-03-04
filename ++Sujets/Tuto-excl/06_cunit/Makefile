
CC = gcc -g -Wall -Wextra -ansi
CCUNIT = $(CC) -lcunit

SRCDIR = src
OBJDIR = obj
BINDIR = bin
TESTDIR = tests

all: $(BINDIR)/graph_test

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $^

# $(OBJDIR)/main.o: $(SRCDIR)/main.c
# 	$(CC) -c $(SRCDIR)/main.c -o $(OBJDIR)/main.o
#
# $(OBJDIR)/graph_matrix.o: $(SRCDIR)/graph_matrix.c
#	$(CC) -c $(SRCDIR)/graph_matrix.c -o $(OBJDIR)/graph_matrix.o
#
# $(OBJDIR)/graph_list.o: $(SRCDIR)/graph_list.c
#	$(CC) -c $(SRCDIR)/graph_list.c -o $(OBJDIR)/graph_list.o


$(BINDIR)/graph_test: $(OBJDIR)/main.o $(OBJDIR)/graph_matrix.o
	$(CC) -o $@ $^

test: $(TESTDIR)/test

$(OBJDIR)/%.o: $(TESTDIR)/%.c
	$(CC) -c -o $@ $^

$(TESTDIR)/test : $(OBJDIR)/test.o $(OBJDIR)/graph_matrix.o
	$(CCUNIT) -o $@ $^

clean:
	rm $(OBJDIR)/*.o
	rm $(BINDIR)/graph_test
	rm $(TESTDIR)/test
