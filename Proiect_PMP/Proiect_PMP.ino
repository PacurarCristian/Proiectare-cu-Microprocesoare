#include <Servo.h>
// Pinii motor 1
#define mpin00 5
#define mpin01 6
// Pinii motor 2
#define mpin10 3
#define mpin11 11
Servo srv;
int speed = 0; int dir = 0;

const int trigPin = 2;
const int echoPin = 10;
long duration;
int distance;
const int led1 = 11;
const int led2 = 12;
const int led3 = 13;
const int buzzerPin = 7 ;
const int servoPin = 8;

//notes
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;
int counter = 0;

int autonomusMode = 0;


void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  // configurarea pinilor motor ca iesire, initial valoare 0
  digitalWrite(mpin00, 0);
  digitalWrite(mpin01, 0);
  digitalWrite(mpin10, 0);
  digitalWrite(mpin11, 0);
  pinMode (mpin00, OUTPUT);
  pinMode (mpin01, OUTPUT);
  pinMode (mpin10, OUTPUT);
  pinMode (mpin11, OUTPUT);
  // pin LED
  pinMode(13, OUTPUT);
  //distanta
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.begin(9600); // Interfata Serial 0, pentru PC
}
// Funcție pentru controlul unui motor
// Intrare: pinii m1 și m2, direcția și viteza
void StartMotor (int m1, int m2, int forward, int speed)
{

  if (speed == 0) // oprire
  {
    digitalWrite(m1, 0);
    digitalWrite(m2, 0);
  }
  else
  {
    if (forward)
    {
      digitalWrite(m2, 0);
      analogWrite(m1, speed); // folosire PWM
    }
    else
    {
      digitalWrite(m1, 0);
      analogWrite(m2, speed);
    }
  }
}
// Funcție de siguranță
// Execută oprire motoare, urmată de delay
void delayStopped(int ms)
{
  StartMotor (mpin00, mpin01, 0, 0);
  StartMotor (mpin10, mpin11, 0, 0);
  delay(ms);
}
// Utilizare servo
// Poziționare în trei unghiuri
// La final, rămâne în mijloc (90 grade)
void playWithServo(int pin)
{
  srv.attach(pin);
  srv.write(0);
  delay(1000);
  srv.write(180);
  delay(1000);
  srv.write(90);
  delay(1000);
  srv.detach();
}

void writeServo(int pin, int angle) {
  srv.attach(pin);
  srv.write(angle);
}

void lightUpLeds(int distance) {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  if (distance > 70)
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);

  }
  else if (distance > 50) {
    digitalWrite(led1, HIGH);
  }
  else if (distance > 35) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }
  else if (distance > 20) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }
}

void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(buzzerPin, note, duration);

  //Play different LED depending on value of 'counter'
  if (counter % 2 == 0)
  {
    digitalWrite(led2, HIGH);
    writeServo(servoPin, 60);
    //StartMotor (mpin00, mpin01, 1, 100);
    //StartMotor (mpin10, mpin11, 0, 100);
    delay(duration);
    digitalWrite(led2, LOW);
  } else
  {
    digitalWrite(led3, HIGH);
    writeServo(servoPin, 120);
    //StartMotor (mpin00, mpin01, 0, 100);
    //StartMotor (mpin10, mpin11, 1, 100);
    delay(duration);
    digitalWrite(led3, LOW);
  }

  //Stop tone on buzzerPin
  noTone(buzzerPin);

  delay(50);

  //Increment counter
  counter++;
}

void firstSection()
{
  beep(a, 500);
  beep(a, 500);
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  delay(500);


  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);

  delay(500);
}

void secondSection()
{
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);
  beep(fSH, 250);

  delay(325);

  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);
  beep(cSH, 175);
  beep(cH, 125);
  beep(b, 125);
  beep(cH, 250);

  delay(350);
}

void fun() {
  //Play first section
  firstSection();

  //Play second section
  secondSection();

  //Variant 1
  beep(f, 250);
  beep(gS, 500);
  beep(f, 350);
  beep(a, 125);
  beep(cH, 500);
  beep(a, 375);
  beep(cH, 125);
  beep(eH, 650);

  delay(500);

  //Repeat second section
  secondSection();

  //Variant 2
  beep(f, 250);
  beep(gS, 500);
  beep(f, 375);
  beep(cH, 125);
  beep(a, 500);
  beep(f, 375);
  beep(cH, 125);
  beep(a, 650);

  delay(650);

  speed = 0;
}

int readUltrasonic() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  return duration * 0.034 / 2;
}

void stopEngines() {
  dir = 0;
  speed = 0;
  StartMotor (mpin00, mpin01, dir, abs(speed * 10));
  StartMotor (mpin10, mpin11, dir, abs(speed * 10));
}

void turnLeft() {
  StartMotor (mpin00, mpin01, 1, 90);
  StartMotor (mpin10, mpin11, 0, 90);
  delay (500);
  stopEngines();
}

void turnRight() {
  StartMotor (mpin00, mpin01, 0, 90);
  StartMotor (mpin10, mpin11, 1, 90);

  delay (500);
  stopEngines();
}

void goForward(int theSpeed) {
  dir = 1;
  speed = theSpeed;
  StartMotor (mpin00, mpin01, dir, abs(speed * 10));
  StartMotor (mpin10, mpin11, dir, abs(speed * 10));
}


void loop() {

  distance = readUltrasonic();
  Serial.print("Distance: ");
  Serial.println(distance);

  lightUpLeds(distance);

  if (autonomusMode == 1) {
    if (distance < 40) {
      //daca distanta este intre 20 si 40 cm, atunci ne oprim si cautam o noua cale
      stopEngines();
      //ma uit in stanga si citesc distanta
      writeServo(servoPin, 0);
      delay(500);
      distance = readUltrasonic();

      if (distance > 40) {
        Serial.write("facem stanga");
        //daca este liber, miscam masinuta si ne ducem acolo
        turnLeft();
        writeServo(servoPin, 90);//punem ultrasonicul in fata
        delay(1000);
        goForward(5);
      }

      else {
        //ma uit in dreapta si citesc distanta
        writeServo(servoPin, 90);
        delay(1000);
        writeServo(servoPin, 180);
        delay(1000);

        distance = readUltrasonic();

        if (distance > 40) {
          Serial.write("facem dreapta");
          //daca este liber, miscam masinuta si ne ducem acolo
          writeServo( servoPin, 90);
          delay(1000);
          delay(500);
          turnRight();
          goForward(5);
        }
      }
    }
  }  //emergency break
  if (distance < 20) {
    dir = 0;
    speed = 0;
    StartMotor (mpin00, mpin01, dir, abs(speed * 10));
    StartMotor (mpin10, mpin11, dir, abs(speed * 10));
  }
  else if (Serial.available()) // Citire de pe Bluetooth, trimite la PC
  { char c = Serial.read();

    if ( c == 'w') {

      speed++;
      if (speed >= 0) {
        dir = 1;
      }
      else {
        dir = 0;
      }
      autonomusMode = 0;

    }
    else if ( c == 's') {
      speed--;
      if (speed >= 0) {
        dir = 1;
      }
      else {
        dir = 0;
      }
      autonomusMode = 0;

    }
    else if ( c == 'a') {
      StartMotor (mpin00, mpin01, 0, 128);
      StartMotor (mpin10, mpin11, 0, 0);

      delay (500); // Cât timp e motorul pornit
      delayStopped(500); // Cât timp e oprit
    }
    else if ( c == 'd') {
      StartMotor (mpin00, mpin01, 0, 0);
      StartMotor (mpin10, mpin11, 0, 128);

      delay (500); // Cât timp e motorul pornit
      delayStopped(500); // Cât timp e oprit
      autonomusMode = 0;
    }
    else if ( c == 'p') {
      dir = 0;
      speed = 0;
      autonomusMode = 0;
    }
    else if (c == 'f') {
      fun();
      autonomusMode = 0;

    }
    else if (c == 't') {
      //facem sa mearga in fata cu viteza 30
      speed = 5;
      dir = 1;
      autonomusMode = 1;
      
    }

    StartMotor (mpin00, mpin01, dir, abs(speed * 10));
    StartMotor (mpin10, mpin11, dir, abs(speed * 10));
  }

}
