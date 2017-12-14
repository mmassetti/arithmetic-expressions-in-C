#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


/** Implementacion de metodos de lista.  */

lista_t lista_crear(){
    lista_t lista=malloc(sizeof(struct lista_eficiente)*4);
    lista->primera_celda=NULL;
    lista->cantidad_elementos=0;
    return lista;
}

int lista_insertar (lista_t lista,unsigned int pos,int elem) {

    // Si la cantidad de elementos es menor que la posicion en la que se
    // quiere insertar , se produce un error . La posicion no es valida.

    if(lista->cantidad_elementos<pos)
        exit(LST_POS_INV);

    // Si la posicion ingresada esta dentro del rango entonces se realizara
    // una insercion.

    // Caso 1
    // Situacion : La lista se encuentra vacia , se debe crear una celda e insertar
    // el elemento en la primera posicion del arreglo.

    if (lista->cantidad_elementos==0) {
        celda_t* nueva_celda=crearCelda(elem); // Creamos una celda
        nueva_celda->proxima_celda=NULL; // Seteamos la siguiente celda como NULL. nueva_celda-->NULL
        lista->primera_celda=nueva_celda; // Seteamos nuestro header como nueva_celda.
    }
    else{//Se realizara una insercion sabiendo que ya hay elementos en la lista

        int nro_celda= pos/4;  //Celda donde se insertara el nuevo elemento.
        int indice_insertar= pos%4; // Indice del  arreglo de 4 elementos , donde se insertara el elemento.
        int cant_celdas=cantidad_celdas(lista); // Cantidad de celdas de la lista

        celda_t* celda_Actual = obtenerCelda(lista,nro_celda);

        //Caso 2
        //Situacion: Se debe insertar el elemento en una celda que ya contiene
        // un elemento en el indice indicado.(Se remplazara el elemento con el nuevo proporcionado).
        if(cant_celdas > nro_celda) { //Debo insertar en una celda existente.
                celda_Actual->elementos[indice_insertar] = elem;
        } else
            //Caso 3
            // Situacion : se quiere insertar un elemento en una lista que posee
            // todas las celdas ocupadas. Se creara una nueva_celda y se insertara el elemento.
            if (cant_celdas-nro_celda==0 && indice_insertar==0) {
                celda_t* nueva_celda=crearCelda(elem); //  Creamos una nueva_celda y colocamos el elemento en su primera componente.
                celda_Actual->proxima_celda= nueva_celda; // a celda_Actual le seteamos como proxima celda nuestra nueva_celda.
            }
    }

    // Si la cantidad de elementos es menor
    // que la pos donde se quiso insertar quiere decir
    // que agrege un nuevo elemento sino , sobreescribi uno antiguo.
    if(lista->cantidad_elementos==pos)
        lista->cantidad_elementos++;

    return EXITO;

}

int lista_eliminar(lista_t lista, unsigned int pos){

     // Si la cantidad de elementos es menor que la posicion en la que se
    // quiere eleminar , se produce un error . La posicion no es valida.


     if(lista->primera_celda==NULL){
         exit(LST_NO_INI);
     }

    if(lista->cantidad_elementos<pos){
        exit(LST_POS_INV);
     }


    //Caso 1
    // Se solicita eliminar el unico elemento de la lista.
    if(lista->primera_celda!=NULL && lista->cantidad_elementos>pos){
        if(pos==0 && lista->cantidad_elementos==1){
            celda_t * celda_eliminar=lista->primera_celda;
            lista->primera_celda=NULL;
            destruirCelda(celda_eliminar);
            lista->cantidad_elementos--;
        }
        else{
            //Caso 2
            // Se debe realizar una eliminacion dentro de una lista con mas de
            int nro_celda= pos/4;
            int indice_eliminar= pos%4;
            celda_t* celda_modificar = obtenerCelda(lista,nro_celda);
            //"Elimino" el elemento,le seteo null y el reacomodarLista se encargar de hacer los corrinmientos necesarios
            celda_modificar->elementos[indice_eliminar]='\0';
            reacomodarLista(lista,indice_eliminar,celda_modificar);
        }
    }


    return EXITO;

}


void reacomodarLista(lista_t lista,int indice,celda_t * celda_Actual){

    //En este ciclo realiza los intercambios arreglo[i]=arreglo[i+1]
    while(indice<3){
        celda_Actual->elementos[indice]=celda_Actual->elementos[indice+1];
        celda_Actual->elementos[indice+1]='\0';
        indice++;
    }

    // Luego de los intercabios necesarios es arreglo quedara de esta forma
    // |elem1|elem2 |elem3 |NULL |


    //Ahora tendremos 2 casos a analizar
    //Caso 1
    //Situacion: la proxima celda es NULL .
    // Debemos verificar que en la celda en la que eliminamos queden elementos
    // de no ser asi debemos eliminarl la celda.

    if(celda_Actual->proxima_celda==NULL){

        if(celda_Actual->elementos[0]=='\0'){ // Si la celda quedo vacia
            //Busco la celda anterior a la actual
            celda_t* pos_lista=lista->primera_celda;
            while(pos_lista->proxima_celda!=celda_Actual)
                pos_lista=pos_lista->proxima_celda;

            pos_lista->proxima_celda=NULL;
            destruirCelda(celda_Actual);
        }

    }
    else{//Tengo una celda siguiente y debo "rellenar" la celda actual

        // Tomo el primer elemento de la celda siguiente, lo guardo en una variable.
        int elemento_de_celda_siguiete=celda_Actual->proxima_celda->elementos[0];
        // Marco el primer elemento de la celda siguiente.
        celda_Actual->proxima_celda->elementos[0]='\0';
        //Coloco el elemento de la celda siguiente en la celda actual
        celda_Actual->elementos[3]=elemento_de_celda_siguiete;

        //Ahora la proxima celda puede haberme quedado vacia .

        //Si quedo vacia.
        if(celda_Actual->proxima_celda->elementos[0]=='\0' && celda_Actual->proxima_celda->elementos[1]=='\0'){ //SI los primeros 2 elemenos de la celda que sigue estan nulos , entones es una celda vacia
            destruirCelda(celda_Actual->proxima_celda); // Le pido que elimine la proxima celda porque se quedo sin elementos
            celda_Actual->proxima_celda=NULL;  // Le seteo NULL la proxima celda.
        }
        else //Si no quedo vacia debo reacomodar la celda siguiente en la pos=0
            reacomodarLista(lista,0,celda_Actual->proxima_celda);
    }

}

int lista_adjuntar(lista_t lista, int elem){
    //Delego la insercion en el mentodo lista_insertar y le paso la cantidad
    // de elementos de la lista (es la ultima posicion)
    return lista_insertar(lista,lista->cantidad_elementos,elem);

}

int lista_cantidad (lista_t lista){
    return lista->cantidad_elementos;
}

int lista_obtener (lista_t lista,unsigned int pos){

    //Si la lista esta vacia.
    if(lista->primera_celda==NULL)
        exit(LST_NO_INI);


    if(lista->cantidad_elementos<pos)
        exit(LST_POS_INV);


    int nro_celda=pos/4;
    int indice_celda=pos%4;
    celda_t * pos_celda=obtenerCelda(lista,nro_celda);
    return pos_celda->elementos[indice_celda];

}

int lista_destruir(lista_t *lista){
    if((*lista)->primera_celda==NULL){
        exit(LST_NO_INI);
     }

    destruir_lista_aux((*lista)->primera_celda);
    (*lista)->primera_celda=NULL;
    (*lista)->cantidad_elementos=0;
    free((*lista));
    *lista=NULL;

    return EXITO;
}


/** Implementacion de metodos auxiliares.  */

celda_t* crearCelda(int entero){
    celda_t* celda= malloc(sizeof(struct celda));
    celda->elementos[0]= entero;
    celda->proxima_celda=NULL;
    return celda;
}

void destruirCelda(celda_t* celda){
    free(celda);
}

void destruir_lista_aux(celda_t * celda){
   if(celda->proxima_celda!=NULL){
        destruir_lista_aux(celda->proxima_celda);
   }
   free(celda);
}

celda_t* obtenerCelda(lista_t lista,int nro_celda) {
    int i=0;
    celda_t* pos_celda;

    if (lista->cantidad_elementos==0)
        pos_celda= NULL;
    else {
        pos_celda= lista->primera_celda;
        while (i<nro_celda && pos_celda->proxima_celda != NULL){
            pos_celda= pos_celda->proxima_celda;
            i++;
        }
    }
    return pos_celda;
}

int cantidad_celdas(lista_t lista){
    int cant_celdas=0;
    if(lista==NULL)
        return 0;
    celda_t* celda_Actual=lista->primera_celda;
    while(celda_Actual!=NULL){
        celda_Actual=celda_Actual->proxima_celda;
        cant_celdas ++;
    }
    return cant_celdas;
}

