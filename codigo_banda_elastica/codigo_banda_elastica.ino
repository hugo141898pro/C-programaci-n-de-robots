este es de mi brazo: 

#include <LiquidCrystal.h>

char reponseBluetooth = "Anyone"; 

const int trigPin = 9;
const int echoPin = 10;
const int ledPin = 11;
const int motorPin = 8;

int distance;


long duration = 0;

bool ledOn = false;
bool screenOn = false;
bool once = false;
bool newOperation = false;
bool motorOn = false;
bool isConectionBluetooth = false;


LiquidCrystal lcd(2,3,4,5,6,7);

void setup() {
  lcd.begin(16, 2);
  pinMode(motorPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
 
 
  ConexionBluetooth();
  Serial.print("Estado del motor: ");
  Serial.println(motorOn);
   Serial.println("Tu distancia: ");
    Serial.print(distance);
    Serial.println("cm");
    once = false;
    DispararOndaDeSonido();
    distance = CalcularDistancia();
  if(newOperation)
  {
    
   
 
    if(distance <= 5 && distance !=0){
      digitalWrite(ledPin, 1);
      Serial.println("Maquina detenida");
      // newOperation = false;
      digitalWrite(motorPin, 0);
      lcd.setCursor(0,0);
      lcd.print("Objeto detectado");
     
  
    }else
    {
      digitalWrite(ledPin, 0);
      MostrarResultado(distance);
      digitalWrite(motorPin, 1);
      lcd.setCursor(0,0);
      lcd.print("En curso...");
 
     
      
     
 
    }
  
  }
  else
  {
   
     
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Welcome!");
 
    
  }
}
void ConexionBluetooth(){
  Serial.print(Serial.available ()>0);
  if(Serial.available ()>0)
  {

    Serial.println("Se establecio la conexion");
     reponseBluetooth = Serial.read();
    if( reponseBluetooth == 'm')
    {
      Serial.print("Opercion iniciada");
      newOperation = true;
      digitalWrite(motorPin, 1);
    
    
      distance = 0;
    }
    if(reponseBluetooth == 'n')
    {
      Serial.print("Opercion terminada");
      newOperation = false;
      digitalWrite(motorPin, 0);
    

    }
  }
  else
  {
  
    Serial.print("La conexion no esta establecida");
  }

}



int CalcularDistancia()
{
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.println(distance);
  
  return distance;
}

void DispararOndaDeSonido()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

void MostrarResultado(int distance) 
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Distancia: ");
  lcd.setCursor(0,1);
  lcd.print(distance);
  lcd.print("cm");

}





void MotorAction()
{
  if(motorOn)
  {
    digitalWrite(motorPin, 1);
  }
  else
  {
    digitalWrite(motorPin, 0);
  }

}

