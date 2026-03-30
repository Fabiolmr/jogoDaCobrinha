#include <stdio.h>
#include <string.h>
#include "cenario/cenario.h"
#include "player/player.h"
#include "acoes/acoes.h"


int main(void){
    //inicializa cenario
    char mat[MAX_LINHAS][MAX_COLUNAS];
    geraCenario(mat);

    //inicializa cobra
    cobra player;
    player.life = 5;

    //atribue valores para a cobra
    player.vet[0].valor = '$';
    for(int i = 1; i < TAM_COBRA; i++) {
        player.vet[i].valor = 'S';
    }

    //imprimeCenario(mat, &player);
    nasce(&player, mat);
    imprimeCenario(mat, &player);

    while (estado == 0){
        leEntrada(mat, &player);
        imprimeCenario(mat, &player);
    }

    if(estado == 1) printf("\nVoce venceu!\n");
    if(estado == 2) printf("\nVoce perdeu!\n");
    
    return 0;
}