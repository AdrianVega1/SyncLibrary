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
- [Barrera](#Barrera)
- [Read/Write-Lock](#read/write-lock)

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
* La función de waitSem() se utiliza cuando un hilo va a hacer uso de los recursos para 
su ejecución, lo que decrementa la cantidad de recursos restantes. Esto mediante la utilización
de la función mutex_lock proporcionada por la biblioteca pthreads. En caso de no haber
ningún recurso restante, el hilo se queda dentro de un ciclo while hasta que se libere 
un recurso. 
* Por otro lado, la función signalSem(), simplemente incrementa la cantidad de
recursos disponibles. Esto se realiza cuando ya el hilo terminó su ejecución.

Para la utilización de esta estructura es necesario primero llamar la función semaphore_init()
con la dirección de memoria del semáforo a utilizar y la cantidad de recursos disponibles. Luego,
simplemente se usa la función waitSem() cuando el hilo tenga que ejecutar y al final de la ejecución
se utiliza signalSem().

# Barrera

Esta estructura tiene una función principal la cual es barrier_wait().
* barrier_wait() es la función clave del funcionamiento de la barrera. Cuando un hilo llega a la barrera, llama a
barrier_wait(). Primero, la función realiza un mutex_lock para garantizar que solo un hilo acceda a la
barrera a la vez. Luego, incrementa el contador de hilos que han llegado. Si el contador alcanza el número
total de hilos esperados, la barrera se rompe y todos los hilos que estaban esperando son desbloqueados
mediante pthread_cond_broadcast, de lo contrario se mantienen bloqueados.

Para utilizar esta estructura, primero se debe llamar a la función barrier_init() con la dirección de memoria 
de la barrera y el número de hilos que deben esperar en la barrera. Luego, dentro de cada hilo, se llama a 
barrier_wait() para sincronizar los hilos. Todos los hilos llamarán a esta función y esperarán en la barrera 
hasta que todos hayan llegado, momento en el cual se desbloquean y continúan su ejecución. Finalmente, una vez 
que todos los hilos han terminado, se utiliza barrier_destroy() para limpiar los recursos utilizados por la barrera.

# Read/Write-Lock

Esta estructura está compuesta de 4 funciones principales: adquirir_lock_lectura, liberar_lock_lectura, 
adquirir_lock_escritura, y liberar_lock_escritura.
* La funcion adquirir_lock_lectura() permite que un hilo adquiera un bloqueo de lectura. El hilo entra en un bucle
donde primero adquiere el mutex para verificar si hay un escritor activo. Si no hay ningún escritor activo, el
contador de lectores se incrementa, permitiendo que el hilo lea el recurso compartido. Luego, se libera el mutex
y se sale del bucle. Si hay un escritor activo, el hilo libera el mutex y vuelve a intentar.
* La función liberar_lock_lectura() se ejecuta después de que un hilo ha terminado de leer el recurso. El contador
de lectores se decrementa bajo el mutex para asegurar la consistencia. Esto indica que un lector ha terminado su
lectura, permitiendo potencialmente a un escritor comenzar a escribir si ya no quedan lectores activos.
* La función adquirir_lock_escritura() permite que un hilo adquiera un bloqueo de escritura. Similar al bloqueo de
lectura, el hilo entra en un bucle donde adquiere el mutex para verificar si hay lectores activos o si ya hay un
escritor activo. Si no hay lectores ni escritores activos, el flag escritor_activo se establece en 1, permitiendo
que el hilo escriba en el recurso compartido. Luego, se libera el mutex y se sale del bucle.
* La función liberar_lock_escritura() se ejecuta después de que un hilo ha terminado de escribir. El flag
escritor_activo se restablece a 0, lo que indica que el recurso compartido está disponible para otros lectores
o escritores. Luego, se libera el mutex.

Para utilizar esta estructura, primero se debe llamar a la función mi_rwlock_init() con la dirección de memoria 
de la estructura mi_rwlock que se utilizará. Un hilo que desee leer debe llamar a adquirir_lock_lectura() antes 
de acceder al recurso y liberar_lock_lectura() después de haber terminado. De manera similar, un hilo que desee 
escribir debe llamar a adquirir_lock_escritura() antes de acceder al recurso y liberar_lock_escritura() después 
de haber terminado. Esta implementación permite que múltiples hilos lean simultáneamente, pero restringe la 
escritura a un solo hilo a la vez, asegurando que los datos permanezcan consistentes y libres de condiciones de 
carrera.

# Compilación
* Para compilar el programa:
gcc -o main main.c sync.h
* Para correr el programa:
./main

