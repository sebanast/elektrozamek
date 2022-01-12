#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
 
BLECharacteristic *characteristicTX; //Za pośrednictwem tego obiektu będziemy przesyłać dane do klienta
BLEServer* pServer = NULL;
 
bool deviceConnected = false; //sterowanie podłączonym urządzeniem
const int PIN = 23;
 
#define SERVICE_UUID   "ab0828b1-198e-4351-b779-901fa0e0371e"
#define CHARACTERISTIC_UUID_RX  "4ac8a682-9736-4e5d-932b-e9b31405049c"
#define CHARACTERISTIC_UUID_TX  "0972EF8C-7613-4075-AD52-756F33D4DA91"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class CharacteristicCallbacks: public BLECharacteristicCallbacks {
     void onWrite(BLECharacteristic *characteristic) {
          std::string rxValue = characteristic->getValue(); 
          //sprawdź czy są znaki
          if (rxValue.length() > 0) {
 
    /*           for (int i = 0; i < rxValue.length(); i++) {
             Serial.print(rxValue[i]);
               }   */
         
               if (rxValue.find("1111") != -1) { 
             digitalWrite(PIN, LOW);
             delay(5000);
             digitalWrite(PIN, HIGH);
               }
                else if (rxValue.find("0") != -1) { 
             digitalWrite(PIN, HIGH);
               }
          }
     }
};


void setup() {
   // Serial.begin(115200);
    pinMode(PIN, OUTPUT);
    digitalWrite(PIN, HIGH);
    BLEDevice::init("dwirze");
 
    // Create the BLE Server
    pServer = BLEDevice::createServer();
 
    pServer->setCallbacks(new MyServerCallbacks()); //seta o callback do server
 
    // Create the BLE Service
    BLEService *service = pServer->createService(SERVICE_UUID);
 
    // Create a BLE Characteristic para envio de dados
    characteristicTX = service->createCharacteristic(
                       CHARACTERISTIC_UUID_TX,
                       BLECharacteristic::PROPERTY_NOTIFY
                     );
 
    characteristicTX->addDescriptor(new BLE2902());

    // Create a BLE Characteristic para recebimento de dados
    BLECharacteristic *characteristic = service->createCharacteristic(
                                                      CHARACTERISTIC_UUID_RX,
                                                      BLECharacteristic::PROPERTY_WRITE
                                                    );
 
    characteristic->setCallbacks(new CharacteristicCallbacks());
 
    // Start the service
    service->start();
 
    // Start advertising (descoberta do ESP32)
    pServer->getAdvertising()->start();
 
}



void loop() {
}
