#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
	printf("Current id: %d, parent id: %d\n grandparent id: %d\n", getpid(), getppid(), getancestor(2));
	printf("\n");	
	printf("tatarabuelo: %d, su papa %d, y asi todo el rato", getancestor(3), getancestor(4));
	exit(0);
}


