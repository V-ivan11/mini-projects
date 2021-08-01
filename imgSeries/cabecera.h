/*
	Nombres: 
		De la Cruz Martinez Jorge Luis
		González Mendoza Aarón Abdiel
		Lemus Vallarta Yarazeth Amayrani
		Verduzco Lozano Iván Antonio
	Grupo: 1AM1
	Carrera: Licenciatura en Ciencia de Datos
	Fecha: 25/01/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#define MAX 50
#define IMAGEN 16384
#define VAL 3
#define TAM 128

// float serie[], [0] = k, [1] = h, [2] = n
// double suma[][], Almacenar valores de imagen

typedef struct Serie{
	float valoresSerie[VAL];
	double	arregloImagen[TAM][TAM];
	int seIndetermina;
	int converge;
}Serie;

//k/i*h
//(k/h)^i
//(-1)^i * k^i *h^i

Serie series[VAL];

void inicio(int, char**);
void registrarDatos(int, char**);
void imprimirHasta_n(int);
void generadorDeSuma(int);
void imprimirConvergencia(int);
void especificarTiempo(clock_t, clock_t);
void escribirImagen(char*, char*);
void generarImagen(int);
