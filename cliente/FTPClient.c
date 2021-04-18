
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

char buf[100], *f, filename[25];

int size, status;

int filehandle;
struct stat obj;

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

    
	
    /* code */
    unsigned long inaddr;
    inaddr = inet_addr(argv[1]);
    
    //printf("%s",argv[1]);
    CrearSocket();
    server.sin_family = AF_INET;
    server.sin_port = 80;

    memcpy(&server.sin_addr, &inaddr, sizeof(inaddr));
    Conectar();

    for(int i = 2; i<argc;i++){
        
        printf("\n argumento > %s",argv[i]);

        if(!strcmp( argv[i] ,"ls")){


            strcpy(buf, "ls");
            send(socketServer, buf, 100, 0);
            
            recv(socketServer, &size, sizeof(int), 0);
            //printf("\naca llegue\n");
            f = malloc(size);
            recv(socketServer, f, size, 0);
            filehandle = open("temp.txt", O_RDWR| O_CREAT | S_IRUSR | S_IWUSR );
            write(filehandle, f, size);
            close(filehandle);
            
            printf("\nEl ls del servidor es:\n");
            system("sudo cat temp.txt");
            system("unlink temp.txt");
            
        }

        else if(!strcmp( argv[i] ,"cd")){

            strcpy(buf, "cd");

            printf("\n Escriba el directorio nuevo del servidor remoto: ");
            scanf("%s",buf+3);
            printf("\n%s\n",buf+3);
            send(socketServer,buf,100,0);
            printf("\ncontrol\n");
            recv(socketServer,&status,sizeof(int),0);
            if(status){
                printf("\nse cambio el directorio correctamente \n");
            }
            else{
                printf("\nFallo el cambio de directorio\n");
            }

        }
        else if(!strcmp(argv[i],"put")){
            printf("\nIngrese el nombre del archivo a subir: ");
            scanf("%s",filename);

            check(filehandle = open(filename,O_RDONLY),
            "\nError:el archivo no existe en el directorio\n");



            strcpy(buf, "put ");
            strcat(buf,filename);
            send(socketServer,buf,100,0);
            stat(filename,&obj);
            size = obj.st_size;
            send(socketServer,&size,sizeof(int),0);
            sendfile(socketServer,filehandle,NULL,size);
            recv(socketServer,&status,sizeof(int),0);
            if(status){
                printf("\nSe agrago correctamente el archivo al servidor");
            }
            else{
                printf("\nFallo al agregar el archivo al servidor");
            }

        }
        else if(!strcmp(argv[i],"get")){

            printf("\nIngrese el nombre del archivo a obtener: ");
            scanf("%s",filename);
            strcpy(buf, "get ");
            strcat(buf,filename);
            send(socketServer,buf,100,0);

            recv(socketServer,&size,sizeof(int),0);
            
            filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
            
            if(filehandle == -1){
                printf("\nerror al crear el archivo a guardar\n");
            }


            f = malloc(size);
            recv(socketServer,f,size,0);
            write(filehandle,f,size);
            close(filehandle);
        }

    }
    
    
                

        


    


    return 0;
}
