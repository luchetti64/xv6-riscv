Tarea 1 (2) Lucas Rodriguez.
Para esta tarea no tenia idea que hacer, asi que lei los primeros
tres capitulos del libro de xv6, donde (aunque entendi la mitad), pude
captar los conceptos mas importantes de la tarea, como que el kernel
contiene los procesos (en xv6 hay una carpeta explicita del kernel), 
las cuales se ejcutan mediante un system call (uno de los archivos que
hay en el xv6 que no sabia que hacia). Todo esto se ubica en la pagina 9


En la pagina 10 explican el concepto de PID, parent y child process,
fork y ademas en la 11 tienen una lista de todos los system calls que
tiene xv6, donde ademas se encuentra getpid() (muy similar a lo que se pide)
entonces fue una gran pista. Luego no entendi tanto (ni es relevante para
esta tarea) pero vi que citaban mucho la carpeta user, y descubri que 
ahi tambien hay informacion importante (a medida que leia el texto,
tenia el source code de xv6 abierto para poder saber de que hablaban)

el folder kernel y que hace las files dentro (te da breve descripcion)
donde finalmente vemos donde esta syscall.c, sysfile.c y sysproc.c.Con
este adquirido contexto, busque en google dos cosas: 1 process id donde
me aparecio un video en youtube (https://www.youtube.com/watch?v=PZrQ4eGm-hM&t=56s)
donde usaba la funcion getppid(), entonces busque en que libreria se 
encuentra ya que si ya esta hecha la funcion podia copiar y pegar
sin complicarme demas (esta en la libreria unistd.h), aunque
no lo pude encontrar de esa manera. Lo segundo que busque fue como
implementar un sistem call en xv6 en google, y hay una pagina que te 
explicaba perfectamente como hacerlo, entonces la segui (https://www.geeksforgeeks.org/xv6-operating-system-adding-a-new-system-call/)
Y finalmente encontre el getppid() hecho en esta pagina https://github.com/emranbm/xv6/blob/master/sysproc.c
(y era muy parecido a lo que sospechaba)

De manera resumida, hay 5 archivos que hay que modificar para poder hacer
llamadas al sistema. El folder syscall.h que basicamente define las 
llamadas que existen y que se pueden agregar. Luego modificamos syscall.c
archivo que se encarga de Dispatch system calls to handling function (copiado textual del libro)
basicamente usa un puntero para apuntar a la funcion y llamarla.
Ademas agregamos en el mismo archivo a function prototype.
Luego agregamos la system function en si la cual definimos como codigo
de C, y le pedimos que hacer. Luego modificamos el usys.pl el cual crea
un archivo en usys.S que permite acceder a la llamada a sistema.
Finalmente en user.h agregamos le funcion que el usuario en si
va a usar cuando necesite llamarla.

Que hice en el proyecto:
1.syscall.h: #define SYS_getppid() 22
2.syscall.c sys_getppid() sys_getyear
3. syscall.c tambien extern int sys_getyear(void)
4.Agregar el codigo para poder obtener el parent (return myproc()->parent->pid;
5.En usys.pl agregar entry("getppif") (al hacer esto crea lo necesario
para que se use en el riscv dentro del archivo user.S
6. En user.h agregar int getppid(void);


Para poderver si nos funciona el llamado, creamos el archivo yo soy
tu padre con nano en user, y hacemos una simple llamada al systema (o a la funcion
creada en este caso),la cual para ser ejecutada tenemos que finalmente
modificar el makefile, el cual en uprogs esta todos los programas que se compilan
y ejecutan como parte de los programas de usuario, donde agregamos nuestra
funcion yosoytupadre. Hicimos make clean, make qemu y deespues de arreglar
unos errores de ortografia, entramos al qemu y corrimos nuestro archivo
donde obuvimos un parent id y un child id.

Para poder entender como funciona esto, vi que getpid en syscall.c
llamaba a my proc. Me fui al archivo de proc y vi que apuntaba a mycpu el cual hacer referencia a cpuid el cual hacer referencia a 
riscv.h a r_tp() ahi ya me perdi porque nose que lenguaje usa (asembly?)
pero por nomenclatura me di cuenta que usando punteros basicamente
apuntaban a la ID que se necesitaba,y daban ese puntero a myproc
el cual luego se almacenaba en pid. 

Para hacer el getancesror me di cuenta que lo mas probable es que
tuviese que hacer algo asi (myproc->tatarabuelo-> abuelo-> padre-> hijo.)
Pense en hacerlo de manera recursiva o con un for, pero no se me ocurrio
como, por ende le pedi a chat gpt, y despues de arreglar un par de cosas
lo pude ejecutar.

Ambas funciones son llamadas en el archivo yosoytupadre.c para simplificar
las cosas :D.

Y ese fue mi largo camino con esta tarea. Se puede ver el codigo modificado
en la rama, e igual lo explique aca.
