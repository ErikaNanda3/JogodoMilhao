
main: menuprincipal.o funcoes.o
	@echo "Gerando arquivo executavel"
	# Comando para linkar os objetos e criar o executável
	gcc menuprincipal.o funcoes.o -o main


menuprincipal.o: menuprincipal.c funcoes.h
	@echo "Compilando e gerando arq menuprincipal.o"
	gcc -c menuprincipal.c

funcoes.o: funcoes.c funcoes.h
	@echo "Compilando e gerando arq funcoes.o"
	gcc -c funcoes.c


clean:
	@echo "Apagando os objetos e executáveis antigos"
	rm -f *.o main


run:
	@echo "Executando o programa..."
	./main