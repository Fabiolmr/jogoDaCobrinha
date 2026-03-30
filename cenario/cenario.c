#include "cenario.h"

//funcao gera cenário
void geraCenario(char mat[][MAX_COLUNAS]){
    srand(time(NULL)); //inicializa semente de geração

    for (int i = 0; i < MAX_LINHAS; i++){
        for (int j = 0; j < MAX_COLUNAS; j++){ 
            //coloca + nas quinas
            if(i == 0 && j == 0) mat[i][j] = '+';
            else if(i == 0 && j == MAX_COLUNAS-1) mat[i][j] = '+';
            else if(i == MAX_LINHAS-1 && j == 0) mat[i][j] = '+';
            else if(i == MAX_LINHAS-1 && j == MAX_COLUNAS-1) mat[i][j] = '+';
            //coloca = nas bordas horizontais
            else if(i == 0 || i == MAX_LINHAS-1) mat[i][j] = '=';
            //coloca barra nas bordas verticais
            else if(j == 0 || j == MAX_COLUNAS-1) mat[i][j] = '|';

            else{
                int valor = rand() % 1001; //gera range de numeros aleatórios

                if(valor >=0 && valor <= 20) mat[i][j] = '#'; //obstaculo
                else if(valor >= 20 && valor <= 30){mat[i][j] = '*'; cont_comida++;} //comida
                else mat[i][j] = ' '; //preeenche o resto
            }
        }
    }
}


//imprime cenario
void imprimeCenario(char mat[][MAX_COLUNAS], cobra *play){
    for (int i = 0; i < MAX_LINHAS; i++){
        for (int j = 0; j < MAX_COLUNAS; j++){
            printf("%c", mat[i][j]);
        }
        printf("\n");
    }

    printf("Quantidade de fruta: %d\n", cont_comida);
    printf("Vida: %d\n", play->life);   
}