#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include <time.h>

#define NOME_ARQUIVO_BINARIO "questoes_milhao.bin"
#define NOME_ARQUIVO_CSV "questoesdoJogoDoMilhao.csv"

/*Para gerenciar uma coleção de perguntas para o jogo, defina uma estrutura Pergunta
contendo, no mínimo: enunciado (texto), 4 alternativas (texto), letra da alternativa
correta(char), nível de dificuldade. O sistema deverá permitir cadastrar (inserir/ Listar/
pesquisar/ alterar/ excluir) as perguntas disponíveis. Essa relação deve aumentar e
diminuir dinamicamente*/

int main(){
    int opcao;
    srand(time(NULL));

    Pergunta* perguntasDoJogo = NULL;
    int totalPergunta = 0;//contador de perguntas
    
    // 1. Carregar as perguntas do arquivo CSV primeiro
    printf("Tentando carregar perguntas do arquivo CSV: '%s'...\n", NOME_ARQUIVO_CSV);
    perguntasDoJogo = carregarPerguntasDoCSV(NOME_ARQUIVO_CSV, &totalPergunta);

    // Verifica se o carregamento do CSV falhou ou se o arquivo estava vazio
    if (perguntasDoJogo == NULL || totalPergunta == 0) {

        printf("Nenhuma pergunta carregada do CSV. Iniciando com um banco de dados vazio.\n");

        // Alocar uma capacidade inicial se nenhum arquivo foi carregado
        perguntasDoJogo = (Pergunta*) malloc(50 * sizeof(Pergunta));

        if (perguntasDoJogo == NULL) {

            perror("Erro ao alocar memoria inicial para perguntas.");
            exit(1);
        }

        totalPergunta = 0; // Garante que o contador está em zero
    } else {

        printf("Carregadas %d perguntas do arquivo CSV.\n", totalPergunta);
    }

    do
    {
        printf(" 1 - Inserir Pergunta \n");
        printf(" 2 - Listar Perguntas  \n");
        printf(" 3 - Alterar Pergunta \n" );
        printf(" 4 - Pesquisar Pergunta \n" );
        printf(" 5 - Apagar Pergunta \n" );
        printf(" 6 - Jogar \n");
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
        case 3: 
            alteraPergunta(perguntasDoJogo,&totalPergunta);
            break;
        case 4:
            pesquisarPergunta(perguntasDoJogo,totalPergunta);
            break;
        case 5:
           excluirPergunta(perguntasDoJogo, &totalPergunta);
            break;    
        case 6:
            printf("Quem quer ser um milionario?\n");
            printf("Vamos jogar!\n");
            printf("O jogo comeca na dificuldade mais facil, e quando voce errar alguma das perguntas o jogo diminuira a dificuldade.\n");
            printf("Boa sorte!\n");
            jogar(perguntasDoJogo,totalPergunta);
            break;
        case 0:
            printf("Saindo do Jogo...\n");
            salvarPerguntasBinario(NOME_ARQUIVO_BINARIO, perguntasDoJogo, totalPergunta);
            break;
        default:
            printf("Opcao invalida, tente novamente !\n");
            break;
        }//switch
    }//do 
    while (opcao != 0 );

    free(perguntasDoJogo);
    return 0;
}