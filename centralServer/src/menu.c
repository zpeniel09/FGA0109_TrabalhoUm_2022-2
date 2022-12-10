#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "menu.h"

Aparelhos aparelhos;
Sensores sensores;

void atualizaDispositivo(int dispNum, int novoStatus, int serv){
  unsigned short int porta = serv ? 10239 : 10231; // verifica se é servidor central ou distribuido
  enviaDistribuido(dispNum, novoStatus, porta);
}

char * verificaOnOff(int estadoSensorAparelho) {
  if(estadoSensorAparelho == 1){ return "ON"; }
  else { return "OFF"; }
}

void mostraMenu() {
  system("clear");

  printf(" | =============== STATUS DAS ENTRADAS ============== | ================ STATUS DAS SAIDAS =============== |\n\n");

  printf(" | ===============================================  SALA  ================================================ |\n");
  printf(" | ---      Sensor de presenca: %s                    |      0 -  Lampada 01: %s                       --- |\n", verificaOnOff(sensores.presenca), verificaOnOff(aparelhos.lampada01));
  printf(" | ---      Sensor de fumaca: %s                      |      1 -  Lampada 02: %s                       --- |\n", verificaOnOff(sensores.fumaca), verificaOnOff(aparelhos.lampada02));
  printf(" | ---      Sensor janela: %s                         |      2 -  Projetor Multimidia: %s              --- |\n", verificaOnOff(sensores.janela), verificaOnOff(aparelhos.projetor));
  printf(" | ---      Sensor porta de entrada: %s               |      3 -  Ar-condicionado: %s                  --- |\n", verificaOnOff(sensores.porta), verificaOnOff(aparelhos.arCondicionado));
  printf(" | ---      Sensor de temperatura e umidade:          |      4 -  Alarme: %s                           --- |\n", verificaOnOff(aparelhos.alarme));
  printf(" | ---      Sensor contagem de pessoas entrando:      |      5 -  Para ligar todos os aparelhos.       --- |\n");
  printf(" | ---      Sensor contagem de pessoas saindo:        |      6 -  Para desligar todos os aparelhos.    --- |\n\n");

  printf(" | ============================================== COMANDOS =============================================== |\n");
  printf(" |                                  Digite 'CTRL+Z' para dar algum comando                                 |\n");
  printf(" | ======================================================================================================= |\n\n");
}

void menuAtivaDesativa() {
  system("clear");

  printf(" | ============================================== COMANDOS =============================================== |\n");
  printf(" |                             Digite o código para ligar/desligar um aparelho                             |\n");
  printf(" | ======================================================================================================= |\n\n");

  __fpurge(stdin);
  char comando = getchar();

  if(comando == '0') {
    printf("===============================================\n");
    printf("| COMANDO 0 - Liga/desliga lampada 1 - Sala 1 |\n");
    printf("===============================================\n");
    printf("\n");
    aparelhos.lampada01 = !aparelhos.lampada01;
    atualizaDispositivo(0,aparelhos.lampada01,0);
  } 
  else if(comando == '1') {
    printf("===============================================\n");
    printf("| COMANDO 1 - Liga/desliga lampada 2 - Sala 1 |\n");
    printf("===============================================\n");
    printf("\n");
    aparelhos.lampada02 = !aparelhos.lampada02;
    atualizaDispositivo(1,aparelhos.lampada02,0);
  }
  else if(comando == '2') {
    printf("==============================================\n");
    printf("| COMANDO 2 - Liga/desliga projetor - Sala 1 |\n");
    printf("==============================================\n");
    printf("\n");
    aparelhos.projetor = !aparelhos.projetor;
    atualizaDispositivo(2,aparelhos.projetor,0);
  }
  else if(comando == '3') {
    printf("=====================================================\n");
    printf("| COMANDO 3 - Liga/desliga ar-condicionado - Sala 1 |\n");
    printf("=====================================================\n");
    printf("\n");
    aparelhos.arCondicionado = !aparelhos.arCondicionado;
    atualizaDispositivo(3,aparelhos.arCondicionado,0);
  }
  else if(comando == '4') {
    printf("============================================\n");
    printf("| COMANDO 4 - Liga/desliga alarme - Sala 1 |\n");
    printf("============================================\n");
    printf("\n");
    aparelhos.alarme = !aparelhos.alarme;
    atualizaDispositivo(4,aparelhos.alarme,0);
  }
  else if(comando == '5') {
    printf("================================================\n");
    printf("| COMANDO 5 - Liga todos dispositivos - Sala 1 |\n");
    printf("================================================\n");
    printf("\n");
    aparelhos.lampada01 = 1;
    aparelhos.lampada02 = 1;
    aparelhos.projetor = 1;
    aparelhos.arCondicionado = 1;
    aparelhos.alarme = 1;
    atualizaDispositivo(0, aparelhos.lampada01, 0);
    atualizaDispositivo(1, aparelhos.lampada02, 0);
    atualizaDispositivo(2, aparelhos.projetor, 0);
    atualizaDispositivo(3, aparelhos.arCondicionado, 0);
    atualizaDispositivo(4, aparelhos.alarme, 0);
  }
  else if(comando == '6') {
    printf("===================================================\n");
    printf("| COMANDO 6 - Desliga todos dispositivos - Sala 1 |\n");
    printf("===================================================\n");
    printf("\n");
    aparelhos.lampada01 = 0;
    aparelhos.lampada02 = 0;
    aparelhos.projetor = 0;
    aparelhos.arCondicionado = 0;
    aparelhos.alarme = 0;
    atualizaDispositivo(0, aparelhos.lampada01, 0);
    atualizaDispositivo(1, aparelhos.lampada02, 0);
    atualizaDispositivo(2, aparelhos.projetor, 0);
    atualizaDispositivo(3, aparelhos.arCondicionado, 0);
    atualizaDispositivo(4, aparelhos.alarme, 0);
  }
  else if(comando == '9') { printf("COMANDO 9\n");}
  else {
    printf("===========================================================\n");
    printf("| Comando inválido\nAperte 'ENTER' para tentar novamente. |\n");
    printf("===========================================================\n");
    printf("\n");
  }
}

void trata_SIGTSTP(int signum) {menuAtivaDesativa();}

void* menuFunc() {
  signal(SIGTSTP, trata_SIGTSTP);
  while(1) {
    mostraMenu();
    sleep(3);
    __fpurge(stdin);
  }
}

void trataSensores(int comando) {
  switch (comando)
  {
    case 1:
      sensores.presenca = !sensores.presenca;
      break;
    case 2:
      sensores.fumaca = !sensores.fumaca;
      break;
    case 3:
      sensores.janela = !sensores.janela;
      break;
    case 4:
      sensores.porta = !sensores.porta;
      break;
    case 5:
      sensores.entradaPessoas = !sensores.entradaPessoas;
      break;
    case 6:
      sensores.saidaPessoas = !sensores.saidaPessoas;
      break;
    case 7:
      sensores.temperatura = !sensores.temperatura;
      break;
    default:
      break;
  }
}