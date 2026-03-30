#ifndef ACOES_H
    #define ACOES_H
    #include <stdio.h>
    #include "../cenario/cenario.h"
    #include "../player/player.h"
    #include "../constantes.h"

    void verifica_acao(char mat[][MAX_COLUNAS], cobra *play);
    void leEntrada(char mat[][MAX_COLUNAS], cobra *play);

#endif