#include "micola.h"
#include <stdlib.h>

nodo_t* cabeza = NULL;
nodo_t* cola = NULL;

void encolar(int* cliente_socket){
    nodo_t *nuevonodo = malloc(sizeof(nodo_t));
    nuevonodo->cliente_socket = cliente_socket;
    nuevonodo->sig = NULL;
    if(cola == NULL){
        cabeza = nuevonodo;
    }
    else{
        cola->sig = nuevonodo;
    }
    cola = nuevonodo;

}

int* desencolar(){
    if(cabeza == NULL){
        return NULL;
    }
    else{
        int* resultado = cabeza->cliente_socket;
        nodo_t* temporal = cabeza;
        cabeza = cabeza->sig;
        if(cabeza == NULL){
            cola = NULL;
        }
        free(temporal);
        return resultado;
    }
}