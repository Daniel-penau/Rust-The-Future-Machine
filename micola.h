#ifndef MICOLA_H_
#define MICOLA_H_

struct nodo{
    struct nodo* sig;
    int *cliente_socket;
};
typedef struct nodo nodo_t;

void encolar(int* cliente_socket);
int* desencolar();

#endif