#include <ArduinoBLE.h>

#include "arduino_secrets.h"
String serviceUUIDTop = SERVICE_UUID_TOP;
String serviceUUIDUnd = SERVICE_UUID_UND;

int uuidTop;
int uuidUnd;

int sendingCount = 0;

#define _DEBUG_

void setup() {
  #ifdef _DEBUG_
    Serial.begin(9600);
    while (!Serial);
  #endif
  
  Serial1.begin(9600);
  while (!Serial1);

  if (!BLE.begin()) {
    while (1);
  }
  
  BLE.scan(true);

  char buf[50];
  serviceUUIDTop.toCharArray(buf, 50);
  uuidTop = strtol(buf,NULL,16);
  serviceUUIDUnd.toCharArray(buf, 50);
  uuidUnd = strtol(buf,NULL,16);
}

void loop() {
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    if (peripheral.hasAdvertisementData()) {
      int advLen = peripheral.advertisementDataLength();
      int prssi = peripheral.rssi();
      if (advLen == 6 && prssi > -80) {
        uint8_t advData[advLen];
        peripheral.advertisementData(advData, advLen);

        if (advData[1] == 22 && advData[2] == uuidUnd && advData[3] == uuidTop) {
          char sendPacket[5] = "";
          sprintf(sendPacket, "%02x%02x\n", advData[4], advData[5]);
          #ifdef _DEBUG_
            Serial.print(sendPacket);
          #endif
          Serial1.print(sendPacket);
          sendingCount += 1;
        }
      }
    }
  }

  if (sendingCount >= 10) {
    BLE.stopScan();
    #ifdef _DEBUG_
      Serial.println("Sending 10 times. Stop Sending Data.");
    #endif
    Serial1.print("end\n");
    String cmd = "";
    while (!cmd.equals("ack")) {
      #ifdef _DEBUG_
        Serial.println("Waiting resume cmd...");
      #endif
      cmd = "";
      while (!Serial1.available());
      cmd = Serial1.readStringUntil('\n');
      #ifdef _DEBUG_
        Serial.print("Received msg : ");
        Serial.println(cmd);
      #endif
      delay(1000);
    }
    
    if (cmd.equals("ack")) {
      #ifdef _DEBUG_
        Serial.println("Received resume cmd!");
      #endif
      sendingCount = 0;
      BLE.scan(true);
      delay(1);
    }
  }
}
