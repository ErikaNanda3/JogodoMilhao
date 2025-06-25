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

extern const int NIVEIS_DO_JOGO;//total de niveis do jogo

typedef enum {PONTOS_BASE_MUITOFACIL = 100,PONTOS_BASE_FACIL = 200, PONTOS_BASE_MEDIO = 300,PONTOS_BASE_DIFICIL  = 400,PONTOS_BASE_MUITODIFICIL = 500,CUSTO_DICA_VALOR = 50}ValoresPontuacao;
//adicionei um enum pra pontuacao e valor da dica
 Pergunta* inserirPergunta(Pergunta* perguntasDoJogo, int* totalPerguntas);
 void listaPerguntas(Pergunta perguntas[], int totalPerguntasCad);
 Pergunta* alteraPergunta(Pergunta* perguntasDoJogo, int* totalPerguntas);
 Pergunta* pesquisarPergunta(Pergunta* perguntasDoJogo, int totalPerguntas);
 Pergunta* excluirPergunta(Pergunta* perguntasDoJogo, int* totalPeguntas);
 Pergunta* jogar(Pergunta* perguntasDoJogo, int totalPerguntas);
 Pergunta* carregarPerguntasDoCSV(char* nome_arquivo, int* total_perguntas);
 void salvarPerguntasBinario(char* nome_arquivo, Pergunta* perguntas, size_t total_perguntas);
 Pergunta* carregarPerguntasBinario(char* nome_arquivo, int* total_perguntas);
 int random(Pergunta* perguntasDoJogo, int totalPerguntas,  int level, int* perguntasUsadas, int numPerguntasUsadas);



 #endif // FUNCOES_H