#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dht.h"
#include "gpio.h"
#include "readJSON.h"

void* recebeCentral(void *porta) {

  int this_port = *((int *) porta);

  struct sockaddr_in server, client;

	int serverid = socket(AF_INET, SOCK_STREAM, 0);

	memset(&server, '0', sizeof(server));

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(this_port);

	bind(serverid, (struct sockaddr*) &server, sizeof(server));

	if (listen(serverid, 10) == -1) {
    printf("========\n");
		printf("| ERRO |");
    printf("========\n");
    printf("\n");
		exit(1);
	}

  while(1) {
	  unsigned int len = sizeof(client);
	  int clientid = accept(serverid, (struct sockaddr*) &client, &len);
    
    char buffer[16];
	  int size = recv(clientid, buffer, 16, 0);

    if (size < 0) {
      printf("========\n");
      printf("| ERRO |");
      printf("========\n");
      printf("\n");
      exit(1);
    }

    buffer[15] = '\0';
		
    int command;
    sscanf(buffer, "%d", &command);

    // 1 means turning on a lamp or ar condicioner
    if (command == 1) {
      int item;
      int status;
      int codigoGPIO;

      sscanf(buffer, "%d %d %d", &command, &item, &status);

      codigoGPIO = codigoDispoParaGPIO(item);

      printf("====================================================\n");
      printf("| Requisicao para alterar estado do dispositivo %d |\n", codigoGPIO);
      printf("====================================================\n");
      printf("\n");
      ativaDesativaDispositivo(codigoGPIO, status);
      char buf[2];
      snprintf(buf, 2, "%d", 1);
      int size = strlen(buf);
      if (send(clientid, buf, size, 0) != size) {
        printf("========================\n");
        printf("| Erro: falha no envio |\n");
        printf("========================\n");
        printf("\n");
      }
    }

    // 2 means temperature and humidity reading
    if (command == 2) {
      printf("=============================================\n");
      printf("| Coletando dados de temperatura e humidade |\n");
      printf("=============================================\n");
      printf("\n");
      char buf[16];
      snprintf(buf, 16, "%d %4.2f %4.2f", 2, leTemperatura(),leUmidade());
      int size = strlen(buf);
      printf("====================================================================\n");
      printf("| Enviando dados de temperatura e humidade para o servidor central |\n");
      printf("====================================================================\n");
      printf("\n");
      if (send(clientid, buf, size, 0) != size) {
        printf("========================\n");
        printf("| Erro: falha no envio |\n");
        printf("========================\n");
        printf("\n");
      }
    }
		close(clientid);
  }

	close(serverid);
}


void enviaCentral(char *message) {
  char *ipCentral;
  int portaCentral;
  char *ipDistribuido;
  int portaDistribuido;
  
	struct sockaddr_in client;

  ipCentral = getIpCentral();
  portaCentral = getPortaCentral();
  ipDistribuido = getIpDistribuido();
  portaDistribuido = getPortaDistribuido();

  int socketid = socket(AF_INET, SOCK_STREAM, 0);
  if (socketid == -1) {
    printf("Falha ao criar socket\n");
    exit(1);
  }

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr(ipCentral);
  client.sin_port = htons(portaCentral);

  while(connect(socketid, (struct sockaddr*) &client, sizeof(client)) < 0){
    printf("==============================================================\n");
    printf("| Erro ao tentar conectar com o servidor, tentando novamente |\n");
    printf("==============================================================\n");
    printf("\n");
    sleep(1);
  }

  int size = strlen(message);
  if (send(socketid, message, size, 0) != size) {
    printf("========================\n");
    printf("| Erro: falha no envio |\n");
    printf("========================\n");
    printf("\n");
    exit(1);
  }

  char buf[7];
  snprintf(buf, 7, "%d %s %d", 1, ipDistribuido, portaDistribuido);
  int size = strlen(buf);
  if (send(socketid, buf, size, 0) != size) {
    exit(0);
  }

  close(socketid);
}

int codigoDispoParaGPIO(int numDispositivo){
  int codigoGPIO;
  int * dispositivosSaida;
  dispositivosSaida = getDispositivosSaida();
  codigoGPIO = dispositivosSaida[numDispositivo];
  return codigoGPIO;
}