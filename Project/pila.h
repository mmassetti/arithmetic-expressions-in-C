#ifndef _PILA_H_
#define _PILA_H_

/** Codigos de terminacion del programa */

    //Terminacion exitosa
    #define EXITO EXIT_SUCCESS
    //Pila sin inicializar
    #define PIL_NO_INI 9
    //La pila se encuentra vacia
    #define PIL_VACIA 10

/**Librerias*/
    #include <stdio.h>
    #include <stdlib.h>

/**Estructura de pila*/

    typedef struct pila {
        char* elemento;
        struct pila* proximo_elemento;
    } *pila_t;


/**Operaciones de pila*/

    /**Retorna una pila nueva vacia*/
    pila_t pila_crear();

    /**Retorna el string que se encuentra en el tope de la pila*/
    char* tope (pila_t pila);

    /**Elimina el string que se encuentra en el tope de la pila  y lo retorna*/
    char* desapilar(pila_t* pila);

    /**Inserta el string str en el tope de la pila*/
    int apilar(pila_t* pila, char* str);

    /**Retorna verdadero si la pila esta vacia, falso en caso contrario*/
    int pila_vacia (pila_t pila); //Retorna verdadero si la pila esta vacia, falso en caso contrario


#endif
