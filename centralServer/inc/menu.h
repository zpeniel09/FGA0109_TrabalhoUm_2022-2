#ifndef MENU_H_
#define MENU_H_

typedef struct aparelhos {
    int lampada01;
    int lampada02;
    int projetor;
    int arCondicionado;
    int alarme;
} Aparelhos;

typedef struct sensores {
    int presenca;
    int fumaca;
    int janela;
    int porta;

    int entradaPessoas;
    int saidaPessoas;
    int temperatura;
} Sensores;

void* menuFunc();
void mostraMenu();
void atualizaDispositivo(int dispNum, int novoStatus, int serv);
void trataSensores(int comando);

#endif