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
#include <pthread.h>
#include "micola.h"




#define MAX_PATH 1024 //tamanio maximo de la ruta
#define SOCKETERROR (-1) // codigo de error de socket




int maximoConexiones, puerto; // conexiones maximas y puerto de entrada

struct sockaddr_in servidor, cliente; // estructuras del cliente y el servidor

int socketServer, socketAux; // socket principal y socket auxiliar (cliente)

int clienteLargo,serverLargo; // tamanio del cliente y el servidor sizeof()

char direccionRoot[MAX_PATH]; // ruta del servidor

char buf[100], command[5], filename[25],*f;

int filehandle, tamanio, error;

int conexionesActivas = 0, enEspera = 0;

struct stat obj;

pthread_t *thread_pool; //pool de hilos a usar
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //mutex para manejar las estructuras

/* Declaraciones de las funciones */
int check(int exp, const char* msg);
int charArrayToInt(char *pArray);
void CrearSocket();
void BindSocket();
void ModoEscucha();
void ServidorManager();
void ImprimirAyuda();
void IniciarServidor(int argc, char **argv);
void* funcion_hilo(void*arg);
void* ManejarConexion(int* p_cliente_socket);


/*Funcion que crea el pool de hilos*/
void crearHilos(){

    for(int i = 0; i<maximoConexiones;i++ ){
        pthread_create(&thread_pool[i],NULL,funcion_hilo,NULL);
    }


}

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

    crearHilos();

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

        
    
        clienteLargo = sizeof(cliente);
        if(enEspera == 0 ){
            printf("\nEsperando Conexiones...\n");

            check(socketAux = 
                accept(socketServer,(struct sockaddr*)&cliente,(socklen_t*)&clienteLargo),
                "\nError al aceptar conexiones\n");
        }
        
        
        

        if(conexionesActivas < maximoConexiones){ 
            enEspera = 0;
            printf("\nConectado!\n");
            conexionesActivas++;
            send(socketAux,"\nConectado\n",24,0);

            // Aca va lo que sea que haga el servidor 
            // se crean los hilos
            // se verifica que no se pase del maximo de conexiones
            // se ejecuta lo que pida el cliente

            int* pcliente = malloc(sizeof(int));
            *pcliente = socketAux;

            //se usa el mutex para asegurar que solo un hilo use la cola a la vez
            pthread_mutex_lock(&mutex);
            encolar(pcliente);
            pthread_mutex_unlock(&mutex);
        }
        else{
            int cola = conexionesActivas-maximoConexiones+1;
            char mensaje[100] = "\nMaximo de conexiones superado su posicion en cola es ";
            char buffer[3];
            sprintf(buffer,"%d\n",cola);

            send(socketAux,strcat(mensaje,buffer),100,0);

            if(enEspera == 0){
                printf("\nServidor sobrecargado\n"); 
            }
            enEspera = 1;
            
            

        }

    }//fin del ciclo del servidor

}

/* Funcion para ejecutar los comando en cada hilo*/
void* funcion_hilo(void*arg){
    
    while (true){
        

        int* pcliente ;

        pthread_mutex_lock(&mutex);
        pcliente = desencolar();
        pthread_mutex_unlock(&mutex);

        if(pcliente != NULL){
            //aca se llama a lo que se va a hacer en el servidor los ls cd put get etc
            
            ManejarConexion(pcliente);
            conexionesActivas--;
        }
    }
    pthread_exit(NULL);
    
}

/*Funcion que imprime el menu de ayuda*/
void ImprimirAyuda(){
    printf("\n Menu de ayuda\n Argumentos necesarios:");
    printf("\n -n : numero maximo de conexiones soportadas por el servidor");
    printf("\n -w : direccion ftp-root del servidor ");
    printf("\n -p : puerto de conexion del servidor\n\n");

}
/*Funcion que arranca el servidor y obtiene los parametros a utilizar*/
void IniciarServidor(int argc, char **argv){

    
	
	
	int option ;
	while((option = getopt(argc,argv,"n:w:p:a")) != -1)
	{
	
		switch (option)
		{
			case 'n'://numero de conexiones maximas
				
				maximoConexiones = charArrayToInt(optarg);
			case 'w':// direccion root del servidor
				strcpy(direccionRoot, optarg); 
				
			case 'p':// puerto del servidor
				
				puerto = charArrayToInt(optarg);
            
			}
        if(option == 'a') {//para solucitar la ayuda
            ImprimirAyuda();
            exit(1);
        }
	
	}
    if( maximoConexiones != 0 && puerto != 0){//verifica que no este vacio para imprimir

        printf("\n Numero de conexiones :%i \n ruta: %s \n puerto: %i \n\n",maximoConexiones,direccionRoot,puerto);

        //se crea el array para el pool de hilos
        pthread_t thread_pool_aux[maximoConexiones];
        thread_pool = &thread_pool_aux[0];

        chdir(direccionRoot);
        ServidorManager();

    }
    if(maximoConexiones == 0 && puerto == 0){


        printf("\nError: Faltan argumentos utilice el argumento -a para recibir ayuda\n");
    }
    
}

void* ManejarConexion(int* p_cliente_socket){


    
    while(recv(*p_cliente_socket, buf, 100, 0)){


        sscanf(buf, "%s", command);
        

        if(!strcmp(command, "ls")){
            
            system("ls >temps.txt");

            stat("temps.txt",&obj);
            tamanio = obj.st_size;
            send(*p_cliente_socket, &tamanio, sizeof(int),0);
            filehandle = open("temps.txt", O_RDONLY);
            sendfile(*p_cliente_socket,filehandle,NULL,tamanio);
            
            //close(filehandle);
        }
        else if(!strcmp(command, "cd")){

            if(chdir(buf+3) == 0){

                error=1;

                send(*p_cliente_socket,&error,sizeof(int),0);
                
            }
            else{
                error=0;
                send(*p_cliente_socket,&error,sizeof(int),0);
            }
        }
        else if(!strcmp(command,"put")){
            error =0;
            sscanf(buf+strlen(command),"%s",filename);
            recv(*p_cliente_socket,&tamanio,sizeof(int),0);
            
            filehandle = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0666);
            
            if(filehandle == -1){
                printf("\nerror al crear el archivo a guardar\n");
            }
            f = malloc(tamanio);
            recv(*p_cliente_socket,f,tamanio,0);
            error = write(filehandle,f,tamanio);
            close(filehandle);
            send(*p_cliente_socket,&error,sizeof(int),0);

        }

        else if(!strcmp(command,"get")){

            sscanf(buf+strlen(command),"%s",filename);
            check(filehandle = open(filename,O_RDONLY),
            "\nError:el archivo no existe en el directorio\n");

            stat(filename,&obj);
            tamanio = obj.st_size;
            send(*p_cliente_socket,&tamanio,sizeof(int),0);
            sendfile(*p_cliente_socket,filehandle,NULL,tamanio);
            


        }
    }
    
    return 0 ;
}




int main(int argc, char **argv)
{
    /* code */

    IniciarServidor(argc,argv);


    return 0;
}
