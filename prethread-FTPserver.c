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

int maximoConexiones, puerto; // conexiones amximas y puerto de entrada

struct sockaddr_in servidor, cliente; // estructuras del cliente y el servidor

int socketServer, socketAux; // socket principal y socket auxiliar (cliente)

int clienteLargo,serverLargo; // tamanio del cliente y el servidor sizeof()

char direccionRoot[MAX_PATH]; // ruta del servidor

/* Declaraciones de las funciones */
int check(int exp, const char* msg);
int charArrayToInt(char *pArray);
void CrearSocket();
void BindSocket();
void ModoEscucha();
void ServidorManager();
void ImprimirAyuda();
void IniciarServidor(int argc, char **argv);




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
/* Funcion para pasar un char* a int */
int charArrayToInt(char *pArray){
	return atoi(pArray);
}
/*Funcion que crea el socket del servidor*/
void CrearSocket(){
    
    
    check((socketServer = socket(AF_INET, SOCK_STREAM, 0)),
    "\nFallo la creacion del socket del servidor\n");
    
    printf("\nSocket del servidor creado correctamente\n");




}
/*Funcion que enlaza el socket del servidor*/
void BindSocket(){
    
    check(bind(socketServer,(struct sockaddr*)&servidor,sizeof(servidor)),
    "\nError haciendo el binding del socket del servidor\n");
}

/*Funcion que establece el servidor para escuchar conxiones*/
void ModoEscucha(){
    
    check(listen(socketServer,1),"\nError al entrar en modo escucha\n");
}


void ServidorManager(){

    //se crea el socket del server
    CrearSocket();

    //se inicializa la estructura del servidor
    servidor.sin_port = puerto;
    servidor.sin_addr.s_addr = INADDR_ANY;
    servidor.sin_family = AF_INET;
    //se hace el enlace del socket
    BindSocket();
    //se coloca el servidor en modo escucha
    ModoEscucha();

    //Ciclo infinito del servidor 
    while(true){

        printf("\nEsperando Conexiones...\n");
        clienteLargo = sizeof(cliente);

        check(socketAux = 
                accept(socketServer,(struct sockaddr*)&cliente,&clienteLargo),
                "\nError al aceptar conexiones\n");
        printf("\nConectado!\n");

        // Aca va lo que sea que haga el servidor 
        // se crean los hilos
        // se verifica que no se pase del maximo de conexiones
        // se ejecuta lo que pida el cliente

    }//fin del ciclo del servidor

}



void ImprimirAyuda(){
    printf("\n Menu de ayuda\n Argumentos necesarios:");
    printf("\n -n : numero maximo de conexiones soportadas por el servidor");
    printf("\n -w : direccion ftp-root del servidor ");
    printf("\n -p : puerto de conexion del servidor\n\n");

}

void IniciarServidor(int argc, char **argv){

    
	
	
	int option ;
	while((option = getopt(argc,argv,"n:w:p:a")) != -1)
	{
	
		switch (option)
		{
			case 'n':
				
				maximoConexiones = charArrayToInt(optarg);
			case 'w':
				strcpy(direccionRoot, optarg); 
				
			case 'p':
				
				puerto = charArrayToInt(optarg);
            
			}
        if(option == 'a') {
            ImprimirAyuda();
        }
	
	}
    if(direccionRoot != NULL && maximoConexiones != 0 && puerto != 0){

	printf("\n Numero de conexiones :%i \n ruta: %s \n puerto: %i \n\n",maximoConexiones,direccionRoot,puerto);

    }

    ServidorManager();
}




int main(int argc, char **argv)
{
    /* code */

    IniciarServidor(argc,argv);


    return 0;
}
