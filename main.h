#ifndef MAIN_H // Guarda para evitar include circulares
#define MAIN_H
/* ------ Se hacen todos los includes necesarios ------ */
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ------ Definición de tus estructuras ------ */

/*Defino la estructura para guardar palabras del texto*/
struct palabra{
	int apariciones;
	char *word;
};


/*Definiendo alias para la palabra*/
typedef struct palabra Palabra;

struct elemento {
   struct elemento  *siguiente; //Definimos un apuntador del tipo elemento que apuntará al siguiente elemento
   Palabra *palabra; //Definimos un apuntador que apuntará al valor guardado
}; 

// defino alias para los datos (struct elemento) y (Elemento**)
typedef struct elemento Elemento; 
typedef Elemento** Lista; 

/* ------ Definición de tus funciones ------ */
Lista crea_lista();
void inserta_elemento(Lista lista, Palabra *palabra);
int cmp_words(const void *a, const void *b);
void imprime_lista(Lista lista);
size_t longitud(Lista lista);
void rellena(Lista lista, FILE *archivo);

/*Imprime las instrucciones de uso del programa*/
void imprime_instrucciones();
#endif //MAIN_H
