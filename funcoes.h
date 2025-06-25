#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {MUITOFACIL = 1, FACIL, MEDIO, DIFICIL, MUITODIFICIL}Dificuldade;
typedef struct {

    char enunciado[71];
    char alternativa_escrita[4][21];///sao 4 opçoes e cada opçao tem 21 caracteres
    char alternativa_correta;
    Dificuldade nivel_dificuldade;
    char dica [200];

    
}Pergunta;// Estrutura de Pergunta

#define NIVEIS_DO_JOGO 5;//total de niveis do jogo
#define PONTOS_BASE_MUITOFACIL 100;
#define PONTOS_BASE_FACIL 200;
#define PONTOS_BASE_MEDIO 300;
#define PONTOS_BASE_DIFICIL 400;
#define PONTOS_BASE_MUITODIFICIL 500;
#define CUSTO_DICA_VALOR 50;


//adicionei um enum pra pontuacao e valor da dica
 Pergunta* inserirPergunta(Pergunta* perguntasDoJogo, int* totalPerguntas);
 void listaPerguntas(Pergunta perguntas[], int totalPerguntasCad);
 Pergunta* alteraPergunta(Pergunta* perguntasDoJogo, int* totalPerguntas);
 Pergunta* pesquisarPergunta(Pergunta* perguntasDoJogo, int totalPerguntas);
 Pergunta* excluirPergunta(Pergunta* perguntasDoJogo, int* totalPeguntas);
 Pergunta* jogar(Pergunta* perguntasDoJogo, int totalPerguntas);
 Pergunta* carregarPerguntasDoCSV(char* nome_arquivo, int* total_perguntas);
 void salvarPerguntasBinario(char* nome_arquivo, Pergunta* perguntas, int total_perguntas);
 Pergunta* carregarPerguntasBinario(char* nome_arquivo, int* total_perguntas);
 int random(Pergunta* perguntasDoJogo, int totalPerguntas,  int level, int* perguntasUsadas, int numPerguntasUsadas);



 #endif // FUNCOES_H