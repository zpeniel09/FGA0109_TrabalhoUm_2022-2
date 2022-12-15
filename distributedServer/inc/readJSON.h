#ifndef READJSON_H_
#define READJSON_H_

typedef struct config {
    int portaDistribuido;
    int portaCentral;
    char ipCentral[13];
    char ipDistribuido[13];
} JSONConfig;

JSONConfig leJSONConfig(const char* nomeArquivo);
int *getDispositivosEntrada();
int getQtdeDispositivosEntrada();
int getQtdeDispositivosSaida();
int *getDispositivosSaida();
char *getIpCentral();
int getPortaCentral();
char *getIpDistribuido();
int getPortaDistribuido();


#endif