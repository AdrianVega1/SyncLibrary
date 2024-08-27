# Autores, Curso y Sede
**Instituto Tecnológico de Costa Rica**
*Principios de Sistemas Operativos. Grupo 40*
Integrantes:
*    Sergio Chavarría Avilés- 2021077879 - Centro Académico de Alajuela
*    José Ignacio Sánchez Morales- 2022081784 - Centro Académico Local San José
*    Adrián Josué Vega Barrantes- 2022104007 - Centro académico Local San José

Profesor:
*    Rodolfo Mora Zamora 
    
## Tabla de contenidos
- [Descripción](#Descripción)
- [Compilación](#Compilación)
- [Semáforo](#Semáforo)

## Biblioteca Sync
# Descripción:
En el código de este proyecto se encuentra una biblioteca "sync" que contiene las siguientes estructuras de sincronización:
-Semáforo
-Barrera
-Read/Write Lock
Esta biblioteca está implementada en el lenguaje C y utiliza los threads y mutex de la biblioteca pthread.

Para correr el programa el usuario tiene que abrir una terminal en
el folder donde se encuentra el código. Para que estar seguro de que
el usuario está en el folder correcto, debería poder ver unos archivos
llamados main.c y sync.h. 
Una vez que ya esté dentro del folder y con la terminal abierta, 
el usuario debe ejecutar los comandos especificados en la sección de Compilación.

# Semáforo
Esta estructura se implementó mediante dos funciones principales, waitSem y signalSem.
* La función de waitSem se utiliza cuando un hilo va a hacer uso de los recursos para 
su ejecución, lo que decrementa la cantidad de recursos restantes. En caso de no haber
ningún recurso restante, el hilo se queda dentro de un ciclo while hasta que se libere 
un recurso. 
* Por otro lado, la función signalSem, simplemente incrementa la cantidad de
recursos disponibles. Esto se realiza cuando ya el hilo terminó su ejecución.
Para la utilización de esta estructura es necesario primero llamar la función semaphore_init()
con la dirección de memoria del semáforo a utilizar y la cantidad de recursos disponibles. Luego,
simplemente se usa la función waitSem() cuando el hilo tenga que ejecutar y al final de la ejecución
se utiliza signalSem().

# Compilación
* Para compilar el programa:
gcc -o main main.c sync.h
* Para correr el programa:
./main

