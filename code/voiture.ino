int speedPin_M1 = 5;     //M1 Speed Control
int speedPin_M2 = 6;     //M2 Speed Control
int directionPin_M1 = 4;     //M1 Direction Control
int directionPin_M2 = 7;     //M1 Direction Control

int car_speed = 100;

char Mymessage[10]; 

void setup() {
  Serial.begin(9600);
}

void loop() {
    Serial.readBytes(Mymessage,5); //Read the serial data and store in var
    Serial.println(Mymessage); //Print data on Serial Monitor
    interpretMessage(Mymessage);
    delay(1000);
}

void interpretMessage(char * msg)
{
  if (msg == "advance"){carAdvance(car_speed, car_speed);}
  else if (msg == "back"){carBack(car_speed, car_speed);}
  else if (msg == "left"){carTurnLeft(car_speed, car_speed);}
  else if (msg == "right"){carTurnRight(car_speed, car_speed);}
  else if (msg == "stop"){carStop();}
}

void carStop() {                //  Motor Stop
  digitalWrite(speedPin_M2, 0);
  digitalWrite(directionPin_M1, LOW);
  digitalWrite(speedPin_M1, 0);
  digitalWrite(directionPin_M2, LOW);
}

void carBack(int leftSpeed, int rightSpeed) {       //Move backward
  analogWrite (speedPin_M2, leftSpeed);             //PWM Speed Control
  digitalWrite(directionPin_M1, HIGH);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, HIGH);
}

void carAdvance(int leftSpeed, int rightSpeed) {     //Move forward
  analogWrite (speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, LOW);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, LOW);
}

void carTurnLeft(int leftSpeed, int rightSpeed) {    //Turn Left
  analogWrite (speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, LOW);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, HIGH);
}
void carTurnRight(int leftSpeed, int rightSpeed) {    //Turn Right
  analogWrite (speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, HIGH);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, LOW);
}
