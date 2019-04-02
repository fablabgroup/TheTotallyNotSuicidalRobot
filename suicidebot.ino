int enable1Pin = 10;
int in1Pin = 9;
int in2Pin = 8;

int enable2Pin = 11;
int in3Pin = 12;
int in4Pin = 13;


const int echoPin =2;
const int trigPin =3;
long duration, cm;

const int edgeLPin = 4;
const int edgeRPin = 5;
int L = LOW;
int R = LOW;


boolean turn = false;
int speed = 1;
boolean start = true;
boolean stop = false;

void setup()
{
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
  pinMode(edgeLPin,INPUT);
  pinMode(edgeRPin,INPUT);

}

void loop()
{
  L = digitalRead(edgeLPin);
  R = digitalRead(edgeRPin);
  if (L == HIGH || R == HIGH) {
  	stop = true;
  }
  digitalWrite(trigPin,LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin,LOW);
  
  pinMode(echoPin,INPUT);
  duration = pulseIn(echoPin,HIGH);
  cm =microsecondsToCentimeters(duration);
  delay(80);
  if (stop) {
  	setMotor(0,true);
  }
  if (!stop && cm < 50 && !turn) {
    turn = true;
    setMotor(speed, turn);
    }
  if (!stop && (cm > 50 && turn) || start){
	turn = false;
    setMotor(speed, turn);
    }
  
  start = false;
  
}

void setMotor(int speed, boolean turn)
{
  analogWrite(enable1Pin, 0);
  analogWrite(enable2Pin, 0);
  delay(1000);
  
  analogWrite(enable1Pin, speed);
  digitalWrite(in1Pin, true);
  digitalWrite(in2Pin, false);
  
  analogWrite(enable2Pin, speed);
  digitalWrite(in3Pin, ! turn);
  digitalWrite(in4Pin, turn);
}


long microsecondsToCentimeters(long microseconds){
  return microseconds /29/2;}