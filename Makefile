all: teste

teste: main.o src/interface/interface.o src/jogo/jogo.o src/jogo/tabuleiro.o
	gcc main.o src/interface/interface.o src/jogo/jogo.o src/jogo/tabuleiro.o -o teste

main.o: main.c src/jogo/jogo.h src/interface/interface.h
	gcc -c main.c -Isrc/

src/interface/interface.o: src/interface/interface.c src/interface/interface.h
	gcc -c src/interface/interface.c -Isrc/ -o src/interface/interface.o

src/jogo/jogo.o: src/jogo/jogo.c src/jogo/jogo.h
	gcc -c src/jogo/jogo.c -Isrc/ -o src/jogo/jogo.o

src/jogo/tabuleiro.o: src/jogo/tabuleiro.c src/jogo/tabuleiro.h
	gcc -c src/jogo/tabuleiro.c -Isrc/ -o src/jogo/tabuleiro.o

clean:
	@if exist *.o del /Q *.o
	@if exist src\interface\*.o del /Q src\interface\*.o
	@if exist src\jogo\*.o del /Q src\jogo\*.o
	@if exist teste del /Q teste
