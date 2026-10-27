#include <stdio.h>

#define linhas 10
#define colunas 16

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

void print_matrix(int I[linhas][colunas]) {
    printf("\n");

    for (int i = 0; i < linhas; i++) {
        printf("%d ", i);
        for (int j = 0; j < colunas; j++) {
            printf("%s%c", cores[I[i][j]], 35);
        }
        printf("\033[0m\n");
    }
    printf("\n");
}

void colorir(int i, int j, int nova_cor, int cor_atual, int I[linhas][colunas]) {
    
    if((i >= 0 && i < linhas) && (j >= 0 && j < colunas)) {

        int mudou; // Bandeira para mudança de cor de algum pixel
        int indiceI, indiceJ;

        cor_atual = I[i][j];
        I[i][j] = nova_cor; // Pinta a célula que iniciará o Flood Fill

        // Repete a varredura da matriz até que não haja mais células para serem pintadas
        do{
            mudou = 0; 

            for(indiceI = 0; indiceI < linhas; indiceI++){
                for(indiceJ = 0; indiceJ < colunas; indiceJ++){

                    if(I[indiceI][indiceJ] == cor_atual){
                    // Verificação se a coordenada tinha a cor atual antes de colorir

                        // Verificação se o vizinho está dentro da matriz e
                        // Verificação de vizinhos que já foram pintados no loop anterior 

                        if(((indiceI - 1) >= 0) && (I[indiceI - 1][indiceJ] == nova_cor) ||
                        ((indiceI + 1) < linhas) && (I[indiceI + 1][indiceJ] == nova_cor) ||
                        ((indiceJ - 1) >= 0) && (I[indiceI][indiceJ - 1] == nova_cor) ||
                        ((indiceJ + 1) < colunas) && (I[indiceI][indiceJ + 1] == nova_cor)){
                            
                            I[indiceI][indiceJ] = nova_cor;
                            mudou = 1; // Sinaliza que precisa de mais uma varredura
                        }
                    }
                }
            }
        } while(mudou); // Enquanto a varredura mudar algo
    }
}

void main() {
//  Caso de teste 1:   
      int I[linhas][colunas] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
        {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
        {0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0},
        {0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0},
        {0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0},
        {0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

//  Caso de teste 2:   
/*    int I[linhas][colunas] = {
        {3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {3,3,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
        {3,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
        {0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
        {0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0},
        {0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0},
        {0,0,2,0,0,0,0,0,0,0,0,0,0,2,0,0},
        {0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    }; */
// Caso de teste 3: Cores em camadas
/*    int I[linhas][colunas] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
        {0,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3},
        {0,1,2,3,4,4,4,4,4,4,4,4,4,4,4,4},
        {0,1,2,3,4,5,5,5,5,5,5,5,5,5,5,5},
        {0,1,2,3,4,5,6,6,6,6,6,6,6,6,6,6},
        {0,1,2,3,4,5,6,7,7,7,7,7,7,7,7,7},
        {0,1,2,3,4,5,6,7,8,8,8,8,8,8,8,8},
        {0,1,2,3,4,5,6,7,8,0,0,0,0,0,0,0}
    };*/
// Caso de teste 4: Labirinto e diversas regiões
/*   int I[linhas][colunas] = {
        {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
        {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0},
        {1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0},
        {1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0,0,1,0},
        {0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };*/
// Caso de teste 5: Teste da diagonal
/*   int I[linhas][colunas] = {
        {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
    };*/
    
    int i, j, nova_cor, cor_atual;
    int bandeiraDeSaida = 0;
    
    // O loop ocorrerá até a bandeiraDeSaida ser ativada, ou seja, até o usuário digitar -1
    while(!bandeiraDeSaida){
        print_matrix(I);
        printf("Digite a cor entre 0 e 8: (-1 para sair): ");
        scanf("%d", &nova_cor);
        if(nova_cor == -1){
            bandeiraDeSaida = 1;
        } else {
            printf("\nDigite linha 'i': ");
            scanf("%d", &i);
            printf("\nDigite coluna 'j': ");
            scanf("%d", &j);

            if((i >= 0 && i < linhas) && (j >= 0 && j < colunas)) {
            // Verifica se os índices estão dentro dos limites da matriz
                cor_atual = I[i][j]; // Salva a cor atual da célula selecionada

                // Verifica se nova_cor é diferente da cor_atual
                if(nova_cor != cor_atual){
                    colorir(i, j, nova_cor, cor_atual, I);        
                }
            }  
        }
    }
}



