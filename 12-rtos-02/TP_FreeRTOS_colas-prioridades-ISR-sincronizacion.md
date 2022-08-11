## Técnicas Digitales III

### Trabajo Práctico 15 FreeRTOS : cola de mensajes, manejo de prioridades, ISR y sincronización.

* 1 - Crear un programa usando FreeRTOS que cumpla con las siguientes consignas:
    - Ejecutar dos tareas, **Tarea1** y **Tarea2**, con los niveles de prioridad apropiados y un mecanismo de sincronización.
    - La **Tarea1** debe ejecutar de manera contínua un bucle de busy waiting de 1 segundo aprox, indicándo este estado a través del puerto serie.
    - La **Tarea2** debe estar serializada, bloqueada hasta que la **Tarea1** complete su loop, una vez que pase esto, debe cambiar el estado del led Azul
    - Justifique que herramienta de sincronización utilizó.

* 2 - Crear un programa usando FreeRTOS que cumpla con las siguientes consignas:
    - Poseer dos tareas, **Tarea1** y **Tarea2**, una cola de mansajes entre ellas y una rutina de atención de interrupción de timer RIT.
	- La **Tarea1** debe enviar elementos a la cola de mensajes cada  1500 ms.
	- La **Tarea2** debe esperar de la interrupción del timer RIT (que será de 3 segundo). Una vez que expira el timer, consumir un elemento, indicándolo por puerto serie el elemento consumido y cambiar el estado del led Amarillo.

* 3 - Crear un programa usando FreeRTOS que cumpla con las siguientes consignas:
	- Posea tres tareas, la **Tarea1**, **Tarea2** y **Tarea3**.
	- La **Tarea1**, debe tener la mayor prioridad, la **Tarea2** media prioridad y **Tarea3** baja prioridad.
	- La **Tarea1** y la **Tarea3** comparten el puerto serie, enviando un mensaje cada una periodicamente, cada 800 ms.
	- La **Tarea2** es una tarea periódica, que ejecuta de manera contínua un bucle de busy waiting de 	1 segundo aprox, luego cambia el led Rojo cada y genera un delay de 200 ms.
    - Plantee su solución para evitar inversión de prioridad.

* 4 - En la tarea ImprimeHora mostrada en la página 95 del libro Sistemas Empotrados en Tiempo Real, ¿se podría solucionar el arbitraje del acceso al puerto serie cortando las interrupciones mientras se llama a SeriePuts()? En caso afirmativo, ¿existe alguna ventaja en el uso de semáforos?

* 5 - Reescriba el código mostrado en la sección 4.5.6 (página 105) del libro Sistemas Empotrados en Tiempo Real usando el sistema operativo FreeRTOS. Use para todos los semáforos un timeout de 1000 ms. Describa la ejecución de ambas tareas suponiendo que inicialmente ambos semáforos están libres, que inicialmente se ejecuta la **Tarea1** y que se produce un cambio de contexto justo antes de que la **Tarea1** pida el semáforo B. Ilustre esta descripción mediante un diagrama similar al mostrado en la figura 4.4.

* 6 - En la sección 4.8 del libro Sistemas Empotrados en Tiempo Real, se discuten tres alternativas para realizar llamadas al sistema operativo desde las rutinas de atención a interrupción. Discuta las ventajas e inconvenientes de cada una de estas alternativas en cuanto a la latencia y la facilidad de programación.
