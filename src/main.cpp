#include <Arduino.h>
#include <60ghzfalldetection.h>
#include <SensirionI2CScd4x.h>
#include <Wire.h>
#include <esp_now.h>
#include <WiFi.h>
 
FallDetection_60GHz radar;

SensirionI2CScd4x scd4x;

void printUint16Hex(uint16_t value) {
    Serial.print(value < 4096 ? "0" : "");
    Serial.print(value < 256 ? "0" : "");
    Serial.print(value < 16 ? "0" : "");
    Serial.print(value, HEX);
}

void printSerialNumber(uint16_t serial0, uint16_t serial1, uint16_t serial2) {
    Serial.print("Serial: 0x");
    printUint16Hex(serial0);
    printUint16Hex(serial1);
    printUint16Hex(serial2);
    Serial.println();
}

// EspNow sender
// REPLACE WITH THE RECEIVER'S MAC Address
uint8_t broadcastAddress[] = {0xC8, 0xC9, 0xA3, 0xFB, 0xED, 0xE0};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
<<<<<<< HEAD
    int id; // must be unique for each sender board
    int x;
    int y;
    int z;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Create peer interface
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
=======
  int id;
  int x;
  int y;
  int z;
}struct_message;
// Create a struct_message called myData
struct_message myData;
// Create a structure to hold the readings from each board
struct_message board1;
struct_message board2;
struct_message board3;
// Create an array with all the structures
struct_message boardsStruct[3] = {board1, board2, board3};
// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.printf("Board ID %u: %u bytes\n", myData.id, len);
  // Update the structures with the new incoming data
  boardsStruct[myData.id-1].x = myData.x;
  boardsStruct[myData.id-1].y = myData.y;
  boardsStruct[myData.id-1].z = myData.z;
  Serial.printf("x value: %d \n", boardsStruct[myData.id-1].x);
  Serial.printf("y value: %d \n", boardsStruct[myData.id-1].y);
  Serial.printf("z value: %d \n", boardsStruct[myData.id-1].z);
  Serial.println();
>>>>>>> 82178650f71b4f95f84afa4345cc77e917b3b4ad
}

void EspNowInit() {
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
<<<<<<< HEAD
=======
  Serial.println(WiFi.macAddress());
>>>>>>> 82178650f71b4f95f84afa4345cc77e917b3b4ad
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
<<<<<<< HEAD
// Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void  EspNowLoop() {
// Set values to send
  myData.id = 1;
  //myData.x = random(0,50);
  //myData.y = random(0,50);
  myData.x;
  myData.y;
  myData.z;
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(5000);

}

void radarInit() {
    radar.SerialInit();
}

=======
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
    esp_now_register_recv_cb(OnDataRecv);
}

void EspNowLoop() {
   // Acess the variables for each board
  int board1X = boardsStruct[0].x;
  int board1Y = boardsStruct[0].y;
  int board1Z = boardsStruct[0].z;
  int board2X = boardsStruct[1].x;
  int board2Y = boardsStruct[1].y;
  int board2Z = boardsStruct[1].z;
  int board3X = boardsStruct[2].x;
  int board3Y = boardsStruct[2].y;
  int board3Z = boardsStruct[3].z;

  delay(10000);
}

void radarInit() {
    radar.SerialInit();
}

>>>>>>> 82178650f71b4f95f84afa4345cc77e917b3b4ad
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

void scd4xInit() {
    uint16_t error;
    char errorMessage[256];

    scd4x.begin(Wire);

    // stop potentially previously started measurement
    error = scd4x.stopPeriodicMeasurement();
    if (error) {
        Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }

    uint16_t serial0;
    uint16_t serial1;
    uint16_t serial2;
    error = scd4x.getSerialNumber(serial0, serial1, serial2);
    if (error) {
        Serial.print("Error trying to execute getSerialNumber(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else {
        printSerialNumber(serial0, serial1, serial2);
    }

    // Start Measurement
    error = scd4x.startPeriodicMeasurement();
    if (error) {
        Serial.print("Error trying to execute startPeriodicMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }

    Serial.println("Waiting for first measurement... (5 sec)");

}

void scd4xLoop() {
    uint16_t error;
    char errorMessage[256];

    delay(5000);

    // Read Measurement
    uint16_t co2;
    float temperature;
    float humidity;
    error = scd4x.readMeasurement(co2, temperature, humidity);
    if (error) {
        Serial.print("Error trying to execute readMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else if (co2 == 0) {
        Serial.println("Invalid sample detected, skipping.");
    } else {
        Serial.print("Co2:");
        Serial.print(co2);
        Serial.print("\t");
        Serial.print("Temperature:");
        Serial.print(temperature);
        Serial.print("\t");
        Serial.print("Humidity:");
        Serial.println(humidity);
        Serial.println();
        myData.x = co2;
        myData.y = humidity;
        myData.z = temperature;
    }
}

<<<<<<< HEAD
void setup()
{
  Serial.begin(115200);
  delay(1500);
  Serial.println("Readly");
  EspNowInit();
  radarInit();
  Wire.begin();
  scd4xInit(); 
  
    uint16_t error;
    char errorMessage[256];

=======

void setup()
{
  Serial.begin(115200);
  delay(1500);
  Serial.println("Readly");
  EspNowInit();
  radarInit();
  Wire.begin();
  scd4xInit(); 
  
    uint16_t error;
    char errorMessage[256];

>>>>>>> 82178650f71b4f95f84afa4345cc77e917b3b4ad
    scd4x.begin(Wire);

    // stop potentially previously started measurement
    error = scd4x.stopPeriodicMeasurement();
    if (error) {
        Serial.print("Error trying to execute stopPeriodicMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }
    uint16_t serial0;
    uint16_t serial1;
    uint16_t serial2;
    error = scd4x.getSerialNumber(serial0, serial1, serial2);
    if (error) {
        Serial.print("Error trying to execute getSerialNumber(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    } else {
        printSerialNumber(serial0, serial1, serial2);
    }
    // Start Measurement
    error = scd4x.startPeriodicMeasurement();
    if (error) {
        Serial.print("Error trying to execute startPeriodicMeasurement(): ");
        errorToString(error, errorMessage, 256);
        Serial.println(errorMessage);
    }
    Serial.println("Waiting for first measurement... (5 sec)");
}

void loop()
{
  radarLoop();   
  scd4xLoop();
  EspNowLoop();
}
