#ifndef LISTA_H_
#define LISTA_H_

/** Codigos de terminacion del programa */

    //Terminacion exitosa
    #define	EXITO EXIT_SUCCESS
    //Lista sin inicializar
    #define LST_NO_INI 3
    //Intento de acceso a posicion invalida en lista
    #define LST_POS_INV 4

/** Librerias */
    #include <stdio.h>
    #include <stdlib.h>


/** Estructura de celda */
    typedef struct celda {
        int elementos[4];
        struct celda* proxima_celda;
    } celda_t;

/** Estructura de lista eficiente */
    typedef struct lista_eficiente {
        unsigned int cantidad_elementos;
        celda_t* primera_celda;
    } *lista_t;


/** Definimos las signaturas de los metodos auxiliares . */

/** Reserva espacion en memoria para crear una celda y la retorna . */
celda_t* crearCelda(int entero);

/** Retorna la celda en la posicion indicada , es utilizada por los metodos insertar y eliminar . */
celda_t* obtenerCelda(lista_t lista,int nro_celda);

/** Reacomoda la lista luego de una eliminacion . */
void reacomodarLista(lista_t lista,int indice,celda_t* celda);

/** Realiza el free a una celda . */
void destruirCelda(celda_t* celda);

/** Recorre la lista y va eliminando las celdas recursivamente . */
void destruir_lista_aux(celda_t * celda);

/** Retorna la cantidad de celdas de la lista . */
int cantidad_celdas(lista_t lista);


/** Operaciones de lista_eficiente */

    /** Crea una lista vacía y la retorna. */
    lista_t lista_crear();

    /**Inserte el elemento elem en la posicion pos de la lista.
    Sobrescribe el valor existente en la posicion indicada, o agrega un nuevo elemento si la posición coincide con la cantidad de elementos.
    Si procede exitosamente retorna verdadero.En otro caso retorna falso.*/

    int lista_insertar(lista_t lista,unsigned int pos,int elem);

    /** Elimina el elemento en la posicion pos. Reacomoda la lista adecuadamente al eliminar en posiciones intermedias.
    Retorna verdadero si procede con éxito, falso en caso contrario. Si la posicion no es válida,
    aborta con exit status LST_POS_INV.*/

    int lista_eliminar(lista_t lista,unsigned int pos);

    /** Retorna la cantidad de elementos de la lista. Si la lista no está inicializada, el programa aborta
    con exit status LST_NO_INI.*/
    int lista_cantidad(lista_t lista);

    /** Retorna el elemento en la posicion pos de la lista.
    Si la posicion no es valida, aborta con exit status LST_POS_INV.*/
    int lista_obtener(lista_t lista,unsigned int pos);

    /** Inserta el elemento elem en la ultima posicion de la lista.
    Si la lista no esta inicializada, aborta con exit status LST_NO_INI.*/
    int lista_adjuntar(lista_t lista,int elem);

    /** Libera la memoria ocupada por la lista y le asigna NULL. Retorna verdadero en caso de exito.
        Si la lista no esta inicializadam aborta con exit status LST_NO_INI.*/
    int lista_destruir(lista_t *lista);

    /** Luego de eliminar una posicion de la lista se utiliza este metodo para acomodar las posiciones con
    sus respectivos elementos en la lista.
    */
    void reacomodarLista(lista_t lista,int indice,celda_t * celda);

    /** Elimina una celda y libera el espacio asignado en memoria.
    */
    void destruirCelda(celda_t* celda);

    /** Retorna la celda creada en la posicion nro_celda.
    */
    celda_t* obtenerCelda(lista_t lista,int nro_celda);


#endif
