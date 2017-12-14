#include "lista.h"
#include "pila.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <getopt.h>

/** Codigos de terminacion del programa */

    //Expresion mal formada falta o exceso de parentesis.
    #define	EXP_MALF 2
    //Demasiados operandos para el operador.
    #define OPND_DEMAS 5
    //Insufisientes operandos para el operador.
    #define OPND_INSUF 6
    //Operando invalido.
    #define OPND_INV 7
    //Operando invalido.
    #define OPRD_INV 8

    //Division por '0'.
    #define DIV_CERO 11

    //Archivo inexistente
    #define FILE_NOT_FOUND 12


/** Prototipos */

int esNumero(char elem);
int esOperador(char elem);
int esBlanco(char elem);

int evaluarExpresion(char* cadena);

int suma(lista_t operandos);
int resta(lista_t operandos);
int division(lista_t operandos);
int producto(lista_t operandos);

char op_suma='+';
char op_resta='-';
char op_producto='*';
char op_division='/';
char par_abre='(';

/** Variables de archivos */
FILE *entrada=NULL;
FILE *salida=NULL;

/** Programa principal */

int main(int argc , char* argv []){
    int option;
    char cadena[50];
    while((option=getopt(argc,argv,"hi:o:"))!=1){
		switch(option){
			case'h':
				printf("Evaluar expresion aritmetica ingresada en prefijo\n");
				printf("Opciones de linea de comando : \n");
				printf("-h sin parámetros para texto de ayuda. \n");
				printf("-i nombre_archivo.txt, lectura de expresion por archivo. \n");
				printf("-o nombre_archivo.txt, escritura de expresion por archivo. \n");
				exit(0);
			case'i':
				entrada=fopen(optarg,"r");
				if(entrada==NULL){
					printf("Error archivo inexistente.\n");
					exit(FILE_NOT_FOUND);
				}
				break;
			case'o':
				salida=fopen(optarg,"a");
				break;
			default:
				printf("Lectura y escritura por consola. \n");
				return 1;
		}
	}

	if(entrada!=NULL){
		fgets(cadena,50,entrada);
		fclose(entrada);
	}
	else{
		printf("Ingrese una expresion en formato prefijo: \n");
		scanf("%[^\n]",cadena);
	}

    int resultado = evaluarExpresion(cadena);

	if(salida!=NULL){
		fprintf(salida,"%i",resultado);
		fclose(salida);
	}
	else
		printf("El resultado es : %i\n",resultado);

    printf("El resultado es = %i \n",resultado);

    return 0;
 }

 int evaluarExpresion(char* cadena) {

    //VARIABLES LOCALES

    int pos=0;  //pos indica la posicion actual de la cadena que estoy leyendo
    int fin=strlen(cadena);  //Fin indica el largo de la cadena que recibo
    pila_t pila = pila_crear(); //Estructura utilizada para poder efectuar los calculos en notacion prefija.
    char letra; // Almacena el caracter actual de la cadena.
    int esParentesis=0; // Flag utilizado para verificar que no hayan dos parentesis abiertos seguidos.

    letra = cadena[pos];
    if(letra != '(') { // La cadena necesariamente debe comenzar con parentesis que abre.
         exit(EXP_MALF);
    }
    else //Comienzo a procesar la cadena
    {
        while(pos<fin)  { // Mientras no se termine de procesar la cadena.
            letra = cadena[pos++];

            if (letra!=' ') { // Si es espacio se avanza en la cadena.

                if(letra=='('){ // Si es un parentesis que abre se apila.
                    apilar(&pila,&par_abre);
                }

                if(esNumero(letra)){ //Procesamiento para que todo el numero quede en un solo char * .
                    int indice=0;
                    char * arreglo=malloc(sizeof(char)*100);
                    arreglo[indice++] = letra;
                    letra = cadena[pos++];

                    while(!esBlanco(letra) && esNumero(letra) && pos<fin) { //Por si el numero tiene mas de un digito
                        arreglo[indice++] = letra;
                        letra= cadena[pos++];
                    }

                    if(esBlanco(letra) || letra==')') { //Armar a la cadena y la apilas
                        char *resultado = malloc(strlen(arreglo)+1);
                        strcpy(resultado,arreglo);
                        apilar(&pila,resultado);
                    }


                } // Fin de procesamiento de un numero.

                if(esOperador(letra)) {  //Apilo operando o parentesis abierto y hago control de doble parentesis abiertos

                        if (letra=='(' && esParentesis==1){ //Error se leyeron 2 parentesis que abren seguidos.
                            exit(EXP_MALF);
                        }
                        else{
                            esParentesis=0;
                            printf("Apilo un operador %c \n",letra);

                                if(letra=='+')
                                    apilar(&pila,&op_suma);

                                if(letra=='-')
                                    apilar(&pila,&op_resta);

                                if(letra=='*')
                                    apilar(&pila,&op_producto);

                                if(letra=='/')
                                    apilar(&pila,&op_division);

                                if (letra == '(')
                                    esParentesis= 1;  //Dejo un flag activado para la proxima iteracion controlar si es parentesis
                        }
                    }

                if(letra==')'){ //Parentesis cerrado, tengo que procesar y calcular el valor correspondiente. Aca interactua la lista. Antes solo pila

                    char * tope_pila=malloc(sizeof(char)*2);
                    lista_t lista=lista_crear();
                    tope_pila=desapilar(&pila);
                    while (!esOperador(tope_pila[0]) && esNumero(tope_pila[0]) ) {
                        int operador=atoi(tope_pila);
                        lista_adjuntar(lista,operador);
                        tope_pila= desapilar(&pila);
                    }

                    //Al finalizar el while la variable tope es el operador.

                    printf("La operacion a realizar es : %c \n",tope_pila[0]);

                    char * parentesisAbre=desapilar(&pila);

                    if(parentesisAbre[0]!='('){ //Desapilo el parentesis abierto ( si no hay parentesis fallo ).
                        exit(EXP_MALF);
                    }

                    int numero=0;
                    char operacion=tope_pila[0];

                    if(operacion == '+'){
                        numero = suma(lista);
                    }

                    if(operacion == '-') {
                        numero =resta(lista); //Controlo cantidad de elemntos de lista, si es mayor a 2, error
                    }

                    if(operacion == '/'){
                        numero =division(lista); //Controlo cantidad de elemntos de lista, si es mayor a 2, error

                        if(numero==-1){
                            exit(DIV_CERO);
                            break;
                        }
                    }

                    if(operacion == '*'){
                        numero = producto(lista);
                    }

                    lista_destruir(&lista);

                    char * res=malloc(sizeof(char)*100);
                    sprintf(res,"%d",numero);
                    apilar(&pila,res);

                }

            } //FIN IF ES ESPACIO.


        } //FIN WHILE .

    } //FIN IF ES PARENTESIS , VERIFICACION INICIAL.

    //Terminamos de procesar la cadena de entrada

    char * resultado = desapilar(&pila);

    int res= atoi(resultado);

    if (!pila_vacia(pila)){
        exit(EXP_MALF);
    }

    return res;
}


int resta(lista_t operandos){
    int cantidad=lista_cantidad(operandos);
    int resultado=0;

    if(cantidad==1){ // ES UN NUMERO NEGATIVO
        resultado=(lista_obtener(operandos,0)*(-1));
        return resultado;
    }else{
        if(cantidad!=2){
            exit(OPND_DEMAS);
        }
        else{
            int op1=lista_obtener(operandos,0);
            int op2=lista_obtener(operandos,1);
            resultado=op2-op1;
        }
        return resultado;
    }
}

int suma(lista_t operandos){
    int cantidad=lista_cantidad(operandos);
    int resultado=0;
    int i;
    if(cantidad>1){
        for(i=0;i<cantidad;i++){
            resultado+=lista_obtener(operandos,i);
        }
    }
    else
        printf("Error en suma");


    return resultado;

}

int producto(lista_t operandos){
    int cantidad=lista_cantidad(operandos);
    int resultado=1;
    int i;
    if(cantidad>1){
        for(i=0;i<cantidad;i++){
            resultado*=lista_obtener(operandos,i);
        }
    }
    else
        printf("Error en producto");


    return resultado;

}

int division(lista_t operandos){

    int cantidad=lista_cantidad(operandos);
    int resultado=0;
    if(cantidad!=2){
        exit(OPND_DEMAS);
    }
    else{
        int op1=lista_obtener(operandos,0);
        int op2=lista_obtener(operandos,1);
        if(op1!=0)
            resultado=op2/op1;
        else
            return -1;
    }


    return resultado;
}

int esNumero(char elem) {
    return isdigit(elem);
}

int esOperador(char elem ) {
    return (elem=='+' || elem=='-' || elem=='/' || elem=='*' );
}

int esBlanco (char elem) {
    return (elem==' ');
}
