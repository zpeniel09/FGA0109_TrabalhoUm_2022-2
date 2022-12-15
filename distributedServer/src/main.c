#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

#include "readJSON.h"
#include "communication.h"
#include "gpio.h"

pthread_t communication;
pthread_t gpio;

JSONConfig config;

void encerraPrograma() {
    printf("=================\n");
    printf("| Encerrando... |\n");
    printf("=================\n");
    printf("\n");
    exit(0);
}

void inicializaPrograma(const char * filename) {

    if (wiringPiSetup() == -1) {
		printf("Failed to initialize wiringPi\n");
		exit(1);
    }
    config = leJSONConfig(filename);
    desativaDispositivos();
}

void trata_SIGINT(int signum) {encerraPrograma();}

int main(int argc, const char * argv[]) {
    signal(SIGINT, trata_SIGINT);

    if (argc >= 2){	inicializaPrograma(argv[1]);}
	else{
		printf("O arquivo de configuracao precisa ser passado como parametro\n");
		return -1;
	}
    int porta = getPortaDistribuido();

    pthread_create(&communication, NULL, recebeCentral, &porta);
    pthread_create(&gpio, NULL, handleGPIO, NULL);
    
    pthread_join(communication, NULL);
    pthread_join(gpio, NULL);
    return 0;
}