
#include <Servo.h>

Servo myservo;
Servo myservo2; // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 50;
// variable to store the servo position

int Speed = 185;

int motorpin3 = 3;
int motorpin4 = 4;
int pwm2 = 5;               // LEFT motor pin and pwm
int flag = 0;
int motorpin1 = 7;
int motorpin2 = 8;
int pwm1 = 9;              // RIGHT motor pin and pwm

int s1 = A1; //orange
int s2 = A2; //white
int s3 = A3; //brown
int s4 = A4; //black
int s5 = A5; //black
//Pin assignment
const int usTrigPin = 10; //connects to Arduino digital pin #2
const int usEchoPin = 11; //connects to Arduino digital pin #3


const int led = 13;      //Arduino built-in led. No connection required

//operational parameters
const int paceOfSound = 29.15;  //pace of sound = 1/speed of sound
//              = 1/0.03435 cm/ss
//              = 29.15 us/cm

//CALIBRATION
int turningPoint = 6;  //turn when an obstacle is within 20cm (approx 8in)

//wait 100msec until next sensor check.
int sensDelay = 100;

//used only in testing phase
boolean DEBUG = false;    //change to true when debuging. See serial monitor for log

// the setup routine runs once when you press reset or power on
void setup() {
  {
    myservo.attach(2);
    myservo2.attach(12);
    
    myservo.write(50);
    myservo2.write(50);
    delay(2000);
  
    Serial.begin(9600);
    pinMode(s1, INPUT);
    pinMode(s2, INPUT);
    pinMode(s3, INPUT);
    pinMode(s4, INPUT);
 pinMode(s5, INPUT);
    // Motor pins and Pulse Width Modulation declared by pinMode
    pinMode(motorpin1, OUTPUT);
    pinMode(motorpin2, OUTPUT);
    pinMode(motorpin3, OUTPUT);
    pinMode(motorpin4, OUTPUT);
    pinMode(pwm1, OUTPUT);
    pinMode(pwm2, OUTPUT);
  }
  //set digital pin modes for ultrasonic sensors
  pinMode(usTrigPin, OUTPUT);
  pinMode(usEchoPin, INPUT);

  //set digital pin mode for built-in led
  pinMode(led, OUTPUT);

}


void loop() {
  

 goForward();
  if (flag == 0)
  {
    
    sonarCheck();
  }


}

void sonarCheck()
{
  int distance;

  // call getDistance to get the distance to an obstacle. Ignore anything farther than 100cm
  distance = getDistance();
  Serial.println(distance);
  //,l'delay(100);
  if (distance < 6 && distance > 0 )
  {
    grab();
    if (digitalRead(s5) == 0) { myservo.attach(2);
  myservo2.attach(12);
    ServoUp();
    survotake();
   }
    fulturn();
    flag = 1;
    Speed == 200;
  }


}

int getDistance() {

  long duration, distance;

  digitalWrite(usTrigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line

  //send 10 micro second pulse to trigger
  digitalWrite(usTrigPin, HIGH);
  delayMicroseconds(10); // Added this line per spec (spec says at least 10us)
  digitalWrite(usTrigPin, LOW);

  //Below step wait for HIGH upto a second (default) on the Echo pin before timing out.
  duration = pulseIn(usEchoPin, HIGH);   //wait for HIGH

  //calculate the distance in cm
  distance = (duration / 2) / paceOfSound;

  //We don't care about distance of more than 100cm
  if (distance >= 100 || distance <= 0) {
    if (DEBUG) Serial.println("getDistance: Out of range");
    return 0;
  } else {
    if (DEBUG) {
      Serial.print("getDistance: ");
      Serial.print(distance);
      Serial.println(" cm");
    }
    return distance;
  }
}

void ServoUp() {
 
{  
   for (pos = 50; pos <= 70; pos += 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
   {
    for (pos = 50; pos <= 140; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
    // waits 15ms for the servo to reach the position
  }

}

}

void survotake()
{  
   for (pos = 70; pos >= 40; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void leave()
 {
 
{  
   for (pos = 40; pos <= 70; pos++) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
}
   
    for (pos = 140; pos >= 50; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);
    // waits 15ms for the servo to reach the position
  }
  delay(200000);

}



void goForward ()
{
  {

    Serial.print(digitalRead(s1));  // Mark the Sensors for instant Digital Read in 0,1
    Serial.print(digitalRead(s2));
    Serial.print(digitalRead(s3));
    Serial.print(digitalRead(s4));
    Serial.println () ;


    if  (digitalRead(s1) == 0 && digitalRead(s2) == 1 && digitalRead(s3) == 1 && digitalRead(s4) == 0) {
      forward();
    }
    else if (digitalRead(s1) == 0 && digitalRead(s2) == 1 && digitalRead(s3) == 0 && digitalRead(s4) == 0) {
      sl();
    }
    else if (digitalRead(s1) == 1 && digitalRead(s2) == 1 && digitalRead(s3) == 0 && digitalRead(s4) == 0) {
      ml();
    }
    else if (digitalRead(s1) == 1 && digitalRead(s2) == 0 && digitalRead(s3) == 0 && digitalRead(s4) == 0) {
      hl();

    }
    else if (digitalRead(s1) == 0 && digitalRead(s2) == 0 && digitalRead(s3) == 1 && digitalRead(s4) == 0) {
      sr();
    }
    else if (digitalRead(s1) == 0 && digitalRead(s2) == 0 && digitalRead(s3) == 1 && digitalRead(s4) == 1) {
      mr();
    }
    else if (digitalRead(s1) == 0 && digitalRead(s2) == 0 && digitalRead(s3) == 0 && digitalRead(s4) == 1) {
      hr();

    }
    else if (digitalRead(s1) == 0 && digitalRead(s2) == 0 && digitalRead(s3) == 0 && digitalRead(s4) == 0) {
      oo();

    }
    else if (digitalRead(s1) == 1 && digitalRead(s2) == 1 && digitalRead(s3) == 1 && digitalRead(s4) == 1) {
     grab();
      leave();
      delay (2000000);
     
    }

  }

}

void fulturn(){
  while (digitalRead(s4) == 0)
    {digitalWrite(motorpin2, LOW);
  digitalWrite(motorpin1, HIGH);
  analogWrite(pwm1, Speed - 75);

  digitalWrite(motorpin3, LOW);
  digitalWrite(motorpin4, HIGH);
  analogWrite(pwm2, Speed - 75);}
  
   
}
void grab ()
{

  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, HIGH);
  analogWrite(pwm1, 70);

  digitalWrite(motorpin3, LOW);
  digitalWrite(motorpin4, HIGH);
  analogWrite(pwm2, 70);
  delay(100);

  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
  analogWrite(pwm1, 0);

  digitalWrite(motorpin3, HIGH);
  digitalWrite(motorpin4, LOW);
  analogWrite(pwm2, 0);
}

// Adjusting Directions

void forward() {
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
  analogWrite(pwm1, Speed);

  digitalWrite(motorpin3, HIGH);
  digitalWrite(motorpin4, LOW);
  analogWrite(pwm2, Speed);
}


void sl() {
  digitalWrite(motorpin2, LOW);
  digitalWrite(motorpin1, HIGH);
  analogWrite(pwm1, Speed - 70);

  digitalWrite(motorpin3, HIGH);
  digitalWrite(motorpin4, LOW);
  analogWrite(pwm2, Speed - 32);
}

void sr() {
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
  analogWrite(pwm1, Speed - 32);

  digitalWrite(motorpin4, LOW);
  digitalWrite(motorpin3, HIGH);
  analogWrite(pwm2, Speed - 70);
}

void ml() {
  analogWrite(pwm1, Speed - 130);
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, HIGH);
  analogWrite(pwm2, Speed - 50);
  digitalWrite(motorpin3, HIGH);
  digitalWrite(motorpin4, LOW);
}


void mr() {
  analogWrite(pwm1, Speed - 50);
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
  analogWrite(pwm2, Speed - 130);
  digitalWrite(motorpin3, LOW);
  digitalWrite(motorpin4, HIGH);

}

void hl() {
  analogWrite(pwm1, Speed - 130);
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);

  analogWrite(pwm2, Speed- 60);
  digitalWrite(motorpin3, HIGH);
  digitalWrite(motorpin4, LOW);
}


void hr() {
  analogWrite(pwm1, Speed- 60);
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);

  analogWrite(pwm2, Speed - 130);
  digitalWrite(motorpin3, HIGH);
  digitalWrite(motorpin4, LOW);

}

void oo() {
  analogWrite(pwm1, Speed - 80);
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, HIGH);

  analogWrite(pwm2, Speed - 80);
  digitalWrite(motorpin3, LOW);
  digitalWrite(motorpin4, HIGH);


}


