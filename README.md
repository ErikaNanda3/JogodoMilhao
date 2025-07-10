## Jogo do Milhão (Tema: História da Mulher na Computação)

## Participantes:

    Érika Fernanda Santos De Souza R.A.: 2478382

    Mayane Rye Aomoto Ioaoka R.A.: 2270862



## Como fazer o programa rodar: 

    Explicando cada função e a bbiblioteca:

    Funções: 
    As funções cada uma tem sua funcionalidade específica;
    "Pergunta* carregarPerguntasDoCSV(char* nome_arquivo, int* total_perguntas)" :
    É uma função ponteiro que passa tudo que está no arquivo "questõesJogoDoMilhao.csv" vai para a estrutura Perguntas em suas respectivas variaveis para que o jogo mostre corretamente as perguntas de seu nível,sendo eles: Muito Fáci,Fácil, Médio, Difícil e Muito Difícil, e consequentemente suas alternativas e logo após o jogador acertar ou errar mostrar a resposta correta, as dicas que é a parte criativa ainda não estão implementadas no arquivo CSV.

    Após o jogador finalizar o jogo todas as alterações em relação as perguntas (se foram excluidas e as que foram cadastradas pelo usuário) é chamada a função " void salvarPerguntasBinario(char* nome_arquivo, Pergunta* perguntas, int total_perguntas);" , que não faz alteração na array, ou seja , não faz alteração nas perguntas que estão na estrutura Perguntas

    Foi salvo as alterações do usuario em relação as perguntas, alternativas e a alternativa correta em binario para não ocorrer o erro de alguma letra ou frase não ser salva como esperado (aparecer simbolos no lugar),ou seja , essa função cria um arquivo binario com os dados citados anteriormente
    Para conseguirmos ler o que está escrito no arquivo "questoes_milhao.bin", temos a função " Pergunta* carregarPerguntasBinario(char* nome_arquivo, int* total_perguntas); "

    Foi colocado a leitura/escrita em binario/leitura de arquivo binario em funções pra que não fosse preciso muita alteração no código básico e que talvez possamos reutiliza-los caso precise.

    a biblioteca ctype.h para que possamos usar a sintax strok, que para ler até o ponto e vígula (;) e fazer a quebra de linha das perguntas, alternativas, resposta correta e nível de dificuldade que serão enviadas para a variavel da estrutura Perguntas.

    Biblioteca:
    A biblioteca é  para uma melhor organização e vizualização do código  
    "funcoes.h" é uma biblioteca que recebe todas a funções do arquivo em C ("funcoes.c"), é chamada pelo arquivo "menuPrincipal.c", ou seja, a biblioteca "funcoes.h" é uma ponte ou facilitadora de comunicação entre dois arquivos em C.

    (O arquivo teste1.c é apenas o arquivo original das funções sem a parte da biblioteca)

## Parte criativa:

    Sistema de Pontuação com Bônus: Um sistema de pontuação que não apenas conte as respostas corretas, mas também recompense a velocidade e a estratégia. Por exemplo, responder corretamente em um tempo curto poderia dar um bônus de pontos, ou usar as ajudas estrategicamente poderia resultar em uma pontuação extra. Isso adiciona uma camada extra de 
    competição e estratégia ao jogo.

    Sistema de dicas:
    -Elimina metade das respostas
    -Pula uma questão
    -A pessoa perde 1 ponto a cada ajuda utilizada
    -Recebe uma dica





```
