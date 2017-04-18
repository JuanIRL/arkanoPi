#ifndef _ARKANOPI_H_
#define _ARKANOPI_H_

#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <wiringPi.h>

#include "kbhit.h" // para poder detectar teclas pulsadas sin bloqueo y leer las teclas pulsadas
#include "fsm.h"
#include "tmr.h"// para poder crear y ejecutar la máquina de estados

#include "arkanoPiLib.h"

typedef enum {
	WAIT_START,
	WAIT_PUSH,
	WAIT_END} tipo_estados_juego;

typedef struct {
	tipo_arkanoPi arkanoPi;
	tipo_estados_juego estado;
	char teclaPulsada;
} tipo_juego;

#include "kbhit.h" // para poder detectar teclas pulsadas sin bloqueo y leer las teclas pulsadas

#define CLK_MS 10 // PERIODO DE ACTUALIZACION DE LA MAQUINA ESTADOS
#define CLK_DISPLAY 1

// FLAGS DEL SISTEMA
#define FLAG_TECLA			     0x01
#define FLAG_RAQUETA_DERECHA     0x02
#define FLAG_RAQUETA_IZQUIERDA   0x04
#define FLAG_PELOTA              0x08
#define FLAG_FINAL_JUEGO         0x10
#define FLAG_JOYSTICK            0x20

// A 'key' which we can lock and unlock - values are 0 through 3
//	This is interpreted internally as a pthread_mutex by wiringPi
//	which is hiding some of that to make life simple.
#define	FLAGS_KEY	1
#define	STD_IO_BUFFER_KEY	2
#define	JUEGO_KEY	3
//------------------------------------------------------
// FUNCIONES DE ENCENDIDO LEDS
//------------------------------------------------------

void enciende_columna(int numero);
void endiende_filas(int filas);
//------------------------------------------------------
// FUNCIONES DE TEMPORIZADORES
//------------------------------------------------------
static int timer_display_start(int ms);
static void timer_display_isr (union sigval arg);
static int timer_pelota_start(int ms);
static void timer_pelota_isr (union sigval arg);
//------------------------------------------------------
// FUNCIONES DE ENTRADA O DE TRANSICION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------
// Prototipos de funciones de entrada
int comprueba_tecla_pulsada (fsm_t* this);
int comprueba_tecla_pelota (fsm_t* this);
int comprueba_tecla_raqueta_derecha (fsm_t* this);
int comprueba_tecla_raqueta_izquierda (fsm_t* this);
int comprueba_final_juego (fsm_t* this);
int comprueba_joystick (fsm_t* this);

//------------------------------------------------------
// FUNCIONES DE ACCION
//------------------------------------------------------

void InicializaJuego (fsm_t* fsm);
void MueveRaquetaIzquierda (fsm_t* fsm);
void MueveRaquetaDerecha (fsm_t* fsm);
void MovimientoPelota (fsm_t* fsm);
void FinalJuego (fsm_t* fsm);
void ReseteaJuego (fsm_t* fsm);

//------------------------------------------------------
// FUNCIONES DE INICIALIZACION
//------------------------------------------------------
int systemSetup (void);

int areaPala(tipo_raqueta *p_pala);
//------------------------------------------------------
// SUBRUTINAS DE ATENCION A LAS INTERRUPCIONES
//------------------------------------------------------
PI_THREAD (thread_explora_teclado);

#endif /* ARKANOPI_H_ */
