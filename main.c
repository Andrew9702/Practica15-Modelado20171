#include "main.h"
 // No hagas #include aquí, hazlos en main.h
 
 int main(int argc, char const *argv[])
 {
     // Verifica si hay al menos de 3 parametros
     // sino entonces se imprimen las instrucciones
     // y se para la ejecución del programa
     if (argc < 3){
         imprime_instrucciones();
         return 0;
 
     } else {

     	int indice = 1;
     	printf("\n***************************************************************************\n");
     	printf("\nNombre del archivo     Palabra mas repetida     Numero de repeticiones\n\n");
     	//Abrimos todos los archivos que se le pasan como parametros
     	FILE *archivo;
     	for(indice;indice<argc-1;indice++){
     	 	//Creamos una lista en donde guardaremos las palabras del archivo
    		Lista palabras = crea_lista();
     		archivo = fopen(argv[indice], "a+");
     		rellena(palabras, archivo);
     		Palabra *repetido = buscaElRepetido(palabras);
     		printf("%s\n", argv[indice]);
     		printf("                       %s", repetido->word);
     		printf("                       %d\n", repetido-> apariciones);

     	}

     	printf("\n*************************************************************************\n");
     	printf("\nSe guardo el resultado en el archivo %s\n", argv[argc-1]); 

     	FILE *resultado = fopen(argv[argc-1], "w");

     	fprintf(resultado, "\n***************************************************************************\n");
     	fprintf(resultado, "\nNombre del archivo     Palabra mas repetida     Numero de repeticiones\n\n");

     	int nuevoInd = 1;

     	//Ahora iteramos otra vez para escribir todo en un archivo
     	for(nuevoInd;nuevoInd<argc-1;nuevoInd++){
     	 	//Creamos una lista en donde guardaremos las palabras del archivo
    		Lista palabras = crea_lista();
     		archivo = fopen(argv[nuevoInd], "r");
     		rellena(palabras, archivo);
     		Palabra *repetido = buscaElRepetido(palabras);
     		fprintf(resultado, " %s\n", argv[nuevoInd]);
     		fprintf(resultado, "                       %s", repetido->word);
     		fprintf(resultado, "                       %d\n", repetido-> apariciones);
     	}

     	fprintf(resultado, "\n***************************************************************************\n");

    	fclose(resultado);
 
     }
     return 0; 
 }
 
 /* ------ Aquí va la implementación de tus funciones ------ */
 void imprime_instrucciones(){
 	//La funcion puts solo imprime el output en la consola
  	puts("\n   Error: El formato de archivo es incorrecto\n   Uso: Nombre del ejecutable <archivo> [<archivo> [<archivo> ...]] <archivo>");
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
 	Lista lista = calloc(1,sizeof(Lista));
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
 
/*Va a llenar una lista con estructuras palabra*/
void rellena(Lista palabras, FILE *archivo){
    // Se lee del archivo que este en indice
    char buffer[301];
    //Para obtener renglones
    while(fgets(buffer,300,archivo)){
     	//Primera palabra del archivo
     	char *token_actual = strtok(buffer, " ,.-\n\r");
     	//Mientras haya palabras en el archivo
 		while(token_actual != NULL) {
 			//Creamos un valor palabra para añadir a la lista
 			Palabra *segmento = malloc(sizeof(Palabra));
 			//Aumentamos las apariciones de la palabra
     		segmento -> apariciones = 1;
     		//Le damos como id la palabra que estaba en el archivo
     		//Asignamos memoria para más palabras
     		char*  copia = malloc(strlen(token_actual)+1);
     		strcpy(copia,token_actual);
     		segmento -> word = copia;
			
 			inserta_elemento(palabras, segmento);

 			//Nos deshacemos de la pabra y pasamos a la siguiente
        	token_actual = strtok (NULL, " ,.-\n\r");
     	}
    }
}

/*Va a iterar sobre la lista de cada archivo buscando la palabra que tenga más apariciones*/
Palabra* buscaElRepetido(Lista lista){
	//Hacemos una copia del primer elemento de la lista
    Elemento* cabeza = *lista;
    //Inicializamos una var temporal donde se va a almacenar las apariciones de cada palabra
    int total = 0;
    //Creamos una palabra que tomara el valor de donde iteramos
    Palabra *recopila;
    char * palabra;

    while(cabeza != NULL){
    	//Si la palabra en la que estamos tiene un valor de apariciones mayor al total que tenemos, entonces recopila
    	//se convierte en esta palabra
    	//Y nuestro total será las apariciones de recopila
        if(cabeza -> palabra -> apariciones >= total){
            recopila = cabeza -> palabra; 
            total = recopila -> apariciones;
            palabra = (char*)recopila -> word;
        }
        cabeza = cabeza -> siguiente;
    }
    //printf("LA PALABRA MAS REPETIDA ES: %s, CON %d\n", palabra, total);
    return recopila;
}
