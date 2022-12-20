# FGA0109_TrabalhoUm_2022-2
Este trabalho tem por objetivo a criação de um sistema distribuído de automação predial para monitoramento e acionamento de sensores e dispositivos de um prédio com múltiplas salas. 

Para ver a integrar desse trabalho basta acessar este [link](https://gitlab.com/fse_fga/trabalhos-2022_2/trabalho-1-2022-2).


Compilando os códigos dos servidores:

* Vá no diretorio do centralServer
* Digite o commando abaixo.
  ```
  make
  bin/bin
  ```

* Vá no diretório do distributedServer 
* Digite o commando abaixo.
  ```
  make
  bin/bin configuracao_sala_01.json
  ```
  ou 

  ```
  make

  bin/bin configuracao_sala_02.json
  ```