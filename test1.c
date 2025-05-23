#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
/*Para gerenciar uma coleção de perguntas para o jogo, defina uma estrutura Pergunta
contendo, no mínimo: enunciado (texto), 4 alternativas (texto), letra da alternativa
correta(char), nível de dificuldade. O sistema deverá permitir cadastrar (inserir/ Listar/
pesquisar/ alterar/ excluir) as perguntas disponíveis. Essa relação deve aumentar e
diminuir dinamicamen*/

typedef struct 
{
    char enunciado[71];
    char alternativa_escrita[4][21];///sao 4 opçoes e cada opçao tem 21 caracteres
    char alternativa_correta;
    char nivel_dificuldade[21];

    
}Pergunta;

void leString(char texto[], int tam)
{
    fgets(texto,tam,stdin);
    texto[strcspn(texto,"\n")] = '\0';
    setbuf(stdin,NULL);
    return;
}


Pergunta* inserirPergunta(Pergunta* perguntasDoJogo, int* totalPeguntas)
{
    Pergunta nova;
   
    printf("Digite o enunciado da pergunta: \n");
    leString(nova.enunciado, sizeof(nova.enunciado));

    for (int i = 0; i < 4; i++)
    {
        printf("Digite a alternativa %c: " ,'A' + i);//A+i transforma A em 0,1,2,3
        leString(nova.alternativa_escrita[i],sizeof(nova.alternativa_escrita[i]));
    }
    printf("Digite a alternativa correta: \n");
    scanf("%c",&nova.alternativa_correta);
    getchar();

    printf("Digite o nivel de dificuldade da sua pergunta: \n");
    leString(nova.nivel_dificuldade,sizeof(nova.nivel_dificuldade));

    perguntasDoJogo  = realloc(perguntasDoJogo, (*totalPeguntas + 1) * sizeof(Pergunta));
    if (perguntasDoJogo == NULL)
    {
        printf("Erro ao realocar a memoria ");
        exit(1);
    }
    
    
        perguntasDoJogo[*totalPeguntas] = nova;
        (*totalPeguntas)++;

        return perguntasDoJogo;


}

void listaPerguntas(Pergunta perguntas[], int totalPerguntasCad)
{


    if (totalPerguntasCad == 0)
    {
       printf("Nenhuma pergunta cadastrada\n");
       return;
    }
    printf("Lista Perguntas Cadastradas (%d): \n",totalPerguntasCad);
    for (int i = 0; i < totalPerguntasCad; i++)
    {
       printf("Pergunta %d : \n",i + 1);
       printf("Enunciado: %s",perguntas[i].enunciado);

       for (int j = 0; j < 4; j++)
       {
            printf("    %c) %s\n", 'A' + j, perguntas[i].alternativa_escrita[j]);
        
       }
    
       printf("A alternativa correta e: %c\n",perguntas[i].alternativa_correta);
       printf("Nivel de dificuldade da pergunta: %s",perguntas[i].nivel_dificuldade);

    }
    
    return;


}

int main(){
   Pergunta* perguntasDoJogo = (Pergunta*) malloc (50 *sizeof(Pergunta));
    if (perguntasDoJogo == NULL)
    {
        printf("Erro ao alocar memoria\n");
        exit(1);
    }
    

    int totalPergunta = 0;//contador de perguntas

    int opcao;
    do
    {
        printf(" 1 - Inserir pergunta \n");
        printf(" 2 - Listar Perguntas  \n");
        printf(" 0 - Sair \n");
        printf("Escolha uma opcao: \n");
        scanf("%d",&opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            perguntasDoJogo = inserirPergunta(perguntasDoJogo,&totalPergunta);
            break;
        case 2:
            listaPerguntas(perguntasDoJogo,totalPergunta);
            break;
        case 0:
            printf("Saindo do Jogo...\n");
            break;
        default:printf("Opcao invalida, tente novamente !\n");
            break;
        }
    } while (opcao != 0 );

    free(perguntasDoJogo);

    return 0;
}