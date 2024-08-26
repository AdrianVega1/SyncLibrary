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
llamados main.c, semaphore.h, barrera.c, barrera.h, etc. 
Una vez que ya esté dentro del folder y con la terminal abierta, 
el usuario debe ejecutar los siguientes comandos:

# Compilación
* Para compilar el programa:
gcc -o main main.c sync.h

