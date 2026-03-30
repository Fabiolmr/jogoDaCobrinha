#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//constantes
#define MAX_LINHAS 15
#define MAX_COLUNAS 50
#define TAM_COBRA 5

//structs
struct Gomo{
    char valor;
    int posI;
    int posJ;
};
typedef struct Gomo gomo;

struct Cobra{
    int life;
    gomo vet[TAM_COBRA];
    
};
typedef struct Cobra cobra;

//variaveis globais
int estado = 0;
int cont_comida = 0;

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

//verifica ação
void verifica_acao(char mat[][MAX_COLUNAS], cobra *play){
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

    //realisa loop no mapa
    else if(play->vet[0].posI == MAX_LINHAS-1) play->vet[0].posI = 1;

    else if(play->vet[0].posI == 0) play->vet[0].posI = MAX_LINHAS-2;

    else if(play->vet[0].posJ == MAX_COLUNAS-1) play->vet[0].posJ = 1;

    else if(play->vet[0].posJ == 0) play->vet[0].posJ = MAX_COLUNAS-2;

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