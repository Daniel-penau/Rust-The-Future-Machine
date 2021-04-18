
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <netdb.h> 
#include <unistd.h>

#define SOCKETERROR (-1) // codigo de error de socket

struct sockaddr_in server;


int socketServer;

char buf[100], *f;

int size;

int filehandle;

void CrearSocket();
int check(int exp, const char* msg);

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

/*Funcion que crea el socket del servidor*/
void CrearSocket(){
    
    
    check((socketServer = socket(AF_INET, SOCK_STREAM, 0)),
    "\nFallo la creacion del socket del cliente\n");
    
}
void Conectar(){
    check(connect(socketServer,(struct sockaddr*)&server,sizeof(server)),
    "Fallo la conexion");
}

int main(int argc, char *argv[])
{

    int option ;
	
    /* code */
    unsigned long inaddr;
    inaddr = inet_addr(argv[1]);
    
    printf("%s",argv[1]);
    CrearSocket();
    server.sin_family = AF_INET;
    server.sin_port = 80;
    memcpy(&server.sin_addr, &inaddr, sizeof(inaddr));
    Conectar();
    
    
    if(!strcmp( argv[2] ,"ls")){


        strcpy(buf, "ls");
        send(socketServer, buf, 100, 0);
        
        recv(socketServer, &size, sizeof(int), 0);
        printf("\naca llegue\n");
        f = malloc(size);
        recv(socketServer, f, size, 0);
        filehandle = open("temp.txt", O_RDWR| O_CREAT | S_IRUSR);
        write(filehandle, f, size);
        close(filehandle);
        
        printf("\nEl ls del servidor es:\n");
        system("sudo cat temp.txt");
    }
                

        


    


    return 0;
}
