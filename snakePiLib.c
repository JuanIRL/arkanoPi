/*
 * snakePiLib.c

 *
 *  Created on: 22 abr. 2017
 *      Author: juani.rodriguez
 */

#include "snakePiLib.h"

int cuerpo_inicial[3][2] = {
		{4,2},
		{4,3},
		{4,4}
};

void ReseteaSerpiente(tipo_serpiente *p_serpiente){
	p_serpiente->size = 3;
	p_serpiente->vx = 0;
	p_serpiente->vy = -1;
	int i;
	for(i=0;i<LONG_MAX;i++){
		if(i<p_serpiente->size){
			p_serpiente->matriz[i].x = cuerpo_inicial[i][0];
			p_serpiente->matriz[i].y = cuerpo_inicial[i][1];
			continue;
		}
		p_serpiente->matriz[i].x = MATRIZ_ANCHO + 1;//Valor definido fuera del area
		p_serpiente->matriz[i].y = MATRIZ_ALTO +1;//Valor definido fuera del area
	}
}

void ReseteaPresa(tipo_presa *p_presa){
	p_presa->posicion.x = MATRIZ_ANCHO - 3;
	p_presa->posicion.y = MATRIZ_ALTO - 2;
}

void ReseteaPresaAleatorio(tipo_presa *p_presa){
	int x = rand() % (MATRIZ_ANCHO +1);
	int y = rand() % (MATRIZ_ALTO +1);
	p_presa->posicion.x = x;
	p_presa->posicion.y = y;
}

void PintaSerpiente(tipo_serpiente *p_serpiente, tipo_pantalla *p_pantalla){
	int i, j, k = 0;

	for(i=0;i<MATRIZ_ANCHO;i++) {
		for(j=0;j<MATRIZ_ALTO;j++) {
			for(k=0;k<p_serpiente->size;k++){
				if(i==p_serpiente->matriz[k].x && j==p_serpiente->matriz[k].y){
					p_pantalla->matriz[i][j] = 1;
				}
			}
		}
	}
}

void PintaPresa(tipo_presa *p_presa, tipo_pantalla *p_pantalla){
	int x = p_presa->posicion.x;
	int y = p_presa->posicion.y;

	p_pantalla->matriz[x][y] = 1;
}

void ActualizaPantallaSnake(tipo_snakePi* p_snakePi){
	// Borro toda la pantalla
		ReseteaMatriz((tipo_pantalla*)(&(p_snakePi->pantalla)));

		PintaSerpiente( &(p_snakePi->serpiente),&(p_snakePi->pantalla));
		PintaPresa(&(p_snakePi->presa), &(p_snakePi->pantalla));
#ifdef __MODO_DEBUG_TERMINAL__
		int i;
		printf("Movimiento en x: %d, en y: %d\n",p_snakePi->serpiente.vx,p_snakePi->serpiente.vy);
		for(i=0;i<LONG_MAX;i++){
			printf("Parte %d -> x:%d y:%d\n",i,p_snakePi->serpiente.matriz[i].x,p_snakePi->serpiente.matriz[i].y);
		}
#endif
}

void InicializaSnakePi(tipo_snakePi *p_snakePi) {

	ReseteaMatriz((tipo_pantalla*)(&(p_snakePi->pantalla)));

	ReseteaSerpiente((tipo_serpiente*)(&(p_snakePi->serpiente)));
	ReseteaPresa((tipo_presa*)(&(p_snakePi->presa)));

	ActualizaPantallaSnake(p_snakePi);



}

