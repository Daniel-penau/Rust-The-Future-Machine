#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <limits.h>
#include <fcntl.h>
#include <stdbool.h>



#define MAX_PATH 1024 //tamanio maximo de la ruta
#define FILE_KEY "/bin/ls"//espaciod e memoria compartida
#define KEY_ACTIVE_PROCESS 202 //llave para la memoria compartida
#define KEY_INCOMING_CONNECTION 105 //llave de proceso entrante 
#define SOCKETERROR (-1) // codigo de error de socket



pid_t pidFork;
int * procesosHijos;
char buf[100], command[5], filename[25],*f;
int puerto;
int maximo;
int idMemCompProcActivo;
int idMemConexEntrante;
int *procesosActivos;
int coneccionEntrante;
int socketServer;
int numeroProceso;
int clienteLargo ;
struct sockaddr_in server, cliente;

struct stat obj;

int filehandle, tamanio, error;



void* ManejarConexion(int* p_cliente_socket);
int check(int exp, const char* msg);

//Funcion que transforma un strong a un int
int charArrayToInt(char *pArray)
{
	return atoi(pArray);
}


//Verfica que hayan procesos activos
int activeProcess()
{
	int count = 0;
	for(int i = 0; i < maximo; i++)
	{
		if(*(procesosActivos + i) == 1)
		{
			count++;
		}
	}
	return count;
}


//Verifica que los procesos estan disponibles para utilizarse
int verificarDisponibles(){
	
	int contador =-1;
	for (int i = 0; i<maximo; i++){
		if(procesosActivos[i] == 0 ){
			contador = i;
			
		}
		
	}
	return contador;
}


//Pone el bind al socket
void bindSocket(){
	
	//Datos iniciales
	server.sin_family = AF_INET; //TCP/IP
	server.sin_port = 20; //Conversion necesaria
	server.sin_addr.s_addr = INADDR_ANY; // Cualquiera puede conectarse
	bzero(&(server.sin_zero), 8);

	if(bind(socketServer, (struct sockaddr*) &server, sizeof(server)) == -1){
		printf("Error al activar le puerto\n");
		exit(-1);
	}else{
		printf("Socket del server asociado...\n");
	}
}

//Función que pone el socket del server en modo escucha
void escuchar(){
	int maxConexiones = 1024;
	if(listen(socketServer, maxConexiones) == -1){
		printf("Error en la escucha\n");
		exit(-1);
	}else{
		printf("Socket puesto en modo escucha...\n");
	}
	
}


//Limpia los procesos usa vez se a dejado de utilizar
void llenardeZero(){
	for(int i = 0; i < maximo-1; i++)
	{
		procesosActivos[i] = 0;
	}
}

int check(int exp, const char* msg){

    if(exp == SOCKETERROR){
        perror(msg);
        exit(1);
    }
    return exp;
}

//Aceptas y maneja las solicitudes 
void AceptarConexiones(){
	
	if(pidFork != 0){
		
		socketServer = socket(AF_INET, SOCK_STREAM, 0);
		if(socketServer == -1){
			
			printf("Error al crear el socket del server");
		}
		
		bindSocket();
		
		escuchar();
		printf("\naqui1\n");
		llenardeZero();
		printf("\naqui2\n");
		while(1){
			clienteLargo = sizeof(cliente);
			coneccionEntrante = accept(socketServer,(struct sockaddr*)&cliente,(socklen_t*)&clienteLargo);
			printf("conexion recibida\n");
			
			if(coneccionEntrante == -1){
				printf("Error al aceptar conexion");
			}
			else{
				
				int procesoDisponible = verificarDisponibles();
				printf("\nverifica %d\n",procesoDisponible);
				if(procesoDisponible >= 0){
					
					procesosActivos[procesoDisponible]  =1;
					
					send(coneccionEntrante,"me conecte a la vara",24,0);
					ManejarConexion(coneccionEntrante);
					
				}
				else{
					printf("Error Se exedio la carga del servidor\n");
					char *mensajeError = "Servidor sobre cargado";
					send(coneccionEntrante,mensajeError,strlen(mensajeError),0);
					shutdown(coneccionEntrante,2);
					close(coneccionEntrante);
					printf("conexion al proceso cerrada\n ");
					
				}
				
				
				
			}
		}
	}
	
	else{
		
		while(1){
			if(*(procesosActivos+ numeroProceso) == 1){
				coneccionEntrante = 0;
				//int actvProc = activeProcess();
				//aqui se llama a la funcion que se va a hacer
				
				shutdown(coneccionEntrante,2);
				close(coneccionEntrante);
				printf("conexion al proceso ya atendida y cerrada");
				*(procesosActivos + numeroProceso) =0;
			}
			
			
		}
		
	}
	
}

//Crear los procesos indicados
void StartPreForkServer(){
	
	int procesosCont = 0;
	
	pidFork = -1;
	
	procesosHijos = malloc(maximo * sizeof(int));
	while(procesosCont < maximo){
		
		pidFork = fork();
		if(pidFork == 0){
			break;
		}
		else{
			procesosHijos[procesosCont] = pidFork;
			procesosCont++;
			waitpid(-1, NULL, WNOHANG);
			
		}
		printf("\npid: %i\n",pidFork);
	}
	
	int llaveProcesoActivo;
	check(llaveProcesoActivo = ftok(FILE_KEY, KEY_ACTIVE_PROCESS),
	"\nerror al crear la key de memoria\n");

	int llaveProcesoEntrante = ftok(FILE_KEY, KEY_INCOMING_CONNECTION);
	idMemCompProcActivo = shmget(llaveProcesoActivo, sizeof(int) * (maximo), 0777 | IPC_CREAT );
	if(idMemCompProcActivo == -1){
		printf("\nerror1\n");
	}
	idMemConexEntrante = shmget(llaveProcesoEntrante, sizeof(int), 0777 | IPC_CREAT );
	procesosActivos = shmat(idMemCompProcActivo, NULL, 0);
	coneccionEntrante = shmat(idMemConexEntrante, NULL, 0);
	AceptarConexiones();
	
}

//Puene a funcionar el servidor
void IniciarServidor(int argc, char *argv[]){
	
	
	char direccionRoot[MAX_PATH];
	
	
	int option ;
	while((option = getopt(argc,argv,"n:w:p:h")) != -1)
	{
	
		switch (option)
		{
			case 'n':
				
				maximo = charArrayToInt(optarg);
			case 'w':
				strcpy(direccionRoot, optarg); 
				
			case 'p':
				
				puerto = charArrayToInt(optarg);
				
			}
	
	}
	printf("\n conexiones :%i \n ruta: %s \n puerto: %i \n",maximo,direccionRoot,puerto);
	chdir(direccionRoot);
	StartPreForkServer();
	
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


int main(int argc, char *argv[])
{
	IniciarServidor(argc,argv);
	return 0;
}

