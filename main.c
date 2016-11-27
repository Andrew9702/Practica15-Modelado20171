#include "main.h"
// No hagas #include aquí, hazlos en main.h

int main(int argc, char const *argv[])
{

    // Verifica si hay al menos de 3 parametros
    // sino entonces se imprimen las instrucciones
    // y se para la ejecución del programa
    if (argc < 2){
        imprime_instrucciones();
        return 0;

    } else {
    	int indice = 1;
    	FILE *archivo;
    	//Abrimos todos los archivos que se le pasan como parametros
    	for(indice;argv[indice]!=NULL;indice++){
    		//Creamos una lista en donde guardaremos las palabras del archivo
			Lista palabras = crea_lista();
    		archivo = fopen(argv[indice], "a+");
    		printf("Abriendo el archivo %s\n", argv[indice]);
    		rellena(palabras, archivo);
    		//buscaElRepetido(palabras);
    	}

    }
    return 0; 
}

/* ------ Aquí va la implementación de tus funciones ------ */
void imprime_instrucciones(){
	//La funcion puts solo imprime el output en la consola
 	puts("   Error: El formato de archivo es incorrecto\n\n   Uso: Nombre del ejecutable <archivo> [<archivo> [<archivo> ...]] <archivo>");
    return;
}

/*Inserta un elemento en la lista y se regresa el nuevo tamaño de la lista
  Los elementos se agregan al inicio de la lista, como una pila
*/
void inserta_elemento(Lista lista, Palabra *palabra){
	int indice =0;
	Elemento* doit = *lista;
	int found = 0;
	while(doit!=NULL){
		if(strcmp(doit->palabra->word, palabra->word) ==0 ){
			doit->palabra->apariciones +=1;
			found = 1;
			break;
		} 
		doit= doit->siguiente;
	}

	if(!found){
		//Creamos un nuevo elemento
		Elemento *recien = malloc(sizeof(Elemento));
		//Le damos direcciones a este nuevo elemento
		recien->siguiente = *lista;
		//Igualamos el valor del nuevo elemento a la nueva palabra
		recien->palabra = palabra;
		//Apuntamos la cabeza al nuevo elemento
		*lista = recien;
	}		
}

/*Imprime los elementos de la lista como cadenas*/
void imprime_lista(Lista lista){
	int indice = 0;
	Elemento *aux = *lista;
	indice =0;
	for(indice;indice<longitud(lista);indice++){
		Palabra *valorCabeza = aux->palabra;
		printf("la palabra en el indice %d es:  %s, aparece %d veces \n", indice, valorCabeza->word, valorCabeza->apariciones);
		aux = aux->siguiente;
	} 
}

/*Crea una lista vacía*/
Lista crea_lista(){
	//Se aparta el espacio en el heap para la lista
	Lista lista = calloc(1 ,sizeof(Lista));
	return lista;
}

/*Regresa el número de elementos en la lista*/
size_t longitud(Lista lista){
	if(*lista == NULL){
		return 0;
	} else{
		size_t size = 0;
		Elemento* derecho = *lista;
		while(derecho != NULL){
			derecho = derecho->siguiente;
			size+=1;
		}
        return size;
	}
}

void rellena(Lista palabras, FILE *archivo){
    // Se lee del archivo que este en indice
    char buffer[100];
    while(fgets(buffer, 100, archivo)) {
    	char *token_actual = strtok(buffer, " ,.-");
		while(token_actual != NULL) {
			Palabra *segmento = malloc(sizeof(Palabra));
    		segmento -> apariciones = 1;
    		//segmento -> word = strndup(token_actual,100);
			inserta_elemento(palabras, segmento);
       		token_actual = strtok (NULL, " ,.-");
    	}
    	printf("..................TU LISTA.....................\n");
    	imprime_lista(palabras);
    }
}

Palabra* buscaElRepetido(Lista lista){
	int indice = 0;
	Elemento* cabeza = *lista;
	int total = 0;
	Palabra *recopila;
	while(cabeza != NULL){
		if(cabeza -> palabra -> apariciones >= total){
			total = cabeza -> palabra -> apariciones;
			recopila = cabeza -> palabra; 
		}
		cabeza = cabeza -> siguiente;
	}
	printf("LA MAS REPETIDA ES:....%s\n", recopila -> word);
	return recopila;
}