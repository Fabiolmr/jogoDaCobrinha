#ifndef CENARIO_H
    #define CENARIO_H

	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include "../player/player.h"
	#include "../constantes.h"

	void geraCenario(char mat[][MAX_COLUNAS]);
	void imprimeCenario(char mat[][MAX_COLUNAS], cobra *play);


#endif