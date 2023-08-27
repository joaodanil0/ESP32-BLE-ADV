/*
 * ESP32-Dynabeacon
 * Non-connectable beacon that changes scan response data periodically
 * 
 * Tested on ESP32 devkit
 * 
 * Created on 23-1-2018 by RammaK
 * Based on Neil Kolban's ESP32-BLE library at https://github.com/nkolban/ESP32_BLE_Arduino
 * and https://github.com/rammak/ESPthings/blob/master/Examples/ESP32/ESP32-Dynabeacon-test-1.ino
*/
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

BLEAdvertisementData advert;
BLEAdvertising *pAdvertising;

int i = 0;

//manufacturer code (0x02E5 for Espressif)
int man_code = 0xFFFF;


// function takes String and adds manufacturer code at the beginning 
void setManData(String c, int c_size, BLEAdvertisementData &adv, int m_code) {
  
  String s;
  char b2 = (char)(m_code >> 8);
  m_code <<= 8;
  char b1 = (char)(m_code >> 8);
  s.concat(b2);
  s.concat(b1);
  s.concat(c);

  
  adv.setManufacturerData(s.c_str());
  
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("TEST1");
  BLEServer *pServer = BLEDevice::createServer();

  pAdvertising = pServer->getAdvertising();
  advert.setName("TEST1");
  pAdvertising->setAdvertisementData(advert);
  pAdvertising->start();
}

void loop() {

  BLEAdvertisementData scan_response;
  

  
  char str[10] = {'0'};

  snprintf( str, 10, "%09d", i );

  setManData(str, 10 , scan_response, man_code);

  


  pAdvertising->stop();
  delay(50);
  pAdvertising->setScanResponseData(scan_response);
  pAdvertising->start();

  i++;  
}
