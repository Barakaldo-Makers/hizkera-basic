#include <Arduino.h>
#include <SoftwareSerial.h>
#include <60ghzfalldetection.h>
#include <SensirionI2CScd4x.h>
#include <Wire.h>

SoftwareSerial SSerial(32, 33); // RX, TX Tambien es posible usar 25-26
#define Serial1 SSerial

FallDetection_60GHz radar;

void radarInit() {
    radar.SerialInit();
}

void radarLoop() {
    radar.recvRadarBytes();                       //Receive radar data and start processing
        if (radar.newData == true) {                  //The data is received and transferred to the new list dataMsg[]
    byte dataMsg[radar.dataLen+3] = {0x00};
    dataMsg[0] = 0x53;                         //Add the header frame as the first element of the array
    for (byte n = 0; n < radar.dataLen; n++)dataMsg[n+1] = radar.Msg[n];  //Frame-by-frame transfer
    dataMsg[radar.dataLen+1] = 0x54;
    dataMsg[radar.dataLen+2] = 0x43;
    radar.newData = false;                     //A complete set of data frames is saved
    
    radar.ShowData(dataMsg);                 //Serial port prints a set of received data frames
    radar.Fall_Detection(dataMsg);         //Use radar built-in algorithm to output human motion status
  }
}



void setup()
{
    Serial.begin(115200);
    delay(1500);
    Serial.println("Start sensors init ");
    radarInit();
   }

void loop()
{
    radarLoop();   

}
