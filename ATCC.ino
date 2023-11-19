/*
Board: DOIT ESP2 DEV Kit

  CONEXÃO ACCESS POINT PARA QUE ENTRE DADOS DA REDE WIFI E SENHA PELO CELULAR
  CONEXÃO WIFI
  FUNÇÃO LIGA/DESLIGA
  FUNÇÃO COUNTDOWN
  
*/
#include <WiFi.h>

const char* ssid_AP = "Tomada Inteligente";         //AP name

WiFiServer MeuServer(80);
WiFiClient ClienteRemoto;

//variavel para guardar HTTP request
String header;
//liga/desliga
#define BOTAO 32
//estado BOTÃO
int est_BTN = 0;
//estado anterior BOTÃO
int est_ant_BTN = 0;
//estado RELE
int est_RELE = 0;

//pino conectado ao RELE
#define RELE 37
//valor TENSÃO
#define tensao 31
//valor CORRENTE
#define corrente 30

//consumo WATTS
float consumo = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BOTAO, INPUT_PULLUP);
  pinMode(RELE, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  //iniciando Access Point
  Serial.print("Iniciando AP (Access Point)…");
  //definindo nome e senha (removendo a senha o AP fica aberto)
  WiFi.softAP(ssid_AP);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  MeuServer.begin();

  CheckForConnections();

  uint8_t ReceiveBuffer[30];
  while (ClienteRemoto.connected() && ClienteRemoto.available())
  {
    int Received = ClienteRemoto.read(ReceiveBuffer, sizeof(ReceiveBuffer));
    ClienteRemoto.write(ReceiveBuffer, Received);
  }
}

void CheckForConnections(){
  Serial.print("Aguardando conexão...  ");
  while (!ClienteRemoto.connected()){
    ClienteRemoto = MeuServer.available();
  }
  Serial.println("Conexão bem sucedida");
}

void loop(){
}