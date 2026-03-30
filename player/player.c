int estado = 0;
int cont_comida = 0;
#include "player.h"

//gera cobra
void nasce(cobra * play, char mat[][MAX_COLUNAS]){
    for (int i = 1; i < MAX_LINHAS; i++){
        int achou = 0; //indicador de encontrou lugar
        for (int j = 2; j < 40; j++){
            //condições ideal
            if(mat[i][j] == ' ' && mat[i][j+1] == ' ' && mat[i][j+2] == ' ' && mat[i][j+3] == ' ' && mat[i][j+4] == ' '){
                
                for(int k = 0; k < TAM_COBRA; k++){
                    mat[i][j+k] = play->vet[k].valor; //coloca na natriz o gomo da cobra
                    play->vet[k].posI = i; //salva posição I
                    play->vet[k].posJ = j+k; //salva posição J
                }
                achou = 1;
                break;
            }
        }
        if (achou == 1) break; // para loop I
    }
}