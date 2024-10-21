Para iniciar esta tarea, como siempre revise toda la informacion disponible
a mano, leyendo (de manera rapida) el capitulo de locks y shceduling 
del lubro de XV6. Si bien no ayudaron tanto como en otras tareas, si 
sirvieron para saber donde se encuentra que funcion/sistemcall/mecanismo.
El default scheduler de xv6 es el round-robbing el cual utiliza quantum
de tiempo para asegurar lo maximo que puede estar un proceso antes de ser
interrumpido, si es interrumpido se guarda su proceso y se agrega a la cola

lo cual asegura justicia (prLa funcion scheduler ya existe en xv6 
dentro del archico proc.c, implementado con su respectivo codigo.

La idea del sistema de prioridades es si llega un proceso nuevo, se le
otorga la prioridad mas alta (numero mas bajo), y el resto se agrega 
"a la cola" al sumar 1. Si llegan mas procesos se sigue sumando 1, 
acumulando dicho contador, hasta llegar al 9, donde ya se le decide dar
maxima prioridad a dicho proceso porque no ha sido ejecutado por muchho 
tiempo, rompiendo con el principio de la justicia. Por ende nuevos procesos
entran de inmediato, y a medida que se completan los procesos se va
eligiendo los que vienen por la prioridad asignada en el boost.

Para implementar esto se implementaron las estructura del proceso en si
para que esta tenga un int para ver que nivel de prioridad tiene, y
el boost para ver que boost tiene (en el struct proc dentro de proc.h)
Luego inicializar el valor de priority y boost en el archivo de allocproc
(le estamos dando memoria a estas variables) y con esas variables, modificar el shceduler.
Antes nuestro scheduler simplemente cerraba con lock la seccion para que
no fuese interrumpido, hacia un switch entre procesos guardando el contexto
Y soltaba el lock. Ahora para implementar prioridad, al proceso que entra
le agregamos su prioridad, y agregamos condiciones para ver si este esta en
los limites dichos anteriormente. Luego mediante otro for vemos si el 
proceso es igual a 0 (maxima prioridad) o si la prioridad es menor seleccionado
libera el lock del proceso con mayir prioridad para cederlo al nuevo de 
menor prioridad. Luego hacemos el switch entre los dos e inciamos la ejecucion.

Haciendo asi un round robin con prioridad. Finalmente para ver la prioridad
creamos un programa donde se crean 20 hijos y se les asigna prioridad segun
como llegan. En este caso se ejecutan en orden de llegada, pero si fuesen 
procesos mas largos debido al time slice cambiarian.

ALgunas dificultades fueron la poca documentacion. Solamente habia 
un articulo que ayudaba del cual se basaban todos los videos de youtube
El articulo es excelente (https://medium.com/@harshalshree03/xv6-implementing-ps-nice-system-calls-and-priority-scheduling-b12fa10494e4)
y de hecho me di cuenta que hace lo mismo que se pide para la tarea
pero al revez, y entrega un resultado mas completo del que consegui,
pero no tuve mas tiempo para implementarlo. Dependi demasiado de chatgpt
debido a la poca documentacion existente, confiando en la logica
que utiliza para resolver el problema de prioridad y ajustando lo que
le pido si da algo sin sentido, no me gusta sentir que chat gpt me 
hizo todo el trabajo. Finalmente, no pude implementar un sistem call
que pudiese imprimirme la prioridad y boost actual de los procesos creados
siempre me tiraba error al invocar el proc, y no tuve mas tiempo para resolverlo

Y asi fue como desarrolle la tarea 2.
