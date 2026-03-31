#include "acoes.h"

//verifica ação
void verifica_acao(char mat[][MAX_COLUNAS], cobra *play){
    //realisa loop no mapa
    if(play->vet[0].posI == MAX_LINHAS-1) play->vet[0].posI = 1;

    else if(play->vet[0].posI == 0) play->vet[0].posI = MAX_LINHAS-2;

    else if(play->vet[0].posJ == MAX_COLUNAS-1) play->vet[0].posJ = 1;

    else if(play->vet[0].posJ == 0) play->vet[0].posJ = MAX_COLUNAS-2;

    //se bateu no obstaculo, perde uma vida
    if(mat[play->vet[0].posI][play->vet[0].posJ] == '#' || mat[play->vet[0].posI][play->vet[0].posJ] == 'S'){
        play->life--;

        //se vida zerou, acaba o jogo
        if(play->life == 0){estado = 2; return;}
        
        //apaga cobra
        for (int i = 1; i < TAM_COBRA; i++){
            mat[play->vet[i].posI][play->vet[i].posJ] = ' ';
        }
        
        //"renasce" no caso
        nasce(play, mat);
    }
    //se acha comida
    else if (mat[play->vet[0].posI][play->vet[0].posJ] == '*'){
        cont_comida--;
        if(cont_comida == 0) estado = 1; //se comeu tudo, acaba o jogo
    }

}

//le entrada
void leEntrada(char mat[][MAX_COLUNAS], cobra *play){
    char entrada;
    printf("Digite o proximo movimento: ");
    scanf(" %c", &entrada);
    
    //tratamento de entradas inválidas
    if(entrada != 'a' && entrada != 'w' && entrada != 's' && entrada != 'd'){
        printf("Comando Invalido!\n");
        return;
    }

    //apaga "rabo" da cobra
    mat[play->vet[TAM_COBRA-1].posI][play->vet[TAM_COBRA-1].posJ] = ' ';
    
    //movimenta os indicadores de posição para "Frente" da cobra
    for (int i = TAM_COBRA - 1; i > 0; i--){
        play->vet[i].posI = play->vet[i-1].posI;
        play->vet[i].posJ = play->vet[i-1].posJ;
    }

    //cima
    if(entrada == 'w'){
        play->vet[0].posI--; 
    }
    //esquerda
    else if(entrada == 'a'){
        play->vet[0].posJ--; 
    }
    //baixo
    else if(entrada == 's'){
        play->vet[0].posI++;
    }
    //direita
    else if(entrada == 'd'){
        play->vet[0].posJ++;
    }
    
    //verifica oque acontece com essa movimentação
    verifica_acao(mat, play);

    //atualiza cobra no mapa
    for (int i = 0; i < TAM_COBRA; i++){
        mat[play->vet[i].posI][play->vet[i].posJ] = play->vet[i].valor;
    }
}
