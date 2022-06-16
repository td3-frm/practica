## Técnicas Digitales III

### Trabajo Práctico 14 FreeRTOS : Introducción a FreeRTOS.

* 1 - Crear un programa usando FreeRTOS que cumpla con las siguientes consignas:
    - Ejecutar dos tareas, **Tarea1** y **Tarea2**, con los niveles de prioridad apropiados.
    - La **Tarea1** debe ejecutarse de manera continua, indicando a través del puerto serie el valor de la entrada **GPIO_0**.
    - La **Tarea2** debe ser periódica, con período de 1 segundo y debe cambiar el estado del led verde e indicarlo a través del puerto serie. Adicionalmente debe indicar los ticks del reloj de FreeRTOS para verificar el período solicitado.

* 2 - Crear un programa usando FreeRTOS que cumpla con las siguientes consignas:
    - Ejecutar la tarea **Tarea1**.
    - La **Tarea1** debe leer el valor de la entrada **GPIO_2** cada 500 ms, indicando su estado por puerto serie. En caso de estar activa, crear la **Tarea2**.
    - La **Tarea2** debe cambiar el estado del led amarillo, indicarlo por puerto serie y terminar.

* 3 - Crear un programa usando FreeRTOS que cumpla con las siguientes consignas:
    - Ejecutar dos tareas, **Tarea1** y **Tarea2**.
    - La **Tarea1**, de mayor prioridad, debe ejecutar una espera activa (busy-waiting) indicando a través del puerto serie el valor de las entradas **GPIO_0** a **GPIO_3** en formato binario (nibble).
    - Periódicamente debe aumentar la prioridad de la **Tarea2**, para que esta pueda ejecutarse.
    - La **Tarea2** debe cambiar el estado del led verde, indicarlo por puerto serie y disminuir su propia prioridad para detener su ejecución.

* 4 - Crear un programa usando FreeRTOS que cumpla con las siguientes consignas:
    - Ejecutar dos tareas, **Tarea1** y **Tarea2** de distinta prioridad y que sean implementadas con la misma función.
    - Ambas tareas deben indicar por puerto serie que están en ejecución y su prioridad, luego bloquearse por 500 ms.
    - En el tiempo ocioso (Idle) aprovechar para cambiar el estado del led azul cada 300 ms e indicarlo por puerto serie. (Implementar Idle Hook)
    - Justifique qué sucede con los cambios de estado del led en caso que la tarea **Tarea1** pase a ejecutarse de manera contínua.

* 5 - Crear un programa usando FreeRTOS que cumpla con las siguientes consignas:
    - Ejecutar las tareas **Tarea1**, **Tarea2** y **Tarea3** con los niveles de prioridad apropiados.
    - Las tareas **Tarea1** y **Tarea2** deben enviar por cola de mensaje a la **Tarea3** el tiempo en milisegundos que debe estar encendido el led amarillo e indicarlo por puerto serie.
    - La **Tarea3** debe leer esos tiempos de la cola a medida que llegan y controlar el led en cuestión. Siempre, el tiempo apagado del led es de 500 ms. También debe indicar por puerto serie sus acciones. 
    - Indique qué pasa en caso de que el timeout de la escritura en la cola de mensajes sea de 300 ms.

