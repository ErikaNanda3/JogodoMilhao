#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
/*Para gerenciar uma coleção de perguntas para o jogo, defina uma estrutura Pergunta
contendo, no mínimo: enunciado (texto), 4 alternativas (texto), letra da alternativa
correta(char), nível de dificuldade. O sistema deverá permitir cadastrar (inserir/ Listar/
pesquisar/ alterar/ excluir) as perguntas disponíveis. Essa relação deve aumentar e
diminuir dinamicamen*/
typedef enum {MUITOFACIL = 1, FACIL, MEDIO, DIFICIL, MUITODIFICIL}Dificuldade;
typedef struct 
{
    char enunciado[71];
    char alternativa_escrita[4][21];///sao 4 opçoes e cada opçao tem 21 caracteres
    char alternativa_correta;
    Dificuldade nivel_dificuldade;

    
}Pergunta;//Pergunta

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

    if (nivel_dif_temp >= 1 && nivel_dif_temp <= 5)
    { 
        nova.nivel_dificuldade = nivel_dif_temp;
    } 
        
    else {
        printf("Nivel de dificuldade invalido. Definido como 3 (MEDIO) por padrao.\n");
        nova.nivel_dificuldade = 3;//caso de erro ele entra no nivel 3 
    }
    

    perguntasDoJogo  = realloc(perguntasDoJogo, (*totalPerguntas + 1) * sizeof(Pergunta));
    if (perguntasDoJogo == NULL)
    {
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
    else
    {
        Pergunta* temporario = (Pergunta*) realloc(perguntasDoJogo, (*totalPeguntas) * sizeof(Pergunta));
        if (temporario == NULL)
        {
            printf("Erro ao realocar memoria após exclusao! \n");
           
            return perguntasDoJogo;
        }
        else
        {
            perguntasDoJogo = temporario;
        }
        printf("Pergunta %d excluida com sucesso!\n", indice_exclui);
        return perguntasDoJogo;
    }
}


int main(){
   Pergunta* perguntasDoJogo = (Pergunta*) malloc (50 *sizeof(Pergunta));
    if (perguntasDoJogo == NULL)
    {
        perror("Erro ao alocar memoria\n");
        exit(1);
    }//if
    int totalPergunta = 0;//contador de perguntas
    
    int opcao;
    do
    {
        printf(" 1 - Inserir Pergunta \n");
        printf(" 2 - Listar Perguntas  \n");
        printf(" 3 - Alterar Pergunta \n" );
        printf(" 5 - Apagar Pergunta \n" );
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
        case 5:
           excluirPergunta(perguntasDoJogo, &totalPergunta);
            break;    
        case 0:
            printf("Saindo do Jogo...\n");
            break;
        default:perror("Opcao invalida, tente novamente !\n");
            break;
        }//switch
    }//do 
    while (opcao != 0 );

    free(perguntasDoJogo);

    return 0;
}