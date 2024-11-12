Como siempre lo primero que hice fue contextulizarme para la tarea mediante
libros o videos en youtube para saber lo que se pide. Leyendo el libro
de XV6, viendo la clase y buscando en youtube me familiarice con el concepto
de paging y porque lo queremos para la proteccion de memoria. La proteccion
de memoria tiene como proposito evitar que un proceso en un sistema operativo
acceda a llamada ocultada para cualquier ocupacion de memoria que no le ha sido asignada.


Para evitar esto, se utiliza la segmentacion conocida como paging la cual
(de forma muy resumida) divide el espacio de direcciones de memoria
en pequeñas piezas identicas llamadas paginas, las cuales mediante una
memoria virtual se consigue que cada pagina resida en cualquier ubicacion
dentro de la memoria fisica, y para mantener rastro de esta y asegurar que
la memoria virtual no apunta a algo distinto en la memoria fisica, se utiliza
una tabla de paginas, la cual se utiliza para este proyecto.

Los archivos que se tuvieron que modificar fueron los siguientes:
-Makefile: Para poder ejecutar el codigo C de prueba
User:
-User.h: Agregar las funciones como int y sus parametros (definir)
-Usys.pl: Para generar la funcion en si (tanto mprotect como munprotect)
-proteger.c: Donde ponemos el codigo de prueba
Kernel:
-Syscall.h: Definir las llamadas a sistema m_protect y mun-protect
-Syscall.c: Agregar las llamadas a sistema de m_protect y mun:_protect

Y finalmente vm.c. Este es el archivo mas importante y en el cual me voy a explayar mas,
ya que el resto de los pasos son rutinarios y ya fueron hechos anteriormente.

Vm quiere decir virtual memory, y aca es donde se maneja todo lo que tiene que ver con el manejo de memoria
virtual y paginacion de esta, y la tabla de paginas en si. Este archivo 
llama a memlayout.h, donde se encuentra la base (kernbase) denuestra memoria
y el phystop de esta (o el limite), y es la que maneja la memoria fisica.
el riscv.h donde estan las importantes variables del pgsize (el tamaño de la pagina)
y el pgshift (offset de la pagina), ademas de las PTE o page table entries
que permiten PTE_: R read, W write, U user, V si esta presente y X si se
puede ejecutar.Finalmente tenemos el vc.m, que incluye la creacion
del pagetable, walk que retorna la direccion virtual de nuestra pagina
que puede ser asi ubicada en el espacio fisico, y mmappages que crea
una page table entry para dicha direccion virtual, y mas funciones para manejar la memoria virtual

Dentro de este archivo agregamos el m protect, el cual inicia con un adress, el largo que vamos a proteger
(lo multiplica por el largo de la pagina por esto), tenemos el inciio y el fin
Luego recorre dicho inicio hasta el fin por pagina (PGSIZE) y con walk obtenemos
una memoria virtual de nuestro pte (almacenada en el puntero), vemos si el valor de esta existe con PTE_V (dije mas arriba lo que hacia)
,si no existe damos error, pero si existe desabilitamos el pte_w de lectura 
(que tambien fue explicada mas arriba). Para el mun protect hacemos exatamente lo mismo, pero ahora en vez de desactivarlo lo activamos.
Y asi funciona el codigo de esta tarea.

Dentro de las dificultades que tuve fue que se me echo a perder el qemu,
ya que no encontraba el lock (o algo por el estilo), y la verdad
entender que se queria hacer fue dificil, me gaste la mitad del tiempo
investigando respecto de las tablas, que hacen y que se queria hacer
con la tarea.

Algunos links utilizados:
https://es.wikipedia.org/wiki/Protecci%C3%B3n_de_memoria
https://man7.org/linux/man-pages/man2/mprotect.2.html
https://github.com/zarif98sjs/xv6-memory-management-walkthrough
+ clases y videos en youtube
