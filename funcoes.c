#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para usar toupper
#include "funcoes.h"


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

    printf("Digite o enunciado da pergunta que deseja pesquisar: ");
    char pesquisa[200];
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
int random(Pergunta* perguntasDoJogo, int* totalPerguntas,  int level){
    int i;
    do{
    i = rand() % *totalPerguntas;
    }while(perguntasDoJogo[i].nivel_dificuldade != level);
    return i;
}//mani q fez e tava dando erro no pc dela
Pergunta* jogar(Pergunta* perguntasDoJogo, int totalPerguntas)//mani q fez e deu erro no pc dela
{
    int i = 0;
    int condicao;
    int level = 0;
    char resp;

    if (totalPerguntas == 0)
    {
        printf("Nenhuma pergunta cadastrada para jogar.\n");
        return perguntasDoJogo;
    }
    do{
        level++;
        switch (level){
            case MUITOFACIL: 
                i = random(perguntasDoJogo, totalPerguntas, level);
                printf("%s", perguntasDoJogo[i].enunciado);  
                for (int j = 0; j<4; j++){
                    printf("%s", perguntasDoJogo[i].alternativa_escrita);
                }
                printf("Escolha a alternativa correta: ");
                scanf("%c",&resp);

                if(resp != perguntasDoJogo[i].alternativa_correta){
                    level = 0;
                    printf("Voce errou, vamos voltar uma dificuldade!");
                }
                printf("Voce acertou, parabens! Proxima pergunta:\n");

            break;

            case FACIL: 
                i = random(perguntasDoJogo, totalPerguntas, level);
                printf("%s", perguntasDoJogo[i].enunciado);  
                for (int j = 0; j<4; j++){
                    printf("%s", perguntasDoJogo[i].alternativa_escrita);
                }
                printf("Escolha a alternativa correta: ");
                scanf("%c",&resp);

                if(resp != perguntasDoJogo[i].alternativa_correta){
                    level = 0;
                    printf("Voce errou, vamos voltar uma dificuldade!");
                }
                printf("Voce acertou, parabens! Proxima pergunta:\n");


            break;

            case MEDIO: 
                i = random(perguntasDoJogo, totalPerguntas, level);
                printf("%s", perguntasDoJogo[i].enunciado);  
                for (int j = 0; j<4; j++){
                    printf("%s", perguntasDoJogo[i].alternativa_escrita);
                }
                printf("Escolha a alternativa correta: ");
                scanf("%c",&resp);

                if(resp != perguntasDoJogo[i].alternativa_correta){
                    level = 1;
                    printf("Voce errou, vamos voltar uma dificuldade!");
                }
                printf("Voce acertou, parabens! Proxima pergunta:\n");

            break;

            case DIFICIL: 
                i = random(perguntasDoJogo, totalPerguntas, level);
                printf("%s", perguntasDoJogo[i].enunciado);  
                for (int j = 0; j<4; j++){
                    printf("%s", perguntasDoJogo[i].alternativa_escrita);
                }
                printf("Escolha a alternativa correta: ");
                scanf("%c",&resp);

                if(resp != perguntasDoJogo[i].alternativa_correta){
                    level = 2;
                    printf("Voce errou, vamos voltar uma dificuldade!");
                }
                printf("Voce acertou, parabens! Proxima pergunta:\n");

            break;

            case MUITODIFICIL: 
                i = random(perguntasDoJogo, totalPerguntas, level);
                printf("%s", perguntasDoJogo[i].enunciado);  
                for (int j = 0; j<4; j++){
                    printf("%s", perguntasDoJogo[i].alternativa_escrita);
                }
                printf("Escolha a alternativa correta: ");
                scanf("%c",&resp);

                if(resp != perguntasDoJogo[i].alternativa_correta){
                    level = 3;
                    printf("Voce errou, vamos voltar uma dificuldade!");
                }
                printf("Voce acertou, parabens! Agora voce eh um milionario!\n");

                condicao = 1;
            break;

        }
    }while(condicao == 0);
    
    return perguntasDoJogo;
}
  

Pergunta* carregarPerguntasDoCSV(char* nome_arquivo, int* total_perguntas) {
   
    FILE *arquivo = fopen(nome_arquivo, "r");
   
    if (arquivo == NULL) {
   
        perror("Erro ao abrir o arquivo CSV de questoes");
        *total_perguntas = 0;
   
        return NULL;
    }

    char linha[1024]; // Buffer para ler cada linha do CSV
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

    linha[strcspn(linha, "\n")] = 0; // Remove o '\n' do cabeçalho também, por boa prática

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
   
        linha[strcspn(linha, "\n")] = 0; // Remover o '\n' do final da linha
        // Realoca mais memória se necessário
        if (contador >= capacidade_atual) {
           
            capacidade_atual += 50; // Aumenta a capacidade em 50 perguntas
           
            Pergunta* temporario = (Pergunta*) realloc(perguntas, capacidade_atual * sizeof(Pergunta));
          
            if (temporario == NULL) {
               
                perror("Erro de realocacao de memoria ao carregar perguntas do CSV");
                fclose(arquivo);
                
                *total_perguntas = contador; // Retorna o que conseguiu carregar até agora
               
                return perguntas;
            }
            perguntas = temporario;
        }

        // Parsing da linha CSV: enunciado, 4 alternativas, correta, dificuldade
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

        // 4. Nível de Dificuldade (último campo)
        token = strtok(NULL, "\n"); // Delimita pelo '\n' para pegar o final da linha
        
        if (token) {
           
            int nivel = atoi(token); // Usando 'nivel' como preferiu
           
            if (nivel >= MUITOFACIL && nivel <= MUITODIFICIL) {

                perguntas[contador].nivel_dificuldade = (Dificuldade)nivel;

            } else {

                perguntas[contador].nivel_dificuldade = MEDIO; // Padrão se o nível for inválido
               
                fprintf(stderr, "Aviso: Nivel de dificuldade invalido '%s' na linha %d. Usando PADRAO (%d).\n", token, contador + 2, MEDIO);
            }
        } else {

            perguntas[contador].nivel_dificuldade = MEDIO; // Padrão se o token estiver faltando
           
            fprintf(stderr, "Aviso: Nivel de dificuldade ausente na linha %d. Usando PADRAO (%d).\n", contador + 2, MEDIO);
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
    
    int contador_lido = 0;
    
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

void salvarPerguntasBinario(char* nome_arquivo, Pergunta* perguntas, int total_perguntas) {

    FILE *arquivo = fopen(nome_arquivo, "wb"); // "wb" cria ou sobrescreve

    if (arquivo == NULL) {

        perror("Erro ao abrir o arquivo binario para salvar as perguntas");
        return;
    }

    // Escreve o número total de perguntas
    if (fwrite(&total_perguntas, sizeof(int), 1, arquivo) != 1) {

        perror("Erro ao escrever o total de perguntas no arquivo binario");
        fclose(arquivo);

        return;
    }

    // Escreve todas as estruturas Pergunta se houver alguma
    if (total_perguntas > 0) {

        if (fwrite(perguntas, sizeof(Pergunta), total_perguntas, arquivo) != total_perguntas) {

            perror("Erro ao escrever as perguntas no arquivo binario");
            fclose(arquivo);

            return;
        }
    }

    fclose(arquivo);
    printf("Perguntas salvas com sucesso em '%s' (formato binario).\n", nome_arquivo);

} // salvarPerguntasBinario
