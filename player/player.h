#ifndef PLAYER_H
    #define PLAYER_H

    #include <stdio.h>
    #include "../constantes.h"

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
    extern int estado;
    extern int cont_comida;

    void nasce(cobra * play, char mat[][MAX_COLUNAS]);

#endif