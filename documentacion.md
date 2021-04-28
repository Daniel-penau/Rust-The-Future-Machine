# Tecnológico de Costa Rica
## Escuela de Ingeniería en Computación
### Principios de sistemas operativos

# Rust the future machine

### Desarrollado por
* #### Jose Daniel Peñaranda Umaña (2013039845)
* #### Carlos Mora Murillo (2017238926)

##### Alajuela, I-S 2021

******

## Introdución
Los Web Servers comúnmente trabajan en un mínimo de sus capacidades sin embargo existen picos de uso y es donde se debe recurrir a técnicas para poder satisfacer la demanda, ellas son el pre forked y el pre thread técnicas que nos ayudarán a manejar de mejor forma los recursos disponibles en el servidor.

## Ambiente de Desarrollo

La tarea se implementó en los siguientes ambientes de trabajo:

- Ubuntu en su última	versión como sistema operativo
- VScode como IDE de desarrollo
- GCC
- Python3

## Estructuras de datos usadas y funciones
### Pre Forked Server
#### IniciarServidor()

Esta función se encarga de tomar los parámetros del input y establecer todas las configuraciones para el servidor.


#### StartPreForkServer()

Esta función se encarga de crear los procesos, mediante fork y punteros, que se van a utilizar , además de establecer sus espacios de memoria y memoria compartida.

#### AceptarConexiones()

Esta función se encarga de escuchar y gestionar las conexiones entrantes al servidor, asignando un proceso a cada conexión, también gestiona sí el servidor está sobrecargado.

#### createSocketPair()

Esta función es la encargada de crear y emparejar el socket interno que se va a utilizar para la memoria compartida. 

#### bindSocket()

Se encarga de crear y enlazar con el servidor su socket de funcionamiento.



### PreThread Server

#### main()

Se encarga de procesar los parámetros de entrada o inputs

#### hilosServer()

Es el encargado de manejar el funcionamiento del servidor, mantiene el ciclo de escucha y ejecuta las peticiones de los usuarios.

#### crearHilos()

Se encarga de crear los hilos que van a ser utilizados por los usuarios.

#### controlHilo()

Se encarga de manejar los hilos para la ejecución de solicitudes.

#### crearSocket()

Se encarga de crear el socket que va a ser utilizado por el servidor.


#### bindServer()

Se encarga de enlazar el socket y avisarle al sistema operativo que ese socket es del servidor.

### manejarSolicitud()

Función que recibe de parametro el socket del cliente a atender. Se encarga de leer el tipo de método y lo que esta solicitando

### solicitudGET()

Se encarga de llevar a cabo el método GET, recibe como parametro el socket del cliente y el recurso solicitado.


### httpClient en python

#### curlData()

Se utiliza el curl para descargar un recurso.


### httpClient en C



#### solicitarRecurso()

Recibe la dirección del recurso que se obtendrá. Una vez dentro usando la libreria <curl/curl.h> recibe el recurso indicado.

### Estress Test

#### worker()

Esta función recibe la ip y el puerto para realizar la ejecución de los clientes para el estress test en terminal.

#### crearHilos()

Se encarga de crear la cantidad especificada de hilos que van a ejecutar los clientes del servidor.

##CGI Injector()

### injectarCodigo()

Función que no recibe parametros, se encarga totalmente de hacer fallar los servidores injectando codigo invalido.



## Instrucciones para ejecutar el programa

Siguiendo las instrucciones del enunciado, las instrucciones para ejecutar nuestra tarea son:

- Prethread Server: prethread-webserver -n <cantidad-hilos> -w <path-www-root> -p <port>
  
- Preforked Server: preforked-webserver -n <cantidad-hilos> -w <path-www-root> -p <port>
  
- Cliente http: httpclient -u <url-de-recurso-a-obtener>

- Cliente para el ataque: stress -n <cantidad-hilos> httpclient <parametros del cliente> 
  
- Injector de código: CGI_Injector

## Actividades realizadas por estudiante

#### Carlos Mora M

|                                  Actividad                                  |    Fecha   | Tiempo     |
|:---------------------------------------------------------------------------:|:----------:|------------|
| Se inicio la investigación sobre el trabajo a realizar                      | 23/10/2020 | 1.5 horas  |
| Se realizo lectura sobre manejo de procesos en C                            | 24/10/2020 | 2 horas    |
| Se realizo lectura e investigación sobre la implementación de procesos en C | 26/10/2020 | 3 horas    |
| Se realizaron pruebas de manejo de puertos en C                             | 27/10/2020 | 3.5 horas  |
| Se realizo la primer implementación de manejo de procesos en C              | 29/10/2020 | 2.5 horas  |
| Se hizo la primer implementación de manejo de puertos en C                  | 29/10/2020 | 2.5 horas  |
| Se realizó más investigación sobre la implementación de servidores en C     | 30/10/2020 | 3 horas    |
| Se creo el primer prototipo de servidor                                     | 03/11/2020 | 5 horas    |
| Se creo un versión más pulida del servidor                                  | 04/11/2020 | 2 horas    |
| Se investigo sobre el estrés test y el cliente                              | 04/11/2020 | 3 horas    |
| Se implemento el cliente y el estressTest                                   | 05/11/2020 | 3 horas    |
| Se realizaron las pruebas de funcionamiento                                 | 05/11/2020 | 30 minutos |
| Se realizo la documentación escrita de la tarea                             | 05/11/2020 | 3 horas    |

Horas Totales: 34 horas.

#### Kevin Segura R

|                                Actividad                                |    Fecha   | Tiempo     |
|:-----------------------------------------------------------------------:|:----------:|------------|
| Se inicio la investigación sobre la tarea                               | 22/10/2020 | 1.5 horas  |
| Se realizo investigación sobre manejo de hilos en C                     | 24/10/2020 | 2 horas    |
| Se realizo investigación sobre la implementación de hilos en C          | 24/10/2020 | 2 horas    |
| Se realizaron pruebas de manejo de puertos en C                         | 26/10/2020 | 1.5 horas  |
| Se realizo la primer prueba de manejo de hilos en C                     | 28/10/2020 | 2.5 horas  |
| Se hizo la primer implementación de manejo de hilos en C                | 28/10/2020 | 2.5 horas  |
| Se realizó más investigación sobre la implementación de servidores en C | 31/10/2020 | 3 horas    |
| Se creo el primer prototipo de servidor                                 | 03/11/2020 | 5 horas    |
| Se creo un versión más pulida del servidor                              | 04/11/2020 | 2 horas    |
| Se investigo sobre los CGI y protocolo http                             | 04/11/2020 | 3 horas    |
| Se implemento el primer prototipo de http                               | 05/11/2020 | 4 horas    |
| Se realizaron las pruebas de funcionamiento                             | 05/11/2020 | 30 minutos |
| Se hicieron pruebas y mejoras de funcionamiento de CGI                  | 05/11/2020 | 3 horas    |
| Se trabajo en la documentación de la tarea                              | 05/11/2020 | 2 horas    |

Horas Totales: 34 y media horas.

## Autoevaluación

#### Carlos Mora M

WebServer: 40 % /20
- Implementación del Pre-thread
- Implementación del Pre-forked
- Servir archivos grandes correctamente
- Desplegar una página web completa desde un navegador
- Implementación del un CGI

Implementación de Protocolos: 10 %/0

http-Client: 5 %/5

http-Client en C: 5 %/5

Stress-Client: 10 %/10

CGI Injector (Exploit): 10 %/7.5

Documentación utilizando MD: 20 %/20


#### Kevin Segura R

WebServer: 40 %/25
- Implementación del Pre-thread
- Implementación del Pre-forked
- Servir archivos grandes correctamente
- Desplegar una página web completa desde un navegador
- Implementación del un CGI

Implementación de Protocolos: 10 % /0

http-Client: 5 %/5

http-Client en C: 5 %/5

Stress-Client: 10 %/10

CGI Injector (Exploit): 10 %/7.5

Documentación utilizando MD: 20 %/20

## Estado Final del Proyecto

Se logró realizar los servidores y su funcionamiento de hilos y procesos sin embargo no se pudo implementar la parte de los CGI completamente, se logró la conexión con el server desde un navegador pero no se logró implementar los métodos de http ni los protocolos solicitados.

En los clientes se logró descargar recursos mediante curl y pycurl sin embargo no se logró hacerlo mediante nuestro servidor, se logró implementar un inyector muy simple donde solo se solicita un recurso que no existe, además se logró crear el estrés test donde se prueba el servidor y su capacidad de atender conexiones.  

## Git Comits

Commits on Nov 6, 2020
Cambios finales del cogido y estado final de la tarea

@Kedres
Kedres committed in 26 seconds
 
actualización de la docu

@carlosmora179
carlosmora179 committed 3 minutes ago
  
Commits on Nov 5, 2020
Cliente en python

@carlosmora179
carlosmora179 committed 17 minutes ago
 
Update documentacion.md

@Kedres
Kedres committed 40 minutes ago
  
Se agregaron las fuentes bibliograficas

@carlosmora179
carlosmora179 committed 4 hours ago
  
Creación de primer versión de la documentación del proyecto.

@carlosmora179
carlosmora179 committed 4 hours ago
  
servidor pre forked terminado cliente y el estres test listo

@carlosmora179
carlosmora179 committed 22 hours ago
 
Commits on Nov 4, 2020
Create documentacion.md

@Kedres
Kedres committed yesterday
  
archivos de Ancillary

@Kedres
Kedres committed yesterday
 
Servidor con el metodo prethread operativo

@Kedres
Kedres committed yesterday
 
Commits on Nov 3, 2020
Implementacion en etapas iniciales del servidor de procesos

@carlosmora179
carlosmora179 committed 3 days ago
 
Implementacion en etapas iniciales del servidor de hilos

@Kedres
Kedres committed 3 days ago
 
Commits on Oct 21, 2020
Update README.md

@carlosmora179
carlosmora179 committed 15 days ago
  
Initial commit

@Kedres
Kedres committed 15 days ago
  



## Lecciones Aprendidas

#### Carlos Mora M

Durante esta tarea se aprendió mucho sobre el manejo de los procesos independientemente, además de entender a fondo su funcionamiento y cómo estos requieren una memoria compartida para su funcionamiento, aprendí a crear segmentos de memoria y utilizarlos como una tabla de índices para cada proceso, consiguiendo mantenerlos abiertos y utilizarlos a conveniencia.

También fue una tarea que me enseñó mucho sobre los distintos protocolos de manejo de archivos y cómo estos son utilizados, también aprendí a correr programas de C desde python mediante una terminal y mantener estos en hilos individuales de ejecución.

Me pareció una tarea muy enriquecedora académicamente, pero pesada por el tiempo que requiere y el nivel de investigación  que hay que realizar para poder entender y trabajar con hilos y procesos, por momentos fue frustrante ya que C incrementa en gran cantidad la dificultad del trabajo.


#### Kevin Segura R

Se aprendio mucho sobre el manejo de hilos, utilizando de manera intenligente la funcionalidad que dan los phtreads, especialmente con sus modos _cond_... y _mutex_... Además, se repaso C y hasta se llegaron a aprender muchas funcionalidades que este lenguaje brinda, notando aún más la importancia y flexibilidad que da el poder manejar memoria.

Se aprendio mucho del manejo y funcionamiento de HTTP, más que en mi caso no he tenido la oportunidad de trabajar a fondo con él antes. Aunque no se logro implementar completamente como para ver su funcionamiento en nuestra tarea, con la teoria aprendida y las pruebas (aunque no del todo satisfactorias) dieron una muy valiosa experiencia para futuros trabajos que se realicen. 

## Bibliografía

<pthread.h>. Retrieved 5 November 2020, from https://pubs.opengroup.org/onlinepubs/007908799/xsh/pthread.h.html

Campos, O. (2011). Multiprocesamiento en Python: Threads a fondo, introducción. Retrieved 5 November 2020, from https://www.genbeta.com/desarrollo/multiprocesamiento-en-python-threads-a-fondo-introduccion

Doherty, J. (2014). What exactly is a pre-fork web server model?. Retrieved 5 November 2020, from https://stackoverflow.com/questions/25834333/what-exactly-is-a-pre-fork-web-server-model

NA, G. (2020). Gisi NA. Retrieved 5 November 2020, from https://www.youtube.com/channel/UC4QlswVP3DPsOI_Ub2q4m3A/videos

Ortiz, S. (2018). Como funciona la función fork(). Retrieved 5 November 2020, from https://es.stackoverflow.com/questions/179414/como-funciona-la-funci%C3%B3n-fork

Programacion en Castellano, S. C�mo ejecutar comandos Unix en tus programas de Python. Retrieved 5 November 2020, from https://programacion.net/articulo/como_ejecutar_comandos_unix_en_tus_programas_de_python_1678

Szabo, G. (2015). Set up CGI with Apache on Ubuntu Linux. Retrieved 5 November 2020, from https://code-maven.com/set-up-cgi-with-apache

What is a pre-fork worker model for a server? : learnprogramming. (2014). Retrieved 5 November 2020, from https://www.reddit.com/r/learnprogramming/comments/25vdm8/what_is_a_prefork_worker_model_for_a_server/

Hypertext Transfer Protocol -- HTTP/1.1. (s.f). Retrieved 5 November 2020, from https://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html#sec6

