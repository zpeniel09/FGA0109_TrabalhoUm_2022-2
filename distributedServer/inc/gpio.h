#ifndef GPIO_H_
#define GPIO_H_

#include <wiringPi.h>
#include <stdio.h>    
#include <softPwm.h>
#include <unistd.h>
#include "readJSON.h"

void ativaDesativaDispositivo(int item, int status);
void desativaDispositivos();
void* handleGPIO(); 

#endif 