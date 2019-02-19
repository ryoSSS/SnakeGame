all:Game.o function.o 
	gcc -o SnakeGame Game.o function.o pdcurses.a 
	
Game.o:Game.c
	gcc -c Game.c 

function.o:function.c
	gcc -c function.c 

play:all
	./Game



clean:
	rm -f SnakeGame Game.o function.o  save.bin
	
