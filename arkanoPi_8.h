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
#include <wiringPiSPI.h>
#include <softTone.h>

#include "kbhit.h" // para poder detectar teclas pulsadas sin bloqueo y leer las teclas pulsadas
#include "fsm.h"
#include "tmr.h"// para poder crear y ejecutar la máquina de estados

#include "arkanoPiLib.h"
#include "snakePiLib.h"

typedef enum {
	WAIT_START,
	WAIT_PUSH_ARKANO,
	WAIT_PUSH_SNAKE,
	PAUSED,
	PLAYING,
	WAIT_END} tipo_estados_juego;

typedef struct {
	tipo_arkanoPi arkanoPi;
	tipo_snakePi snakePi;
	tipo_pantalla display;
	tipo_estados_juego estado;
	char teclaPulsada;
} tipo_juego;

#include "kbhit.h" // para poder detectar teclas pulsadas sin bloqueo y leer las teclas pulsadas

#define CLK_MS 10 // PERIODO DE ACTUALIZACION DE LA MAQUINA ESTADOS
#define CLK_DISPLAY 1 //PERIODO DE REFRESCO DE CADA COLUMNA DE LEDS DEL DISPLAY

// FLAGS DEL SISTEMA
#define FLAG_TECLA			     0x01
#define FLAG_RAQUETA_DERECHA     0x02
#define FLAG_RAQUETA_IZQUIERDA   0x04
#define FLAG_PELOTA              0x08
#define FLAG_FINAL_JUEGO         0x10
#define FLAG_PAUSE               0x20

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
static int timer_raqueta_start(int ms);
static void timer_raqueta_isr (union sigval arg);
static int timer_serpiente_start(int ms);
static void timer_serpiente_isr (union sigval arg);

//------------------------------------------------------
// FUNCIONES DE LECTURA/ESCRITURA EN PERIFERICOS SPI
//------------------------------------------------------
float lectura_ADC(void);

//------------------------------------------------------
// FUNCIONES DE ENTRADA O DE TRANSICION DE LA MAQUINA DE ESTADOS
//------------------------------------------------------
int comprueba_tecla_pulsada (fsm_t* this);
int comprueba_pause (fsm_t* this);
int comprueba_tecla_pelota (fsm_t* this);
int comprueba_tecla_raqueta_derecha (fsm_t* this);
int comprueba_tecla_raqueta_izquierda (fsm_t* this);
int comprueba_final_juego (fsm_t* this);
int comprueba_joystick (fsm_t* this);

//------------------------------------------------------
// FUNCIONES DE ACCION ARKANOPI
//------------------------------------------------------
void InicializaArkano (fsm_t* fsm);
void MueveRaquetaIzquierda (fsm_t* fsm);
void MueveRaquetaDerecha (fsm_t* fsm);
void MovimientoPelota (fsm_t* fsm);
void FinalJuego (fsm_t* fsm);
void ReseteaJuego (fsm_t* fsm);
//Movimiento de la raqueta con Joystick
void MueveRaqueta(int posicion);
//------------------------------------------------------
// FUNCIONES DE ACCION SNAKEPI
//------------------------------------------------------
void InicializaSnake (fsm_t* fsm);
void AvanzaSerpiente(fsm_t*);
void GiraSerpienteDerecha(fsm_t* fsm);
void GiraSerpienteIzquierda(fsm_t* fsm);
//------------------------------------------------------
// FUNCIONES DE INICIALIZACION
//------------------------------------------------------
int systemSetup (void);
//------------------------------------------------------
// FUNCIONES QUE MANEJAN VICTORIA, DERROTA Y PAUSA
//------------------------------------------------------
void Victoria(tipo_estados_juego estado);
void Derrota(tipo_estados_juego estado);
void PausaJuego(fsm_t* fsm);

int areaPala(tipo_raqueta *p_pala);
//------------------------------------------------------
// FUNCIONES QUE REPRODUCEN SONIDOS USANDO softTone.h
//------------------------------------------------------
void SuenaVictoria();
void SuenaDerrota();
void SuenaRebote();
void SuenaPunto();
//------------------------------------------------------
// SUBRUTINAS DE ATENCION A LAS INTERRUPCIONES
//------------------------------------------------------
PI_THREAD (thread_explora_teclado);

#endif /* ARKANOPI_H_ */
