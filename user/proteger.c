
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    // Paso 1: Reserva una página de memoria
    char *addr = sbrk(4096);  // Reserva 4096 bytes (una página)
    if (addr == (char *)-1) {
        printf("Error reserving memory\n");
        exit(1);
    }

    printf("Page adress reserved: %p\n", addr);

    // Paso 2: Protege la página usando mprotect
    if (mprotect(addr, 1) == -1) {
        printf("Error: mprotect failed\n");
        exit(1);
    } else {
        printf("Page is read only now, PTE_W disabled\n");
    }


    //comentar esto para probar el programa no provoque una  falla
    // Paso 3: Intenta escribir en la página protegida (debería fallar)
    printf("Trying to write to a protected page\n");
    *addr = 'A';  // Esto debería provocar un fallo de protección de memoria

    // Si el programa llega aquí, la protección no funcionó como se esperaba
    printf("Error: It didn´t fail as expected\n");

    // Paso 4: Desproteger la página usando munprotect
    if (munprotect(addr, 1) == -1) {
        printf("Error: munprotect failed\n");
        exit(1);
    } else {
        printf("Page is back to having PTE_R and PTE_W\n");
    }

    // Paso 5: Intentar escribir en la página desprotegida (debería funcionar)
    printf("Trying to write in the unprotected page...\n");
    *addr = 'h';  // Esto debería ser exitoso si munprotect funcionó
    printf("Writing succesfull in address: %c\n", *addr);

    // Finalizacion el programa
    printf("Test completed\n");
    exit(0);
}
