#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

typedef struct {
  float temperatura;
  float umidade;
} DHT22;

#define SERVER_DISTRIBUTED_IP "164.41.98.16"
#define SERVER_CENTRAL_PORT 10239 // 10239
#define SERVER_DISTRIBUTED_PORT 10231 // 10231

void acionaDistribuido();
void *recebeDistribuido();
void leTempUmidade();
int enviaDistribuido(int item, int status, unsigned short int porta);

#endif 