// Nome completo:
// Matricula:
#include <stdio.h>
#include "log.h"

int criar_arquivo_log(const char *nome_arquivo) {
    // cria arquivo de log vazio
    // verifica se o arquivo foi criado com sucesso, caso contrário retorna 0
    if(fopen(*nome_arquivo, "w") == NULL){
        printf("Falha ao criar arquivo.log\n");
        return 0;
    }

    // verifica se o arquivo foi fechado com sucesso, caso contrário retorna 0
    if(fclose(*nome_arquivo) != 0){
        printf("Arquivo não pode ser fechado!\n");
        return 0;
    }

    return 1;
}

int log_append(const char *nome_arquivo, int cor, int i, int j) {

    // Abre o arquivo e faz append no final do arquivo de log no formato: "cor=cor i=i j=j\n". Verifica se o arquivo foi aberto com sucesso, caso contrário retorna 0
    if(fopen(*nome_arquivo, "a") == NULL){
        printf("Falha ao registrar histórico\n");
        return 0;
    }

    // Verifica se a escrita no arquivo foi bem-sucedida, caso contrário fecha o arquivo e retorna 0. Utiliza fprintf() para escrever no arquivo.
    if(fprintf(*nome_arquivo, "Cor = %d, i = %d, j = %d\n", cor, i, j) < 0){
        printf("Erro ao registrar as cores e coordenadas\n");
        return 0;
    }
    
    // Fecha o arquivo. Verifica se o arquivo foi fechado com sucesso, caso contrário retorna 0
    if(fclose(*nome_arquivo) != 0){
        printf("Arquivo log não foi fechado corretamente\n");
    }

    return 1;
}
