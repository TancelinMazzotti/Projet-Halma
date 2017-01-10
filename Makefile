Halma-Game: menu.o donnees_partie.o utilitaire.o partie.o jeu.o main.o
	gcc -fopenmp -o Halma-Game menu.o partie.o utilitaire.o donnees_partie.o jeu.o main.o -Wall
	rm -rf *.o

windows: menu.o donnees_partie.o utilitaire.o partie.o jeu.o main.o
	gcc -fopenmp -o Halma-Game menu.o partie.o utilitaire.o donnees_partie.o jeu.o main.o -Wall
	del *.o

menu.o: menu.c
	gcc -o menu.o -c menu.c -Wall

donnees_partie.o: donnees_partie.c
	gcc -o donnees_partie.o -c donnees_partie.c -Wall

utilitaire.o: utilitaire.c
	gcc -fopenmp -o utilitaire.o -c utilitaire.c -Wall

partie.o: partie.c
	gcc -o partie.o -c partie.c -Wall

jeu.o: jeu.c
	gcc -o jeu.o -c jeu.c -Wall

main.o: main.c
	gcc -o main.o -c main.c -Wall

clear:
	rm -rf *.o
