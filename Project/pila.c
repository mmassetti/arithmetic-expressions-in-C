#include "pila.h"

/**Operaciones de pila*/

pila_t pila_crear() {
	return NULL;
}

char* tope (pila_t pila) {
	char* elem="";
	if (pila_vacia(pila)) {
		exit(PIL_VACIA);
	}
	else {
		elem=pila->elemento;
	}
    return elem;
}

char* desapilar(pila_t* pila) {
    pila_t tmp=NULL;
    char* elem="";
    if (pila==NULL)
        exit(PIL_NO_INI);
    else if (pila_vacia(*pila))
        exit(PIL_VACIA);
    else {
        tmp= (*pila); //Guardo el tope
        elem= tope(*pila); //Obtengo el valor (el string) del tope
        (*pila)= (*pila)->proximo_elemento; //Actualizo el tope
        free(tmp); //Libero la memoria referencia tope anterior
    }
    return elem; //Retorno el string que se encontraba en el tope de la pila
}


int apilar(pila_t* pila, char* str) {
    pila_t tmp=malloc(sizeof(struct pila)); //Defino y una pila auxiliar y reservo espacio
    if (tmp==NULL)
        return 0; //Retorna falso si la operacion no se pudo realizar
    else if (pila==NULL) {
        exit(PIL_NO_INI);
    }
    else {
        tmp->elemento= str; //Inserto el string deseado en la pila auxiliar
        tmp->proximo_elemento= *pila; //La pila en el tope anterior ahora es el proximo elemento de la pila auxiliar
        *pila= tmp; //El nuevo  tope ahora es la pila auxiliar
    }
    return EXITO; //Retorna verdadero si la operacion se realizo correctamente
}

int pila_vacia (pila_t pila) {
    return pila==NULL;
}

