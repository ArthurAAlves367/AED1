// Nome completo:
// Matricula:
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

//prohibido utilizar variáveis globais, exceto algum #define que seja necessário para o funcionamento do programa. 

// não alterar esta struct
typedef struct {
    int linhas;
    int colunas;
    int ** I;
} Matriz;

// Não alterar este vetor
const char cores[][8] = {
    "\033[30m", // 0 - preto
    "\033[31m", // 1 - vermelho
    "\033[32m", // 2 - verde
    "\033[33m", // 3 - amarelo
    "\033[34m", // 4 - azul
    "\033[35m", // 5 - magenta
    "\033[36m", // 6 - ciano
    "\033[37m", // 7 - branco
    "\033[90m", // 8 - cinza
};

// Não alterar esta função
void print_matrix(Matriz matriz) {
    printf("\n");
    for (int i = 0; i < matriz.linhas; i++) {
        printf("%d ", i);
        for (int j = 0; j < matriz.colunas; j++) {
            printf("%s%c", cores[matriz.I[i][j]], 35);
        }
        printf("\033[0m\n");
    }
    printf("\n");
}

// Prohibido alterar a assinatura da função colorir.
void colorir(int i, int j, int nova_cor, int cor_atual, Matriz matriz) {
    // completar com a mesma lógica do TP1, prohibido usar uma lógica diferente da do TP1, apenas pode ser alterado a forma de percorrer a matriz, mas a lógica de colorir deve ser a mesma.
    if((i < matriz.linhas) && (i >= 0) && (j < matriz.colunas) && (j >= 0)){
        int mudou;
        int indiceI, indiceJ;
        
        // Cor que fará a inundação da cor
        cor_atual = matriz.I[i][j];
        // Célula que iniciará o flood fill
        matriz.I[i][j] = nova_cor;

        do{

            mudou = 0;

            for(indiceI = 0; indiceI < matriz.linhas; indiceI++){
                for(indiceJ = 0; indiceJ < matriz.colunas; indiceJ++){

                    if(matriz.I[indiceI][indiceJ] == cor_atual){

                        if( (indiceI - 1 >= 0) && (matriz.I[indiceI - 1][indiceJ] == nova_cor) ||
                            (indiceI + 1 < matriz.linhas) && (matriz.I[indiceI + 1][indiceJ] == nova_cor) ||
                            (indiceJ - 1 >= 0) && (matriz.I[indiceI][indiceJ - 1] == nova_cor) ||
                            (indiceJ + 1 < matriz.colunas) && (matriz.I[indiceI][indiceJ + 1] == nova_cor)){

                                matriz.I[indiceI][indiceJ] = nova_cor;
                                mudou = 1;
                        }
                    }
                }

            } 
        } while(mudou);
    }
}

// Prohibido alterar a assinatura da função ler_arquivo.
int** ler_arquivo(char *nome_arquivo, Matriz *matriz) {

    // Abre o arquivo para leitura com fopen e verifica se foi aberto com sucesso, caso contrário imprime uma mensagem de erro e encerra o programa com exit(1)
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
        printf("Arquivo inexistente\n");
        exit(1);
    }

    int cont, i, j, desalocar;

    // Lê as dimensões da matriz (linhas e colunas) do arquivo usando fscanf, verificando se a leitura foi bem-sucedida e se os valores são válidos (maiores que zero). Caso contrário, fecha o arquivo, imprime uma mensagem de erro e encerra o programa com exit(1).
    
    if(fscanf(arquivo, "%d %d", &(matriz->linhas), &(matriz->colunas)) != 2){
        printf("Falha na leitura de dimensões!\n");
        fclose(arquivo);
        exit(1);
    } else if((matriz->linhas <= 0) || (matriz->colunas <= 0)){
        printf("Número de linhas ou colunas inválido\n");
        fclose(arquivo);
        exit(1);
    }

    // Aloca dinamicamente a matriz de inteiros com malloc usando int** (vetor de ponteiros), verificando se a alocação foi bem-sucedida. Caso contrário, fecha o arquivo, imprime uma mensagem de erro e encerra o programa com exit(1).
    matriz->I = (int**) malloc(matriz->linhas*sizeof(int*));
    if(matriz->I == NULL){
        printf("Erro de alocação de matriz\n");
        fclose(arquivo);
        exit(1);
    }
    
    // Aloca dinamicamente cada linha da matriz com malloc usando I[], verificando se a alocação foi bem-sucedida. Caso contrário, libera a memória já alocada (todas as linhas que foram alocadas e o vetor de ponteiros), fecha o arquivo, imprime uma mensagem de erro e encerra o programa com exit(1). 
    for(cont = 0; cont < matriz->linhas; cont++){
        matriz->I[cont] = (int*) malloc(matriz->colunas*sizeof(int));
        
        if(matriz->I[cont] == NULL){
            desalocar = cont;
            printf("Erro de alocação de elementos da matriz\n");
            for(cont = 0; cont < desalocar; cont++){
                free(matriz->I[cont]);
            }
            free(matriz->I);
            fclose(arquivo);
            exit(1);
        }
    }
    
    // Lê os valores da matriz do arquivo usando fscanf, verificando se a leitura foi bem-sucedida e se os valores são válidos (entre 0 e 8). Caso contrário, libera a memória alocada (todas as linhas e o vetor de ponteiros), fecha o arquivo, imprime uma mensagem de erro e encerra o programa com exit(1).
    for(i = 0; i < matriz->linhas; i++){
        for(j = 0; j < matriz->colunas; j++){
            if((fscanf(arquivo, "%d", &(matriz->I[i][j])) != 1) || 
              ((matriz->I[i][j] < 0) || (matriz->I[i][j] > 8))){
                printf("Falha na leitura dos elementos da matriz\n");
                printf("Ou valores para cor inválidos\n");
                for(cont = 0; cont < matriz->linhas; cont++){
                    free(matriz->I[cont]);
                }
                free(matriz->I);
                fclose(arquivo);
                exit(1);
            }
        }
    }

    // Fecha o arquivo e retorna o ponteiro para a matriz alocada.
    fclose(arquivo);
    return matriz->I;
}

// Prohibido alterar esta função utilizada para limpar_buffer_do_teclado.
void limpar_buffer_do_teclado() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Prohibido alterar a assinatura da função main.
int main(int argc, char *argv[]) {
    
    int i, j, nova_cor, cor_atual;
    int entradaValida, cont;

    // Verifica se o número de argumentos passados para o programa é igual a 2 (o nome do programa e o nome do arquivo da matriz). Caso contrário, imprime uma mensagem de uso e retorna 1.
    if(argv != 2){
        return 1;
    }

    Matriz matriz = {0, 0, NULL};
    matriz.I = ler_arquivo(argv[1], &matriz);    

    // Cria o arquivo de log "color_fill_log.txt" usando a função criar_arquivo_log do TAD log.h. Caso não seja possível criar o arquivo, imprime uma mensagem de erro, libera a memória da matriz e retorna 1.
    if(!(criar_arquivo_log("color_fill_log.txt"))){
        printf("Falha ao criar arquivo log\n");
        for(cont = 0; cont < matriz.linhas; cont++){
            free(matriz.I[cont]);
        }
        free(matriz.I);
        return 1;
    }

    while (1)
    {
        print_matrix(matriz);
        
        // Lógica de interação com o usuário para solicitar a nova cor, a posição (i, j) e chamar a função colorir. A cada iteração, imprime a matriz atualizada e solicita a entrada do usuário.
        
        // Verifica se a cor de entrada do usuário é válida (cor entre 0 e 8 ou -1 para sair). Caso a entrada seja inválida, imprime uma mensagem de erro "Entrada inválida.\n", limpa o buffer do teclado e solicita novamente a entrada do usuário.
        entradaValida = 0;
        while(!entradaValida){
            printf("Digite o número da cor (0 a 8 ou -1 para sair).\n");
            scanf("%d", &nova_cor);

            if((nova_cor == -1) || ((nova_cor >= 0) && (nova_cor <= 8))){
                entradaValida = 1;
            } else {
                printf("Entrada inválida!\n");
                limpar_buffer_do_teclado();
            }
        }

        if(nova_cor == -1){
            break;
        }
        
        // Solicita a coordenada i. Verifica se a coordenada é válida (posição dentro dos limites da matriz). Caso a entrada seja inválida, imprime uma mensagem de erro "Coordenada i inválida.\n", limpa o buffer do teclado e solicita novamente a entrada do usuário.
        entradaValida = 0;
        while(!entradaValida){
            printf("Digite a coordenada i (Linha): ");
            scanf("%d", &i);

            if((i >= 0) && (i < matriz.linhas)){
                entradaValida = 1;
            } else {
                printf("Coordenada i inválida.\n");
                limpar_buffer_do_teclado();
            }
        }
        // Solicita a coordenada j. Verifica se a coordenada é válida (posição dentro dos limites da matriz). Caso a entrada seja inválida, imprime uma mensagem de erro "Coordenada j inválida.\n", limpa o buffer do teclado e solicita novamente a entrada do usuário.
        entradaValida = 0;
        while(!entradaValida){
            printf("\nDigite a coordenada j (Coluna): ");
            scanf("%d", &j);

            if((j >= 0) && (j < matriz.colunas)){
                entradaValida = 1;
            } else {
                printf("Coordenada j inválida.\n");
                limpar_buffer_do_teclado();
            }
        }

        // Verifica se a nova cor é diferente da cor atual na posição (i, j). Caso sejam iguais, imprime uma mensagem de erro "A nova cor deve ser diferente da cor na posição atual\n" e solicita novamente a entrada do usuário.
        cor_atual = matriz.I[i][j];
        if(nova_cor == cor_atual){
            printf("A nova cor deve ser diferente da cor na posição atual\n");
            
            entradaValida = 0;
            while(!entradaValida){
                printf("Digite o número da cor (0 a 8 ou -1 para sair).\n");
                scanf("%d", &nova_cor);

                if(((nova_cor == -1) || (nova_cor >= 0) && 
                    (nova_cor <= 8)) &&
                    (nova_cor != cor_atual)){
                    entradaValida = 1;
                } else {
                    printf("Entrada inválida, tente novamente!\n");
                    limpar_buffer_do_teclado();
                }
            }

            if(nova_cor == -1){
                break;
            }
        
        }
        
        colorir(i, j, nova_cor, cor_atual, matriz);
        
        // Após colorir a matriz, chama a função log_append para registrar a operação no arquivo de log. Caso não seja possível escrever no arquivo, imprime uma mensagem de aviso.
        if (!log_append("color_fill_log.txt", nova_cor, i, j)) {
            fprintf(stderr, "Aviso: nao foi possivel escrever o color_fill_log.txt\n");
        }
    }

    // Liberar memória da matriz antes de encerrar o programa
    for(cont = 0; cont < matriz.linhas; cont++){
        free(matriz.I[cont]);
    }
    free(matriz.I);

    return 0;
}