#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para usar toupper
#include "funcoes.h"

const int NIVEIS_DO_JOGO = 5; // Total de níveis do jogo

void leString(char texto[], int tam)
{
    fgets(texto,tam,stdin);
    texto[strcspn(texto,"\n")] = '\0';
    setbuf(stdin,NULL);
    return;
}//leString

Pergunta* inserirPergunta(Pergunta* perguntasDoJogo, int* totalPerguntas)//retorna ponteiro para Pergunta
{
    Pergunta nova;
    int nivel_dif_temp;

    printf("Digite o enunciado da pergunta: \n");
    leString(nova.enunciado, sizeof(nova.enunciado));

    for (int i = 0; i < 4; i++)
    {
        printf("Digite a alternativa %c: " ,'A' + i);//A+i transforma A em 0,1,2,3
        leString(nova.alternativa_escrita[i],sizeof(nova.alternativa_escrita[i]));

    }//for

    printf("Digite a alternativa correta: \n");
    scanf("%c",&nova.alternativa_correta);
    setbuf(stdin,NULL);

    printf("Digite o nivel de dificuldade da sua pergunta:(1 a 5, sendo 1 muito facil, 2 facil,...) \n");
    printf("Escolha uma opcao de 1 a 5: \n");
    scanf("%d",&nivel_dif_temp);

    if (nivel_dif_temp >= 1 && nivel_dif_temp <= 5){ 

        nova.nivel_dificuldade = nivel_dif_temp;
    } 
    else {
        printf("Nivel de dificuldade invalido. Definido como 3 (MEDIO) por padrao.\n");
        nova.nivel_dificuldade = 3;//caso de erro ele entra no nivel 3 

    }
    printf("Digite a nova dica a ser adicionada: \n (no maximo 200 caracteres)");
    leString(nova.dica,sizeof(nova.dica));

    perguntasDoJogo  = realloc(perguntasDoJogo, (*totalPerguntas + 1) * sizeof(Pergunta));
   
    if (perguntasDoJogo == NULL){

        perror("Erro ao realocar a memoria ");
        exit(1);
    }//if
    
    
        perguntasDoJogo[*totalPerguntas] = nova;
        (*totalPerguntas)++;

        return perguntasDoJogo;


}//inserePergunta

void listaPerguntas(Pergunta perguntas[], int totalPerguntasCad)
{
    

    if (totalPerguntasCad == 0)
    {
       perror("Nenhuma pergunta cadastrada\n");
       return;
    }
    printf("Lista Perguntas Cadastradas (%d): \n",totalPerguntasCad);
    for (int i = 0; i < totalPerguntasCad; i++)
    {
       printf("Pergunta %d : \n",i + 1);
       printf("Enunciado: %s\n",perguntas[i].enunciado);

       for (int j = 0; j < 4; j++)
       {
            printf("    %c) %s\n", 'A' + j, perguntas[i].alternativa_escrita[j]);
        
       }
    
       printf("A alternativa correta e: %c\n",perguntas[i].alternativa_correta);
       printf("Nivel de dificuldade da pergunta: %d",perguntas[i].nivel_dificuldade);
       

    }
    
    return;


}//listaPergunta

Pergunta* alteraPergunta(Pergunta* perguntasDoJogo, int* totalPerguntas)
{
    int nivel_dif_temp;

    int indiceAlterado;

    if (totalPerguntas == 0)
    {
        printf("Nao existem perguntas para serem alteradas \n");
        return perguntasDoJogo;
    }
    
    printf("Alterar Pergunta: \n");
    printf("Digite o numero da pergunta que deseja alterar (1 a %d)",*totalPerguntas);
    scanf("%d",&indiceAlterado);

    if (indiceAlterado < 1 || indiceAlterado > *totalPerguntas)
    {
        perror("Numero de pergunta invalido, por favor tente novamente. \n");
        return perguntasDoJogo;        
    }
    
    printf("Alterando a Pergunta %d: \n",indiceAlterado);
    printf("Enunciado atual: %s\n",perguntasDoJogo[indiceAlterado - 1].enunciado);

    printf("Digite o Novo enunciado: \n");
    leString(perguntasDoJogo[indiceAlterado - 1].enunciado,sizeof(perguntasDoJogo[indiceAlterado - 1]));
     for (int i = 0; i < 4; i++)
    {
        printf("Digite a Nova alternativa %c: ", 'A' + i);
        leString(perguntasDoJogo[indiceAlterado - 1].alternativa_escrita[i], sizeof(perguntasDoJogo[indiceAlterado - 1].alternativa_escrita[i]));
    }

    printf("Digite a Nova alternativa correta (A, B, C ou D): \n");
    scanf(" %c", &perguntasDoJogo[indiceAlterado - 1].alternativa_correta);
    setbuf(stdin, NULL); // Limpar o buffer após scanf

     printf("Digite o NOVO nivel de dificuldade da pergunta (1 a 5, onde 1=MUITO FACIL, 5=MUITO DIFICIL): \n");
    printf("Escolha uma opcao (1-5): ");
    scanf("%d", &nivel_dif_temp);
    if (nivel_dif_temp >= 1 && nivel_dif_temp <= 5) 
    {
        perguntasDoJogo[indiceAlterado - 1].nivel_dificuldade = nivel_dif_temp;
    } 
    else
    {
        printf("Nivel de dificuldade invalido. Mantido o nivel anterior ou 3 (MEDIO) se nao houver.\n");
        perguntasDoJogo[indiceAlterado - 1].nivel_dificuldade = 3;
    }
    printf("Digite a Nova dica: \n(No maximo 200 caracteres)");
    leString(perguntasDoJogo[indiceAlterado - 1].dica,sizeof(perguntasDoJogo[indiceAlterado-1].dica));
   

    printf("Pergunta %d alterada com sucesso!\n", indiceAlterado);
    return perguntasDoJogo;
} // alteraPergunta

Pergunta* pesquisarPergunta(Pergunta* perguntasDoJogo, int totalPerguntas)
{
    if (totalPerguntas == 0)
    {
        printf("Nenhuma pergunta cadastrada.\n");
        return perguntasDoJogo;
    }

    char pesquisa[200];
    printf("Digite o enunciado da pergunta que deseja pesquisar: ");
    leString(pesquisa, sizeof(pesquisa));

    for (int i = 0; i < totalPerguntas; i++)
    {
        if (strstr(perguntasDoJogo[i].enunciado, pesquisa) != NULL)
        {
            printf("Pergunta %d encontrada:\n", i + 1);
            printf("Enunciado: %s\n", perguntasDoJogo[i].enunciado);
            return perguntasDoJogo;
        }
    }

    printf("Nenhuma pergunta encontrada com o enunciado '%s'.\n", pesquisa);
    return perguntasDoJogo;
} // pesquisarPergunta

Pergunta* excluirPergunta(Pergunta* perguntasDoJogo, int* totalPeguntas) // totalPeguntas é ponteiro
{
    int indice_exclui;

    if (*totalPeguntas == 0) 
    {
        printf("Nao existem perguntas para serem excluidas.\n");
        return perguntasDoJogo;
    }

    printf("\n--- Excluir Pergunta ---\n");
    printf("Digite o numero da pergunta que deseja excluir (1 a %d): ", *totalPeguntas); // Desreferenciar totalPeguntas
    scanf("%d", &indice_exclui);
    setbuf(stdin,NULL);

    
    if (indice_exclui < 1 || indice_exclui > *totalPeguntas)
    {
        printf("Numero da pergunta invalido, tente novamente.\n");
        return perguntasDoJogo;
    }

    // Move os elementos posteriores uma posição para trás
    for (int i = indice_exclui - 1; i < (*totalPeguntas - 1); i++)
    {
        perguntasDoJogo[i] = perguntasDoJogo[i + 1];
    }
    (*totalPeguntas)--; // Diminui o contador de perguntas

    if (*totalPeguntas == 0)
    {
        free(perguntasDoJogo);
        perguntasDoJogo = NULL;
        printf("Pergunta %d excluida com sucesso! Todas as perguntas foram removidas.\n", indice_exclui);
        return perguntasDoJogo; 
    }
    else{
        
        Pergunta* temporario = (Pergunta*) realloc(perguntasDoJogo, (*totalPeguntas) * sizeof(Pergunta));
        
        if (temporario == NULL){
            
            printf("Erro ao realocar memoria após exclusao! \n");
           
            return perguntasDoJogo;
        }
        else{
            
            perguntasDoJogo = temporario;
        }
        
        printf("Pergunta %d excluida com sucesso!\n", indice_exclui);
        
        return perguntasDoJogo;
    }//fecha else
}
int randomizer(Pergunta* perguntasDoJogo, int totalPerguntas, int level, int* perguntasUsadas, int numPerguntasUsadas){
    if (totalPerguntas == 0) {
        return -1; // Não há perguntas cadastradas
    }
    if (perguntasDoJogo == NULL) {
        printf("Perguntas no jogo ta NULL no randomizer\n"); // Debugging
        return -1;
    }

    

    int *indicesNivel = (int*)malloc(totalPerguntas * sizeof(int));
    int countNivel = 0;

    if (indicesNivel == NULL) {
        perror("Erro ao alocar memoria para indices de nivel");
       exit(1); 
    }
    

    for (int i = 0; i < totalPerguntas; i++) {
        if ((int)perguntasDoJogo[i].nivel_dificuldade == level) {
          
            int usada = 0;
            for (int j = 0; j < numPerguntasUsadas; j++) {
                if (perguntasUsadas[j] == (int)i) {
                    usada = 1;
                    break;
                }
            }
            if (!usada) {
                indicesNivel[countNivel++] = i;
            }
        }
    }

    if (countNivel == 0) {
        free(indicesNivel);
        return -1; // Nenhuma pergunta disponível para este nível (ou todas já foram usadas)
    }


    int indiceSorteadoNaLista = rand() % countNivel;
    int indiceRealDaPergunta = indicesNivel[indiceSorteadoNaLista];

    free(indicesNivel);
    return indiceRealDaPergunta;
}
Pergunta* jogar(Pergunta* perguntasDoJogo, int totalPerguntas)
{
    int level = MUITOFACIL; // Começa no nível Muito Fácil (1)
    int pontuacao = 0;
    char respChar; // Para a resposta do usuário (A, B, C, D)
    char acaoUsuario[10]; // Buffer para ler dica ,50/50, pular ou a resposta digitada
    int indicePerguntaAtual; // Índice da pergunta sorteada 
    int numPerguntasAcertadas = 0; // Contador de perguntas acertadas 
    int errou = 0; //indicar que o jogador errou e perdeu o jogo
    int *perguntasJaUsadas = NULL; // Guarda os indices de perguntas ja usadas
    int numPerguntasUsadas = 0; // Contador de perguntas já usadas

    

    if (totalPerguntas == 0)
    {
        printf("Nenhuma pergunta cadastrada para jogar. Cadastre perguntas primeiro.\n");
        return perguntasDoJogo;
    }
    //pra evitar q repita perguntas

    perguntasJaUsadas = (int*)malloc(totalPerguntas * sizeof(int));
    if (perguntasJaUsadas == NULL) {
        perror("Erro ao alocar memoria para controle de perguntas usadas");
        return perguntasDoJogo; // Retorna em caso de erro grave
    }//if

    printf("\nQUEM QUER SER UM MILIONARIO?!\n");
    printf("Acerte %d perguntas para se tornar um milionario!\n", NIVEIS_DO_JOGO);  
    printf("Custo das ajudas (dica/50-50/pular): %d pontos.\n", CUSTO_DICA_VALOR);

    printf("Pontuacao inicial: %d\n", pontuacao);

   //loop pra enquanto n atingir dificuldade maxima o acertar o tanto necessario de perguntas
  
    while (level <= MUITODIFICIL && numPerguntasAcertadas < NIVEIS_DO_JOGO && !errou)
    {
        printf("\n--- Nivel de Dificuldade: %d (%s) ---\n", level,
               (level == MUITOFACIL ? "MUITO FACIL" :
                level == FACIL ? "FACIL" :
                level == MEDIO ? "MEDIO" :
                level == DIFICIL ? "DIFICIL" : "MUITODIFICIL"));

        // Sorteia uma pergunta do nível atual
        indicePerguntaAtual = randomizer(perguntasDoJogo, totalPerguntas, level, perguntasJaUsadas, numPerguntasUsadas);

        if (indicePerguntaAtual == -1) {
            printf("Nao ha mais perguntas disponiveis para o nivel %d. Jogo encerrado.\n", level);
            break; // Sai do loop principal se não tem mais perguntas desse nível 
        }//if

        // Adiciona o índice da pergunta sorteada à lista de perguntas que ja foram usadas pra n repetir pergunta
        perguntasJaUsadas[numPerguntasUsadas++] = indicePerguntaAtual;

        int respostaValidaRecebida = 0; // ver se o jogador tento responder
        do {
            printf("\nPergunta:\n%s\n", perguntasDoJogo[indicePerguntaAtual].enunciado);
            // Exibir alternativas originais
            for (int j = 0; j < 4; j++)
            {
                printf("  %c) %s\n", 'A' + j, perguntasDoJogo[indicePerguntaAtual].alternativa_escrita[j]);
            }//for

            printf("Pontuacao atual: %d\n", pontuacao);
            printf("Escolha sua acao: (A, B, C, D para responder) | 'dica' | '50/50' | 'pular': ");
            leString(acaoUsuario, sizeof(acaoUsuario)); // Lê a ação

            if (strcasecmp(acaoUsuario, "dica") == 0) {
               
                if (pontuacao >= CUSTO_DICA_VALOR) {
                    pontuacao -= CUSTO_DICA_VALOR;
                    printf("\nDICA:\n%s\n", perguntasDoJogo[indicePerguntaAtual].dica);
                    printf("Pontuacao atual: %d. Responda ou escolha outra acao.\n", pontuacao);
                    printf("Pressione ENTER para continuar com a mesma pergunta.\n");
                    setbuf(stdin,NULL);
                    getchar();
                }//if 
                else 
                {
                    printf("Pontos insuficientes para usar a dica! Pontuacao atual: %d. Responda ou escolha use outra dica.\n", pontuacao);
                }//else


            }//if 
            else if (strcasecmp(acaoUsuario, "50/50") == 0) 
            {
                if (pontuacao >= CUSTO_DICA_VALOR) 
                {
                    pontuacao -= CUSTO_DICA_VALOR;
                    printf("\nDuas alternativas incorretas foram eliminadas.\n");
                    
                    // Identifica a alternativa correta
                    char correta = perguntasDoJogo[indicePerguntaAtual].alternativa_correta;
                    
                    // Armazenar as alternativas para exibir sem as eliminadas
                    char altsParaExibir[4][21]; // Copia das alternativas
                   
                    
                    // Copia todas as alternativas inicialmente
                    for(int j=0; j<4; j++)
                    {
                        strcpy(altsParaExibir[j], perguntasDoJogo[indicePerguntaAtual].alternativa_escrita[j]);
                    }//for

                    // Encontra e "elimina" duas alternativas incorretas
                    int eliminadasCount = 0;
                    int alternativasIndice[4] = {0, 1, 2, 3}; // A, B, C, D
                    
                    // Embaralha os índices para escolher aleatoriamente quais eliminar
                    for(int j=0; j<4; j++)
                    {
                        int r = rand() % 4;
                        int temp = alternativasIndice[j];
                        alternativasIndice[j] = alternativasIndice[r];
                        alternativasIndice[r] = temp;
                    }//for

                    for(int j=0; j<4 && eliminadasCount < 2; j++)
                    {
                        int indiceAleatorio = alternativasIndice[j]; // Pega um índice aleatório
                        if (('A' + indiceAleatorio) != correta) 
                        { // Se não for a correta
                            strcpy(altsParaExibir[indiceAleatorio], "(ELIMINADA)"); // Marca como eliminada
                            eliminadasCount++;
                        }//if
                    }//for

                    // Exibe as alternativas com as eliminadas marcadas
                    for(int j=0; j<4; j++)
                    {
                        printf("  %c) %s\n", 'A' + j, altsParaExibir[j]);
                    }//for
                    printf("Pontuacao atual: %d. Responda ou escolha outra acao.\n", pontuacao);
                }//if
                else
                {
                    printf("Pontos insuficientes para usar a dica 50/50! Pontuacao atual: %d.\n", pontuacao);
                }//else


            }//else if
          else if (strcasecmp(acaoUsuario, "pular") == 0) {
                if (pontuacao >= CUSTO_DICA_VALOR)
                {
                    pontuacao -= CUSTO_DICA_VALOR;
                    printf("\n--- QUESTAO PULADA! ---\n");
                    printf("Proxima pergunta... Pontuacao atual: %d.\n", pontuacao);
                    numPerguntasAcertadas++;//aumenta qnt de resp acertadas
                    level++;//aumenta level
                    respostaValidaRecebida = 1;//pula questao entao aqui fica 1 (um "break" so que com o controlador de resposta) 
                }//if
                else 
                {
                    printf("Pontos insuficientes para pular a questao! Pontuacao atual: %d.\n", pontuacao);// se n tem pontos continua pedindo resposta
                   
                }//else

            }//else if 
                else 
                { // Assume que é uma tentativa de resposta (A, B, C, D)
                if (strlen(acaoUsuario) == 1 && (toupper(acaoUsuario[0]) >= 'A' && toupper(acaoUsuario[0]) <= 'D'))
                {
                    respChar = toupper(acaoUsuario[0]);
                    respostaValidaRecebida = 1;// se for uma resposta valida, no caso errada ou certa ele entende que recebeu a resposta e da o "break"
                }//if 
                else 
                {
                    printf("Entrada invalida. Por favor, digite A, B, C, D, 'dica', '50/50' ou 'pular'.\n");
                }//else

                }//else
        }//do 
        while (!respostaValidaRecebida); // Repete até que uma resposta válida seja dada ou a pergunta seja pulada

  
     
        if (strcasecmp(acaoUsuario, "pular") == 0) 
        {
             continue; //avança level
        }//if


        // Verifica se a resposta está correta
        if (respChar == perguntasDoJogo[indicePerguntaAtual].alternativa_correta) 
        {
            printf("\nVOCE ACERTOU! Parabens!\n");
            // Adiciona pontos com base no nível, usando os valores do enum
            switch (level) 
            {
                case MUITOFACIL:    pontuacao += PONTOS_BASE_MUITOFACIL; break;//case 1
                case FACIL:         pontuacao += PONTOS_BASE_FACIL;      break;//case 2
                case MEDIO:         pontuacao += PONTOS_BASE_MEDIO;      break;//case 3
                case DIFICIL:       pontuacao += PONTOS_BASE_DIFICIL;    break;//case 4
                case MUITODIFICIL:  pontuacao += PONTOS_BASE_MUITODIFICIL; break;//case 5
                default: break;
            }//switch
            printf("Pontuacao atual: %d\n", pontuacao);
            numPerguntasAcertadas++;
            level++; // Avança para o próximo nível de dificuldade
        }//if
        else 
        {
            printf("\nVOCE ERROU! A alternativa correta era: %c\n", perguntasDoJogo[indicePerguntaAtual].alternativa_correta);
            errou = 1; // Define se perdeu
        }//else
    }//while (Que fica infinito pro jogo rodar)

    // Mensagem final do jogo
    if (numPerguntasAcertadas >= NIVEIS_DO_JOGO) 
    {
        printf("PARABENS! VOCE SE TORNOU UM MILIONARIO!\n");
        printf("Pontuacao final: %d\n", pontuacao);
       
    }//if 
    else if (errou) 
    {
       
        printf("QUE PENA! VOCE PERDEU O JOGO.\n");
        printf("Sua pontuacao final foi: %d\n", pontuacao);
        printf("Tente novamente!\n");
        
    }//else if 
    else 
    {
        printf("\nJogo encerrado antes de completar todos os niveis. Pontuacao final: %d\n", pontuacao);
    }//else

    free(perguntasJaUsadas);
    return perguntasDoJogo;
}//jogar

void salvaJogoemCSV(Pergunta* perguntasDoJogo, int totalPerguntas, const char* nomeArquivo) {
    
    FILE* arquivo = fopen(nomeArquivo, "w");
    
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para salvar o jogo");
        return;
    }

    fprintf(arquivo, "Enunciado;Alternativa A;Alternativa B;Alternativa C;Alternativa D;Alternativa Correta;Nivel de Dificuldade;Dica\n");

    for (int i = 0; i < totalPerguntas; i++) {
        fprintf(arquivo, "%s;%s;%s;%s;%s;%c;%d;%s\n",
                perguntasDoJogo[i].enunciado,
                perguntasDoJogo[i].alternativa_escrita[0],
                perguntasDoJogo[i].alternativa_escrita[1],
                perguntasDoJogo[i].alternativa_escrita[2],
                perguntasDoJogo[i].alternativa_escrita[3],
                perguntasDoJogo[i].alternativa_correta,
                perguntasDoJogo[i].nivel_dificuldade,
                perguntasDoJogo[i].dica);
    }

    fclose(arquivo);
    printf("Jogo salvo com sucesso em '%s'.\n", nomeArquivo);
} // salvaJogoemCSV
  

Pergunta* carregarArquivoCSV(char* nome_arquivo, int* total_perguntas) {
   
    FILE *arquivo = fopen("questoesjogodomilhao.csv", "r");
   
    if (arquivo == NULL) {
   
        perror("Erro ao abrir o arquivo CSV de questoes");
        *total_perguntas = 0;
   
        return NULL;
    }

    char linha[2025]; // Buffer para ler cada linha do CSV
    int contador = 0;
    int capacidade_atual = 0;
   
    Pergunta* perguntas = NULL; // Começa com NULL, a alocação será dinâmica

    // Pular a linha de cabeçalho, se houver
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        
        printf("Arquivo CSV vazio ou erro de leitura do cabeçalho.\n");
        fclose(arquivo);
        
        *total_perguntas = 0;
        return NULL;
    }// fecha if

    linha[strcspn(linha, "\n")] = 0; // Remove o '\n' do cabeçalho 

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
   
        linha[strcspn(linha, "\n")] = 0; // Remover o '\n' do final da linha
        // Realoca mais memória se necessário
        if (contador >= capacidade_atual) {
           
            capacidade_atual += 50; // Aumenta a capacidade em 50 perguntas
           
            Pergunta* temporario = (Pergunta*) realloc(perguntas,(unsigned int)capacidade_atual * sizeof(Pergunta));
          
            if (temporario == NULL) {
               
                perror("Erro de realocacao de memoria ao carregar perguntas do CSV");
                fclose(arquivo);
                
                *total_perguntas = contador; // Retorna o que conseguiu carregar até agora
               
                return perguntas;
            }
            perguntas = temporario;
        }

        // análise da linha CSV: enunciado, 4 alternativas, correta, dificuldade,dica
        char *token;
        char *linha_copy = strdup(linha); // Duplica a linha para strtok (que modifica a string)
        
        if (linha_copy == NULL) {
            perror("Erro ao duplicar linha para parsing CSV. Pulando linha.");
            continue;
        }
        
        // 1. Enunciado
        token = strtok(linha_copy, ";");
        if (token) strncpy(perguntas[contador].enunciado, token, sizeof(perguntas[contador].enunciado) - 1);
        perguntas[contador].enunciado[sizeof(perguntas[contador].enunciado) - 1] = '\0';

        // 2. Alternativas (4 campos)
        for (int i = 0; i < 4; i++) {
            token = strtok(NULL, ";");
        
        if (token) strncpy(perguntas[contador].alternativa_escrita[i], token, sizeof(perguntas[contador].alternativa_escrita[i]) - 1);
        
            perguntas[contador].alternativa_escrita[i][sizeof(perguntas[contador].alternativa_escrita[i]) - 1] = '\0';
        }

        // 3. Alternativa Correta
        token = strtok(NULL, ";");
        
        if (token && strlen(token) > 0) {
        
            perguntas[contador].alternativa_correta = toupper(token[0]);
        
        } else {
        
            perguntas[contador].alternativa_correta = '\0'; // Campo vazio ou inválido
        }

        // 4. Nível de Dificuldade 
        token = strtok(NULL, "\n"); // Delimita pelo '\n' para pegar o final da linha
        
        if (token) {
           
            int nivel = atoi(token); // Usando 'nivel' como preferiu
           
            if (nivel >= MUITOFACIL && nivel <= MUITODIFICIL) {

                perguntas[contador].nivel_dificuldade = (Dificuldade)nivel;

            } else {

                perguntas[contador].nivel_dificuldade = MEDIO; // Padrão se o nível for inválido
               
                fprintf(stderr, "Aviso: Nivel medio de dificuldade invalido '%s' na linha %d. Usando PADRAO (%d).\n", token, contador + 2, MEDIO);
            }
        } else {

            perguntas[contador].nivel_dificuldade = MEDIO; // Padrão se o token estiver faltando
           
            fprintf(stderr, "Aviso: Nivel medio de dificuldade ausente na linha %d. Usando PADRAO (%d).\n", contador + 2, MEDIO);
        }
        
        // 5. Dica
        token = strtok(NULL, "\n"); // Pega a dica até o final da linha
        
        if (token) {
        
            strncpy(perguntas[contador].dica, token, sizeof(perguntas[contador].dica) - 1);
            perguntas[contador].dica[sizeof(perguntas[contador].dica) - 1] = '\0';
        
        } else {
        
            perguntas[contador].dica[0] = '\0'; // Campo vazio ou inválido
        }


        free(linha_copy); // Libera a memória alocada por strdup

        contador++;

    }// while

    fclose(arquivo);
    *total_perguntas = contador;

    // Realoca uma última vez para o tamanho exato, se houver perguntas
    if (*total_perguntas > 0) {
        Pergunta* temp = (Pergunta*) realloc(perguntas, *total_perguntas * sizeof(Pergunta));
        if (temp != NULL) {
            perguntas = temp;
        }
    } else { // Se não carregou nenhuma pergunta, libera e retorna NULL
        free(perguntas);
        perguntas = NULL;
    }
    printf("Carregadas %d perguntas do arquivo CSV.\n", *total_perguntas);
    return perguntas;
} // carregarPerguntasDoCSV

Pergunta* carregarPerguntasBinario(char* nome_arquivo, int* total_perguntas) {
    
    size_t contador_lido = 0;
    
    FILE *arquivo = fopen(nome_arquivo, "rb");
   
    if (arquivo == NULL) {
        
        perror("Erro ao abrir o arquivo binario para carregar perguntas\n");
        exit(1);
    }

    if (fread(&contador_lido, sizeof(int), 1, arquivo) != 1) {
       
        perror("Erro ao ler o numero total de perguntas do arquivo binario\n");
        fclose(arquivo);
      
        *total_perguntas = 0;
      
        return NULL;
    }

    if (contador_lido <= 0) {

        printf("Arquivo binario '%s' vazio ou invalido.\n", nome_arquivo);
        fclose(arquivo);
       
        *total_perguntas = 0;
       
        return NULL;
    }

    Pergunta* perguntas = (Pergunta*) malloc(contador_lido * sizeof(Pergunta));

    if (perguntas == NULL) {

        perror("Erro ao alocar memoria para carregar perguntas do binario");
        fclose(arquivo);
       
        *total_perguntas = 0;
        
        return NULL;
    }

    if (fread(perguntas, sizeof(Pergunta), contador_lido, arquivo) != contador_lido) {
       
        perror("Erro ao ler as perguntas do arquivo binario (dados incompletos ou corrompidos)");
        free(perguntas);
        fclose(arquivo);
       
        *total_perguntas = 0;
        return NULL;
    }

    fclose(arquivo);
    *total_perguntas = contador_lido;

    return perguntas;

} // carregarPerguntasBinario


void salvarPerguntasBinario(char* nome_arquivo, Pergunta* perguntas, size_t  total_perguntas) {
    FILE *arquivo = fopen(nome_arquivo, "wb"); // "wb" cria ou sobrescreve
    
    if(arquivo == NULL)
    {
        
        perror("Erro ao abrir o arquivo binario para salvar as perguntas");
        return;
    }//if
    
    // Escreve o número total de perguntas
    if (fwrite(&total_perguntas, sizeof(int), 1, arquivo) != 1) {
        
        perror("Erro ao escrever o total de perguntas no arquivo binario");
        fclose(arquivo);
        
        return;
    }//if
    
    // Escreve todas as estruturas Pergunta se houver alguma
    if (total_perguntas > 0) {
        
        //size_t total_perguntas;
        if (fwrite(perguntas, sizeof(Pergunta), total_perguntas, arquivo) != total_perguntas) {
            
            perror("Erro ao escrever as perguntas no arquivo binario");
            fclose(arquivo);
            
            return;
        }//if
    }//if
    
    fclose(arquivo);
    printf("Perguntas salvas com sucesso em '%s' (formato binario).\n", nome_arquivo);
    
}
// salvarPerguntasBinario
    