#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
/*Para gerenciar uma coleção de perguntas para o jogo, defina uma estrutura Pergunta
contendo, no mínimo: enunciado (texto), 4 alternativas (texto), letra da alternativa
correta(char), nível de dificuldade. O sistema deverá permitir cadastrar (inserir/ listar/
pesquisar/ alterar/ excluir) as perguntas disponíveis. Essa relação deve aumentar e
diminuir dinamicamen*/

typedef struct 
{
    char enunciado[31];
    char alternativa[21];
    char alternativa_correta;
    char nivel_dificuldade[21];

    
}Pergunta;

void leString(char texto[], int tam)
{
    fgets(texto[],21,stdin);
    texto[strcspn(texto,"\n")] = '\0';
    setbuf(stdin,NULL);

}

int main(){

    

    return 0;
}