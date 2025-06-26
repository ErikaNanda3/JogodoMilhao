main: menuPrincipal.o funcoes.o funcoeslib.o
@echo "Gerando arquivo executavel"
gcc *.o -o main

main.o: menuPrincipal.c
@echo "Compilando e gerando arq menuprincipal"
gcc -c menuPrincipal.c

funcoes.o: funcoes.c
@echo "Compilando e gerando arq funcoes.c"
gcc -c funcoes.c

funcoeslib.o: funcoes.h
echo "Compilando e gerando a biblioteca funcoes.h"
gcc -c funcoes.h

clean: 
@echo "Apagando os objetos executaveis antigos"
rm -f *.o main


run: 
	./main