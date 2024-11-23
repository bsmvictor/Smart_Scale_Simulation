
# IoT Gas Monitor com Blynk

Este projeto implementa um sistema de monitoramento do nível de gás de um botijão utilizando um ESP8266 e a plataforma Blynk. O sistema pode detectar vazamentos, simular altos consumos de gás, e controlar uma válvula para cortar a distribuição de gás de maneira automática.

## Funcionalidades

- Monitoramento do Nível de Gás: O nível do botijão de gás é monitorado e atualizado no painel do Blynk a cada 10 segundos.

- Simulação de Consumo: O sistema simula o consumo normal de gás, bem como um alto consumo quando ativado pelo usuário.

- Detecção de Vazamento: Caso seja detectada uma queda acentuada no nível de gás, um alerta visual é acionado e a válvula de gás é fechada automaticamente.

- Controle da Válvula: A válvula de gás pode ser controlada manualmente ou automaticamente em caso de vazamento.

- Alerta Visual: Um LED virtual no Blynk pisca 5 vezes para indicar um vazamento detectado.

## Hardware Utilizado

- ESP8266: Microcontrolador para conectar ao Wi-Fi e à plataforma Blynk.

## Biblioteca Necessária

- BlynkSimpleEsp8266.h: Biblioteca para integração do ESP8266 com o aplicativo Blynk.

- ESP8266WiFi.h: Biblioteca para conectar o ESP8266 à rede Wi-Fi.

## Como Funciona

1. Conexão ao Wi-Fi e ao Blynk: O ESP8266 se conecta à rede Wi-Fi e ao Blynk utilizando as credenciais fornecidas.

2. Monitoramento e Atualização: O nível de gás é atualizado no painel do Blynk a cada 10 segundos.

3. Detecção de Vazamento: Se houver um vazamento (queda rápida no nível de gás), a válvula é fechada automaticamente e um LED virtual é acionado para indicar o problema.

4. Controle Manual: A válvula de gás pode ser aberta ou fechada manualmente pelo aplicativo Blynk.

## Instruções de Instalação

1. Hardware:

    - Conecte o ESP8266 à placa de pesagem e à válvula (se aplicável).

2. Software:

    - Faça o download da IDE do Arduino.

    - Instale a biblioteca Blynk e ESP8266WiFi através do Gerenciador de Bibliotecas.

    - Configure as credenciais de Wi-Fi no código.

3. Blynk:

    - Crie um novo projeto no aplicativo Blynk.

    - Adicione widgets para visualizar o nível do gás (Gauge), controlar o vazamento (Switch), e visualizar alertas (LED).

    - Utilize os pinos virtuais V0, V1, V2, V3 e V4 conforme descrito no código.

## Pinos Virtuais do Blynk

- V0: Exibe o nível de gás.

- V1: Botão para ativar alto consumo de gás.

- V2: Switch para simular vazamento.

- V3: LED para indicar vazamento detectado.

- V4: Switch para controlar a válvula manualmente.

## Utilização do Projeto

1. Monitorar o Nível de Gás: Acompanhe no widget Gauge do Blynk o nível atual do botijão de gás.

2. Alto Consumo de Gás: Utilize o botão no Blynk para simular um cenário de alto consumo (pino V1).

3. Simular Vazamento: Ligue o switch no pino V2 para simular um vazamento e veja o sistema fechando a válvula automaticamente.

4. Controle Manual da Válvula: Utilize o switch no pino V4 para abrir ou fechar a válvula manualmente.
