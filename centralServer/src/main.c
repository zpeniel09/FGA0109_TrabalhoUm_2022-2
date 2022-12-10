#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "communication.h"
#include "menu.h"

pthread_t menu;
pthread_t recebe;

void encerraPrograma() {
    printf("\n");
    printf("=================\n");
    printf("| Encerrando... |\n");
    printf("=================\n");
    printf("\n");
    exit(0);
}

void trata_SIGINT(int signum) { encerraPrograma();}

int main(int argc, const char * argv[]) {
    signal(SIGINT, trata_SIGINT);

    pthread_create(&menu, NULL, menuFunc, NULL);
    pthread_create(&recebe, NULL, recebeDistribuido, NULL);
    
    pthread_join(recebe, NULL);
    pthread_join(menu, NULL);
    return 0;
}