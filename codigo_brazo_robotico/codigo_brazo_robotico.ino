#include <Servo.h>

Servo tenaza;
Servo brazo;
Servo pata;

int tring = 2;
int echo = 3;
int tiempo;
int distancia;
bool ejecutado = false; // Variable flag para indicar si ya se ejecutó la parte del código

void setup() {
  pinMode(tring, OUTPUT);
  pinMode(echo, INPUT);
  tenaza.attach(6);
  brazo.attach(5);
  pata.attach(4);
}

void loop() {
  digitalWrite(tring, HIGH);
  delay(500);
  digitalWrite(tring, LOW);
  tiempo = pulseIn(echo, HIGH);
  distancia = tiempo / 58; // Corrección de la fórmula
  delay(500);

  if (distancia <= 20) {
    // Girar la pata gradualmente hacia la posición 0
    for (int angulo = 90; angulo >= 0; angulo--) {
      pata.write(angulo);
      delay(10); // Pequeño retraso para suavizar el giro
    }
    delay(1000);

    brazo.write(55);
    delay(1000);
    tenaza.write(0);
    delay(1000);
    brazo.write(0);
    delay(1000);
    // Girar la pata gradualmente hacia la posición 90
    for (int angulo = 0; angulo <= 90; angulo++) {
      pata.write(angulo);
      delay(10); // Pequeño retraso para suavizar el giro
    }
    delay(1000);

    tenaza.write(90);
    delay(1000);
  }
  
  // Verificar si la distancia es mayor que 20 y si la parte del código ya se ha ejecutado
  if (distancia > 20 && !ejecutado) {
    pata.write(90);
    brazo.write(0);
    tenaza.write(90);
    ejecutado = true; // Cambiar el valor de la variable flag a true para indicar que ya se ejecutó
  }
}