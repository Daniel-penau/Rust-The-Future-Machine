#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <getopt.h>
#include <limits.h>
#include <unistd.h>


#define MAX_PATH 1024 //tamanio maximo de la ruta
#define SOCKETERROR (-1) // codigo de error de socket

/*Funcion para hacer un check de errores de socket
* ejecuta una instruccion y muestra un mensaje de 
* error si falla */
int check(int exp, const char* msg){

    if(exp == SOCKETERROR){
        perror(msg);
        exit(1);
    }
    return exp;
}