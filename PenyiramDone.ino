#include <Wire.h>

unsigned long previousMillis = 0;
const long interval = 10800000;

const int buttonPin1 = 10;  
const int buttonPin2 = 11; 

int buttonState1 = HIGH;  
int buttonState2 = HIGH; 

float step = 200; 
float dpulley = 40;
float degperstep = 360;
float kllpulley = dpulley * (22 / 7);
float lpersatstep = (degperstep / 360) * kllpulley;

//POSISI X
float xa = 500;
float xb = 800;
float xc = 1100;
float xd = 1400;
float xe = 1700;
float xf = 300;

//POSISI Y
float ya = 700;
float yb = 300;
float yc = 400;
float yd = 500;
float ye = 200;

//POSISI Z 
float za = 800;

//===========================================
//==============[SUMBU X PERSTEP]===============
int stepxa = xa / lpersatstep;
int stepxb = xb / lpersatstep;
int stepxc = xc / lpersatstep;
int stepxd = xd / lpersatstep;
int stepxe = xe / lpersatstep;
int stepxf = xf / lpersatstep;

//==============[SUMBU Y PERSTEP]===============
int stepya = ya / lpersatstep;
int stepyb = yb / lpersatstep;
int stepyc = yc / lpersatstep;
int stepyd = yd / lpersatstep;
int stepye = ye / lpersatstep;

//==============[SUMBU Z PERSTEP]===============
int stepza = za / lpersatstep;


//==============[SUMBU X STEP]===============
int stepxaa = stepxa + 1;
int stepxba = stepxb + 1;
int stepxca = stepxc + 1;
int stepxda = stepxd + 1;
int stepxea = stepxe + 1;
int stepxfa = stepxe + 1;

//==============[SUMBU Y STEP]===============
int stepyaa = stepya + 1;
int stepyba = stepyb + 1;
int stepyca = stepyc + 1;
int stepyda = stepyd + 1;
int stepyea = stepye + 1;

//==============[SUMBU Z STEP]===============
int stepzaa = stepza + 1;

int x = 0;

int moisture1;
int percentage1;
int map_low1 = 300; //Kondisi basah sensor 1
int map_high1 = 672; // Kondisi kering sensor 1

int val1 = 0; 
int val2 = 0; 
int val3 = 0; 
int val4 = 0; 
int val5 = 0; 

//SENSOR SOIL
int sensorSoil1 = A0;

//RELAY
int relay = 31; //Tool
int relay2 = 33; //Air
int relay3 = 35; //Biji

//MOTOR STEPPER PIN
const int stepPin1 = 2;
const int dirPin1 = 3;
const int stepPin2 = 4;
const int dirPin2 = 5;
const int stepPin3 = 6;
const int dirPin3 = 7;
const int stepPin4 = 8;
const int dirPin4 = 9;

void setup() 
{
  //RELAY
  pinMode(relay, OUTPUT);
  pinMode(relay2, OUTPUT);

  //MOTOR STEPPER
  pinMode(stepPin1, OUTPUT);
  pinMode(dirPin1, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(stepPin4, OUTPUT);
  pinMode(dirPin4, OUTPUT);

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

  val1 = 0;
  val2 = 0;
  val3 = 0;
  val4 = 0;
  val5 = 0;

  digitalWrite(relay, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
}

void loop() 
{
  int buttonReading1 = digitalRead(buttonPin1);  
  int buttonReading2 = digitalRead(buttonPin2);
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) 
  {
    if (buttonReading1 != buttonState1) 
    { 
      delay(10);  
      buttonReading1 = digitalRead(buttonPin1); 
      if (buttonReading1 != buttonState1) 
      { 
        buttonState1 = buttonReading1;  
        if (buttonState1 == LOW) 
        {  
          lubang();
        }
      }
    }
    
    if (buttonReading2 != buttonState2) 
    { 
      delay(10); 
      buttonReading2 = digitalRead(buttonPin2);  
      if (buttonReading2 != buttonState2) 
      {  
        buttonState2 = buttonReading2;  
        if (buttonState2 == LOW) 
        { 
          tanam();
        }
      }
    }

    previousMillis = currentMillis;
  }

  //=============[AMBIL TOOL]==============
  //SUMBU Y
  Serial.println("Ambil Tool");
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  Serial.println("Z Kebawah");
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  Serial.println("TOOL DI PASANG");

  digitalWrite(relay, HIGH);

  delay(5000);
  //SUMBU Z2
  
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  Serial.println("Z Keatas");

  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyea ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }

  //===============[POINT 1]===============

  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxaa; x > 0 ; x++) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxaa; x > 0 ; x--) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }

  if (percentage1 > 50) {
    delay(2000);
    val1 = 1;
  }
  delay(5000);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 2]===============
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxba; x > 0 ; x++) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxba; x > 0 ; x--) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }

  if (percentage1 > 50) {
    delay(2000);
    val2 = 1;
  }
  delay(5000);  
  
  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  
  //===============[POINT 3]===============
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxca; x > 0 ; x++) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxca; x > 0 ; x--) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }

  if (percentage1 > 50) {
    delay(2000);
    val3 = 1;
  }
  delay(5000);  

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 4]===============
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxda; x > 0 ; x++) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxda; x > 0 ; x--) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }

  if (percentage1 > 50) {
    delay(2000);
    val4 = 1;
  }
  delay(5000);  

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  
  //===============[POINT 5]===============
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxea; x > 0 ; x++) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxea; x > 0 ; x--) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }

  if (percentage1 > 50) {
    delay(2000);
    val5 = 1;
  }
  delay(5000);  

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //HOMING X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxea; x > 0 ; x--) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxea; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  //Y
  digitalWrite(dirPin1, HIGH);
  for (int x = stepyea; x > 0 ; x--) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  //Z
  ///////Z1
  Serial.println("Z Kebawah");
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  digitalWrite(relay, LOW);

  delay(5000);
  //SUMBU Z2
  
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  Serial.println("Z Keatas");

  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyea ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);


  if(val1 == 1)
  {
    digitalWrite(dirPin1, HIGH);
    for (int x = stepxaa; x > 0 ; x--) 
    {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(500);
    }
    digitalWrite(dirPin2, HIGH);
    for (int x = stepxaa; x > 0 ; x++) 
    {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(500);
    }

    //Air Keluar
    digitalWrite(relay2, HIGH);
    delay(5000);
    digitalWrite(relay2, LOW);

    //HOMEING KEMBALI
    digitalWrite(dirPin1, HIGH);
    for (int x = stepxaa; x > 0 ; x++) 
    {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(500);
    }
    digitalWrite(dirPin2, HIGH);
    for (int x = stepxaa; x > 0 ; x--) 
    {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(500);
    }
    val1 = 0;
  }

  if(val2 == 1)
  {
    digitalWrite(dirPin1, HIGH);
    for (int x = stepxba; x > 0 ; x--) 
    {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(500);
    }
    digitalWrite(dirPin2, HIGH);
    for (int x = stepxba; x > 0 ; x++) 
    {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(500);
    }

    //Air Keluar
    digitalWrite(relay2, HIGH);
    delay(5000);
    digitalWrite(relay2, LOW);

    //HOMEING KEMBALI
    digitalWrite(dirPin1, HIGH);
    for (int x = stepxba; x > 0 ; x++) 
    {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(500);
    }
    digitalWrite(dirPin2, HIGH);
    for (int x = stepxba; x > 0 ; x--) 
    {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(500);
    }
    val2 = 0;
  }

  if(val3 == 1)
  {
    digitalWrite(dirPin1, HIGH);
    for (int x = stepxca; x > 0 ; x--) 
    {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(500);
    }
    digitalWrite(dirPin2, HIGH);
    for (int x = stepxca; x > 0 ; x++) 
    {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(500);
    }

    //Air Keluar
    digitalWrite(relay2, HIGH);
    delay(5000);
    digitalWrite(relay2, LOW);

    //HOMEING KEMBALI
    digitalWrite(dirPin1, HIGH);
    for (int x = stepxca; x > 0 ; x++) 
    {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(500);
    }
    digitalWrite(dirPin2, HIGH);
    for (int x = stepxca; x > 0 ; x--) 
    {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(500);
    }
    val3 = 0;
  }

  if(val4 == 1)
  {
    digitalWrite(dirPin1, HIGH);
    for (int x = stepxda; x > 0 ; x--) 
    {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(500);
    }
    digitalWrite(dirPin2, HIGH);
    for (int x = stepxda; x > 0 ; x++) 
    {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(500);
    }

    //Air Keluar
    digitalWrite(relay2, HIGH);
    delay(5000);
    digitalWrite(relay2, LOW);

    //HOMEING KEMBALI
    digitalWrite(dirPin1, HIGH);
    for (int x = stepxda; x > 0 ; x++) 
    {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(500);
    }
    digitalWrite(dirPin2, HIGH);
    for (int x = stepxda; x > 0 ; x--) 
    {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(500);
    }
    val4 = 0;
  }
  
  if(val5 == 1)
  {
    digitalWrite(dirPin1, HIGH);
    for (int x = stepxea; x > 0 ; x--) 
    {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(500);
    }
    digitalWrite(dirPin2, HIGH);
    for (int x = stepxea; x > 0 ; x++) 
    {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(500);
    }

    //Air Keluar
    digitalWrite(relay2, HIGH);
    delay(5000);
    digitalWrite(relay2, LOW);

    //HOMEING KEMBALI
    digitalWrite(dirPin1, HIGH);
    for (int x = stepxea; x > 0 ; x++) 
    {
      digitalWrite(stepPin1, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin1, LOW);
      delayMicroseconds(500);
    }
    digitalWrite(dirPin2, HIGH);
    for (int x = stepxea; x > 0 ; x--) 
    {
      digitalWrite(stepPin2, HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin2, LOW);
      delayMicroseconds(500);
    }
  }
  val5 = 0;
}

void tanam () 
{
  //=============[AMBIL TOOL]==============
  //SUMBU Y
  Serial.println("Ambil Tool");
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyda ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  Serial.println("Z Kebawah");
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  Serial.println("TOOL DI PASANG");

  digitalWrite(relay, HIGH);

  delay(5000);
  //SUMBU Z2
  
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  Serial.println("Z Keatas");

  //=============[AMBIL BIJI 1]==============
  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyea ; x++) 
  {
    Serial.print(x * lpersatstep);
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //AMBIL BIJI
  digitalWrite(relay3, HIGH);

  delay(5000);
  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 1]===============

  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxaa; x > 0 ; x++) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxaa; x > 0 ; x--) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //Tanam
  digitalWrite(relay3, LOW);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

//=============[AMBIL BIJI 2]==============
  //SUMBU X
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepxaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxaa; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //AMBIL BIJI
  digitalWrite(relay3, HIGH);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 2]===============
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxba; x > 0 ; x++) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxba; x > 0 ; x--) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //TANAM
  digitalWrite(relay3, LOW);
  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //=============[AMBIL BIJI 3]==============
  //SUMBU X
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepxba ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxba; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //AMBIL BIJI
  digitalWrite(relay3, HIGH);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 3]===============
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxca; x > 0 ; x++) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxca; x > 0 ; x--) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //AMBIL BIJI
  digitalWrite(relay3, LOW);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //=============[AMBIL BIJI 4]==============
  //SUMBU X
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepxca ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxca; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //AMBIL BIJI
  digitalWrite(relay3, HIGH);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 4]===============
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxda; x > 0 ; x++) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxda; x > 0 ; x--) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //TANAM
  digitalWrite(relay3, LOW);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //=============[AMBIL BIJI 5]==============
  //SUMBU X
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepxda ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxda; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //AMBIL BIJI
  digitalWrite(relay3, HIGH);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 5]===============
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxea; x > 0 ; x++) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxea; x > 0 ; x--) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //TANAM
  digitalWrite(relay3, LOW);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //=============[AMBIL BIJI 6]==============
  //SUMBU X
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepxea ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxea; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //AMBIL BIJI
  digitalWrite(relay3, HIGH);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 6]===============
  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyca ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //TANAM
  digitalWrite(relay3, LOW);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //=============[AMBIL BIJI 7]==============

  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyca ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }

  //SUMBU X
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepxda ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxda; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //AMBIL BIJI
  digitalWrite(relay3, HIGH);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 7]===============
  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyca ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxca; x > 0 ; x--) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxca; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //TANAM
  digitalWrite(relay3, LOW);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //=============[AMBIL BIJI 8]==============

  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyca ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }

  //SUMBU X
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepxca ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxca; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //AMBIL BIJI
  digitalWrite(relay3, HIGH);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 8]===============
  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyca ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxca; x > 0 ; x--) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxca; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //TANAM
  digitalWrite(relay3, LOW);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //=============[AMBIL BIJI 9]==============

  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyca ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }

  //SUMBU X
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepxba ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxba; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //AMBIL BIJI
  digitalWrite(relay3, HIGH);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 9]===============
  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyca ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxba; x > 0 ; x--) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxba; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //TANAM
  digitalWrite(relay3, LOW);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

//=============[AMBIL BIJI 10]==============

  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyca ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }

  //SUMBU X
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepxaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxaa; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //AMBIL BIJI
  digitalWrite(relay3, HIGH);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 10]===============
  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyca ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxaa; x > 0 ; x--) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxaa; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //TANAM
  digitalWrite(relay3, LOW);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[HOMEING BOR]===============
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxaa; x > 0 ; x--) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxaa; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }

  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyea ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  
  digitalWrite(relay, LOW);

  delay(5000);
  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyda ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
}

void lubang () 
{
  //=============[AMBIL TOOL]==============
  //SUMBU Y
  Serial.println("Ambil Tool");
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyda ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  Serial.println("Z Kebawah");
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  Serial.println("TOOL DI PASANG");

  digitalWrite(relay, HIGH);

  delay(5000);
  //SUMBU Z2
  
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  Serial.println("Z Keatas");

  //===============[POINT 1]===============

  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxaa; x > 0 ; x++) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxaa; x > 0 ; x--) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 2]===============
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxba; x > 0 ; x++) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxba; x > 0 ; x--) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  
  //===============[POINT 3]===============
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxca; x > 0 ; x++) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxca; x > 0 ; x--) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 4]===============
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxda; x > 0 ; x++) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxda; x > 0 ; x--) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 5]===============
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxea; x > 0 ; x++) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxea; x > 0 ; x--) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 6]===============
  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyca ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 7]===============
  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyca ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxca; x > 0 ; x--) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxca; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 8]===============
  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyca ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxca; x > 0 ; x--) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxca; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 9]===============
  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyca ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxba; x > 0 ; x--) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxba; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[POINT 10]===============
  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyca ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxaa; x > 0 ; x--) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxaa; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  //===============[HOMEING BOR]===============
  //SUMBU X
  digitalWrite(dirPin1, HIGH);
  for (int x = stepxaa; x > 0 ; x--) 
  {
    digitalWrite(stepPin1, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin1, LOW);
    delayMicroseconds(500);
  }
  digitalWrite(dirPin2, HIGH);
  for (int x = stepxaa; x > 0 ; x++) 
  {
    digitalWrite(stepPin2, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin2, LOW);
    delayMicroseconds(500);
  }

  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyea ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Z1
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x++) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);

  digitalWrite(relay, LOW);

  delay(5000);
  //SUMBU Z2
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepzaa ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
  //SUMBU Y
  digitalWrite(dirPin3, HIGH);
  for (int x = 0; x < stepyda ; x--) 
  {
    digitalWrite(stepPin3, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin3, LOW);
    delayMicroseconds(500);
  }
  delay(5000);
}

void baca() {
  moisture1 = analogRead(sensorSoil1);// aktivasi object sensor soil 1
  percentage1 = map(moisture1, map_low1, map_high1, 0, 100);// Persentase kekeringan sensor 1
}