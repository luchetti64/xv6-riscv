#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
  int i;

  for (i = 0; i < 20; i++) {
    int pid = fork();
    if (pid < 0) {
      printf("Error al crear proceso\n");
      exit(1);
    } else if (pid == 0) {
      // Proceso hijo
      printf("Ejecutando proceso (hijo) numero %d con PID: %d\n",i+1, getpid());      
      sleep(70);  // Pausa para simular ejecución
      exit(0);     // El proceso hijo termina
    } else {
      // Proceso padre continúa con el ciclo
      wait(0);     // Espera a que el hijo termine
    }
  }
  exit(0);  // Finaliza el proceso principal
}

