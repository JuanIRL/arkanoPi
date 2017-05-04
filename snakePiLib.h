
#ifndef SNAKEPILIB_H_
#define SNAKEPILIB_H_

#include <stdio.h>
#include <stdlib.h>

#include "arkanoPiLib.h"

//CONSTANTES DEL JUEGO

#define LONG_MAX 50

//DEFINICION ESTRUCTURAS DEL JUEGO

typedef struct {
	int x;
	int y;
}tipo_posicion;

typedef struct {
	tipo_posicion matriz[LONG_MAX];
	int vx;
	int vy;
	int size;
} tipo_serpiente;

typedef struct {
	tipo_posicion posicion;
} tipo_presa;

typedef struct {
	tipo_pantalla pantalla;
	tipo_serpiente serpiente;
	tipo_presa presa;
} tipo_snakePi;

//------------------------------------------------------
// FUNCIONES DE INICIALIZACION / RESET
//------------------------------------------------------
void ReseteaSerpiente(tipo_serpiente *p_serpiente);
void ReseteaPresa(tipo_presa *p_presa);
void ReseteaPresaAleatorio(tipo_presa *p_presa);
//------------------------------------------------------
// FUNCIONES DE VISUALIZACION ADICIONALES A LAS USADAS DE "arkanoPiLib"
// Se reusaran PintaMensajeInicialPantalla, y PintaPantallaPorTerminal
//------------------------------------------------------
void PintaSerpiente(tipo_serpiente *p_serpiente, tipo_pantalla *p_pantalla);
void PintaPresa(tipo_presa *p_presa, tipo_pantalla *p_pantalla);
void ActualizaPantallaSnake(tipo_snakePi* p_snakePi);

void InicializaSnakePi(tipo_snakePi *p_snakePi);


#endif /* SNAKEPILIB_H_ */
