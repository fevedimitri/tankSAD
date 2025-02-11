//Receiver
#include <LoRa.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Servo.h>


Servo servoX;
Servo servoY;

const size_t starti = 1;

int servoVal[2] = {90,90};
int joyVal [2] = {0, 0};
int wheelVal [2] = {0,0};

String LoRaData;
char * LoRaDataNew;


void setup() {
  servoX.write(90);
  servoY.write(90);
  servoX.attach(A0);
  servoY.attach(A1);
  pinMode(5,OUTPUT);
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
    Serial.println("LoRa Initializing OK!");
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");
    // read packet
    while (LoRa.available()) {

      //Serial.println((char)LoRa.read());
      LoRaData = LoRa.readString();
      LoRaDataNew = LoRaData.c_str();
      const size_t len = strlen(LoRaDataNew);
      char buffer[len + 1];
      String buffer_s;
      //Serial.println(LoRaDataNew);
      slice_str(LoRaDataNew, buffer,starti , len);
      //Serial.print(buffer);
      // print RSSI of packet
      //Serial.print("' with RSSI ");
      //Serial.println(LoRa.packetRssi());
      
       
    int d = atoi(buffer);      //convert String to Int
    Serial.print("Int Value = ");
    Serial.println(d);
    Serial.println("");
    Serial.println(LoRaDataNew[0]);
    if (LoRaDataNew[0] == '0' or LoRaDataNew[0] == '1') 
      {
        Serial.println("message for servo motors");
        setJoyVal(d,LoRaDataNew[0]);
        setServoVal();             
      }
    else if (LoRaDataNew[0] == '2' or LoRaDataNew[0] == '3')
    {
      Serial.println("message for wheels");
      if (LoRaDataNew[0] == '2'){wheelVal[0] = buffer;}
      else {wheelVal[1] = buffer;}
      Serial.write(setWheels(wheelVal[0],wheelVal[1]),5);
    }
    }  
  }
}

char * setWheels(int x, int y)
{
  if (y > 600){return "right";}
  else if (y < 400){return "right";}
  else if (x < 400){return "advance";}
  else if (x > 600){return "back";}
  else{return "stop";}
}


void slice_str(const char * str, char * buffer, size_t start, size_t end)
{
    size_t j = 0;
    for ( size_t i = start; i <= end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = 0;
}

void setJoyVal(int buff, int servo)
  {
    joyVal[servo] = buff;    
      
  }


void setServoVal()//takes joystick value and gives value to servo motor
  {
    if (joyVal[0] > 530)
      {
        if (!(servoVal[0] <= 0))
          {servoVal[0] = servoVal[0] - 2;}
      }
    else if (joyVal[0] < 500)
      {
        if (!(servoVal[0] >= 180))
          {servoVal[0] = servoVal[0] + 2;}
      }
    if (joyVal[1] > 530)
      {
        if (!(servoVal[1] >= 180))
          {servoVal[1] = servoVal[1] + 2;}
      }
    else if (joyVal[1] < 500)
      {
        if (!(servoVal[1] <= 0))
          {servoVal[1] = servoVal[1] - 2;}
      }
    map(servoVal[0], -1000, 1000,0,180);
    map(servoVal[1], -1000, 1000,0,180);
    Serial.print("servo value X: ");
    Serial.println(servoVal[0]);
    Serial.print("servo value Y: ");
    Serial.println(servoVal[1]);
    servoX.write(servoVal[0]);
    servoY.write(servoVal[1]);
  }
