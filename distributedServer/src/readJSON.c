#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readJSON.h"
#include "cJSON.h"

JSONConfig config2;

int qtdeDispositivosEntrada;
int dispositivosEntrada[7];
int qtdeDispositivosSaida;
int dispositivosSaida[5];


JSONConfig leJSONConfig(const char* nomeArquivo) {
  const cJSON *item = NULL;
  const cJSON *outputs = NULL;
  const cJSON *inputs = NULL;
  const cJSON *nomeSala = NULL;

  char json_buffer[2000];
  FILE *arq = fopen(nomeArquivo,"r"); //abre o arquivo JSON para leitura
  fread(json_buffer, 2000, 1, arq);
	fclose(arq);

  cJSON *devices = cJSON_Parse(json_buffer);
  if (devices == NULL)
  {
      const char *error_ptr = cJSON_GetErrorPtr();
      if (error_ptr != NULL){fprintf(stderr, "Error before: %s\n", error_ptr);}
      return config2;
  }

  nomeSala = cJSON_GetObjectItemCaseSensitive(devices, "nome");
  printf("Analisando \"%s\"\n", nomeSala->valuestring);
  cJSON *ip_json = cJSON_GetObjectItemCaseSensitive(devices, "ip_servidor_central");
  strcpy(config2.ipCentral, ip_json->valuestring);

  cJSON *porta_json_central = cJSON_GetObjectItemCaseSensitive(devices, "porta_servidor_central");
  config2.portaCentral = porta_json_central->valueint;

  cJSON *porta_json_ip_distribuido = cJSON_GetObjectItemCaseSensitive(devices, "ip_servidor_distribuido");
  strcpy(config2.ipDistribuido, porta_json_ip_distribuido->valuestring);

  cJSON *porta_json_porta_distribuido = cJSON_GetObjectItemCaseSensitive(devices, "porta_servidor_distribuido");
  config2.portaDistribuido = porta_json_porta_distribuido->valueint;

  printf("IP: %s e Porta: %d\n", config2.ipCentral, config2.portaDistribuido);

  inputs = cJSON_GetObjectItemCaseSensitive(devices, "inputs");

  qtdeDispositivosEntrada = 0;
  cJSON_ArrayForEach(item, inputs){
    cJSON *tag = cJSON_GetObjectItemCaseSensitive(item, "tag");
    cJSON *gpio = cJSON_GetObjectItemCaseSensitive(item, "gpio");

    int len = (strlen(tag->valuestring) + 13);

    printIgual(len);
    printf("%s na gpio %d |\n", tag->valuestring, gpio->valueint);
    printIgual(len);
    printf("\n");

    dispositivosEntrada[qtdeDispositivosEntrada] = gpio->valueint;
    qtdeDispositivosEntrada += 1;

  }

  outputs = cJSON_GetObjectItemCaseSensitive(devices, "outputs");

  qtdeDispositivosSaida = 0;
  cJSON_ArrayForEach(item, outputs) {
    cJSON *tag = cJSON_GetObjectItemCaseSensitive(item, "tag");
    cJSON *gpio = cJSON_GetObjectItemCaseSensitive(item, "gpio");

    int len = (strlen(tag->valuestring) + 13);

    printIgual(len);
    printf("%s na gpio %d |\n", tag->valuestring, gpio->valueint);
    printIgual(len);
    printf("\n");

    dispositivosSaida[qtdeDispositivosSaida] = gpio->valueint;
    qtdeDispositivosSaida += 1;
  }

  return config2;
}

int *getDispositivosEntrada(){return dispositivosEntrada;}      //retorna o vetor de dispositivos de entrada
int getQtdeDispositivosEntrada(){return qtdeDispositivosEntrada;} //retorna a quantidade de dispositivos de entrada
int getQtdeDispositivosSaida(){return qtdeDispositivosSaida;}   //retorna a quantidade de dispositivos de saida
int *getDispositivosSaida(){return dispositivosSaida;}          //retorna o vetor de dispositivos de saida
char *getIpCentral(){return config2.ipCentral;}                 //retorna o ip do servidor central
int getPortaCentral(){return config2.portaCentral;}             //retorna a porta do servidor central
char *getIpDistribuido(){return config2.ipDistribuido;}         //retorna o ip do servidor distribuido
int getPortaDistribuido(){return config2.portaDistribuido;}     //retorna a porta do servidor distribuido

void printIgual (int tag) {
  for(int i = 0; i < tag; i++) {
    if(i != (tag-1)) { printf("=");}
    if(i == (tag-1)){
      printf("=");
      printf("\n");
    }
  }
}