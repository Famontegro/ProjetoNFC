#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// Pinos do RFID-RC522
#define SS_PIN 10
#define RST_PIN 7

// Pinos dos LEDs
#define LED_VERDE 4
#define LED_VERMELHO 5

// Pino do buzzer
#define BUZZER 6

// Pino do botao para desligar o alarme nivel 3
#define BOTAO_ALARME 2

// Pino do servo motor
#define PINO_SERVO A1

// Posicoes do servo
#define SERVO_FECHADO 5
#define SERVO_ABERTO 100

// Inicializacao dos componentes
MFRC522 rfid(SS_PIN, RST_PIN);
Servo servoPorta;

// UIDs dos cartoes autorizados
byte cartoesAutorizados[][4] = {
  {0xA5, 0x16, 0x1C, 0x60},
  {0x05, 0x79, 0x87, 0x41},
  {0xF5, 0xAA, 0x76, 0x41}
};

const byte QUANTIDADE_CARTOES = 3;

// Contador de tentativas invalidas consecutivas
byte tentativasInvalidas = 0;

// Duracao do alarme em cada nivel
const unsigned int TEMPO_NIVEL_1 = 300;
const unsigned int TEMPO_NIVEL_2 = 800;

void setup() {
  Serial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Botao com resistor interno de pull-up
  pinMode(BOTAO_ALARME, INPUT_PULLUP);

  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(BUZZER, LOW);

  // Inicializa o servo na posicao fechada
  servoPorta.attach(PINO_SERVO);
  servoPorta.write(SERVO_FECHADO);

  Serial.println("Sistema RFID iniciado!");
  Serial.println("Aproxime um cartao.");
}

void loop() {
  // Verifica se existe um novo cartao
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Tenta ler o cartao
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("UID: ");

  // Exibe o UID lido
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) {
      Serial.print("0");
    }

    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }

  Serial.println();

  // Verifica se o cartao esta autorizado
  bool autorizado = false;

  for (byte c = 0; c < QUANTIDADE_CARTOES; c++) {

    bool igual = true;

    // Verifica se o UID possui 4 bytes
    if (rfid.uid.size != 4) {
      igual = false;
    } else {

      // Compara o UID com o cartao atual da lista
      for (byte i = 0; i < 4; i++) {

        if (rfid.uid.uidByte[i] != cartoesAutorizados[c][i]) {
          igual = false;
        }
      }
    }

    // Se encontrou um cartao correspondente
    if (igual) {
      autorizado = true;
      break;
    }
  }

  // Se o cartao for autorizado
  if (autorizado) {

    Serial.println("ACESSO LIBERADO!");

    // Zera a contagem de tentativas invalidas
    tentativasInvalidas = 0;

    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    noTone(BUZZER);

    // Abre a porta
    servoPorta.write(SERVO_ABERTO);

  } else {

    Serial.println("ACESSO NEGADO!");

    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, HIGH);

    // Mantem a porta fechada
    servoPorta.write(SERVO_FECHADO);

    // Aumenta o contador de tentativas invalidas
    if (tentativasInvalidas < 3) {
      tentativasInvalidas++;
    }

    // Alarme progressivo
    if (tentativasInvalidas == 1) {

      Serial.println("ALARME NIVEL 1");

      tone(BUZZER, 2000);
      delay(TEMPO_NIVEL_1);
      noTone(BUZZER);

    } else if (tentativasInvalidas == 2) {

      Serial.println("ALARME NIVEL 2");

      tone(BUZZER, 2000);
      delay(TEMPO_NIVEL_2);
      noTone(BUZZER);

    } else {

      Serial.println("ALARME NIVEL 3");
      Serial.println("Aperte o botao no D2 para interromper.");

      // Repete o alarme ate apertar o botao
      while (digitalRead(BOTAO_ALARME) == HIGH) {

        // Sinal sonoro
        tone(BUZZER, 2000);
        delay(500);

        noTone(BUZZER);
        delay(300);
      }

      // Interrompe o alarme ao apertar o botao
      noTone(BUZZER);

      Serial.println("ALARME INTERROMPIDO!");
    }
  }

  // Finaliza a comunicacao com o cartao
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  // Reinicializa o leitor RFID
  rfid.PCD_Init();
  delay(50);

  // Aguarda 3 segundos
  delay(3000);

  // Fecha a porta na posicao ajustada
  servoPorta.write(SERVO_FECHADO);

  // Apaga os LEDs
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_VERMELHO, LOW);

  Serial.println("Aproxime outro cartao.");
}