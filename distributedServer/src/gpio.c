#include "gpio.h"
#include "communication.h"

int gpioToPin( int value ){

    int pinToGpioR2 [64] = { // RPi Version 2
      17, 18, 27, 22, 23, 24, 25, 4, 	
      2,  3,				                  
      8,  7,				                  
      10,  9, 11, 			            	
      14, 15,			                  	
      28, 29, 30, 31,			            
      5,  6, 13, 19, 26,		         	
      12, 16, 20, 21,			            
      0,  1,			                
    } ;


    int index = 0;

    while ( index < 64 && pinToGpioR2[index] != value ) ++index;

    return ( index == 64 ? -1 : index );
}

void ativaDesativaDispositivo(int codigoGPIO, int status) {
  printf("===============================\n");
  printf("| Alterando estado da gpio %d |\n", codigoGPIO);
  printf("===============================\n");
  printf("\n");

  int wiringPIpin = gpioToPin(codigoGPIO);
  pinMode(wiringPIpin, OUTPUT);
  digitalWrite(wiringPIpin, status);
}

void sensorPresenca(void) {
  char* message = "1";
  enviaCentral(message);
  printf("======================\n");
  printf("| Sensor de Presença |\n");
  printf("======================\n");
  printf("\n");
}

void sensorFumaca(void) {
  char* message = "2";
  enviaCentral(message);
  printf("====================\n");
  printf("| Sensor de Fumaça |\n");
  printf("====================\n");
  printf("\n");
}

void sensorJanela(void) {
  char* message = "3";
  enviaCentral(message);
  printf("====================\n");
  printf("| Sensor da Janela |\n");
  printf("====================\n");
  printf("\n");
}

void sensorPorta(void) {
  char* message = "4";
  enviaCentral(message);
  printf("===========================\n");
  printf("| Sensor porta de entrada |\n");
  printf("===========================\n");
  printf("\n");
}


void* handleGPIO() {
  wiringPiSetup();
  int *portasDispositivosEntrada =  getDispositivosEntrada();
  int qtdeDispositivosEntrada = getQtdeDispositivosEntrada();
  int gpioPort;
  int wiringPIpin;

  for(int i =0; i < qtdeDispositivosEntrada ; i++){
      gpioPort = portasDispositivosEntrada[i];
      wiringPIpin = gpioToPin(gpioPort);
      pinMode(wiringPIpin, OUTPUT);
      switch (gpioPort)
      {
        case 7:
         wiringPiISR(wiringPIpin, INT_EDGE_BOTH, sensorPresenca);
         break;
        case 1:
         wiringPiISR(wiringPIpin, INT_EDGE_BOTH, sensorFumaca);
         break;
        case 12:
         wiringPiISR(wiringPIpin, INT_EDGE_BOTH, sensorJanela);
         break;
        case 16:
         wiringPiISR(wiringPIpin, INT_EDGE_BOTH, sensorPorta);
         break;
        default:
         break;
      }
  }

  for(;;) {sleep(1);}
}

void desativaDispositivos() {
  int *portasDispositivosSaida =  getDispositivosSaida();
  int qtdeDispositivosSaida = getQtdeDispositivosSaida();
  int wiringPIpin;
  for (size_t i = 0; i < qtdeDispositivosSaida; i++)
  {
    wiringPIpin = gpioToPin(portasDispositivosSaida[i]);
    pinMode(wiringPIpin, OUTPUT);
    digitalWrite(wiringPIpin, LOW);
  }
}