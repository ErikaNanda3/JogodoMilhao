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
    char enunciado[71];
    char alternativa_escrita[4][21];
    char alternativa_correta;
    char nivel_dificuldade[21];

    
}Pergunta;

void leString(char texto[], int tam)
{
    fgets(texto,21,stdin);
    texto[strcspn(texto,"\n")] = '\0';
    setbuf(stdin,NULL);

}
Pergunta* inserePergunta(Pergunta* lista, int *totalPergunta ){

    Pergunta nova;

    printf("Digite o enunciado da pergunta: \n");
    leString(lista->enunciado,71);


    for (int i = 0; i < 4; i++)//sao 4 opções de alternativa 
    {
        printf("Digite a alternativa %c:" ,'A'+ i);//recebe a alternativa e armazena entre as 4 
        leString(nova.alternativa_escrita,21);

    }
    
    printf("Digite a alternativa correta: (A, B, C ou D)\n");
    scanf("%c",nova.alternativa_correta);
    getchar();

    printf("Digite o nivel de dificuldade: (muito dificil, dificil, medio, facil, muito facil)\n");
    leString(nova.nivel_dificuldade,sizeof(nova.nivel_dificuldade));

    lista = realloc(lista,(*totalPergunta + 1) * sizeof(Pergunta));
     if (lista == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    lista[*totalPergunta] = nova;
    (*totalPergunta)++;

    printf("Pergunta inserida");
   return lista;

}
int main(){
    Pergunta* lista = NULL;//incializa com vetor nulo 
    int totalPergunta = 0;

    return 0;
}