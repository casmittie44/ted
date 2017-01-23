CC = gcc
CFLAGS = -g -Wall

default: edit

edit: 	editor.o void_node.o main.c
	$(CC) $(CFLAGS) -o edit editor.o void_node.o main.c

editor.o:      editor.h editor.c void_node.o
	$(CC) $(CFLAGS) -c editor.c

void_node.o:   assets/void_node.h assets/void_node.c
	$(CC) $(CFLAGS) -c assets/void_node.c

clean:
	rm -f *.o *~ edit a.out temp.txt
