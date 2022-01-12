#include <SoftSerial.h>  //Software Serial Port
#define RxD 2
#define TxD 1

#define DEBUG_ENABLED  1
 
SoftSerial blueToothSerial(RxD,TxD);

int led = 1 ;
 
void setup() 
{ 
  //delay(5000);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBlueToothConnection();
  digitalWrite(TxD,LOW);
  
  //pinMode(0,OUTPUT);
  //digitalWrite(0,HIGH);  
  pinMode(0,OUTPUT);
  digitalWrite(0,HIGH);

} 
 
void loop() 
{ 
  char recvChar;
  while(1){
    //check if there's any data sent from the remote bluetooth shield
    if(blueToothSerial.available()){
      recvChar = blueToothSerial.read();

        if(recvChar=='1'){
          digitalWrite(0,LOW);  
          //blueToothSerial.print("bluetooth OK!\n");
          delay(6000);
          digitalWrite(0,HIGH);
          }
 
    }
  }
} 
 
void setupBlueToothConnection()
{
  blueToothSerial.begin(9600); //Set BluetoothBee BaudRate to default baud rate 38400
  // blueToothSerial.print("AT+NAME=Dwirze\r\n");
 /* blueToothSerial.print("\r\n+STWMOD=0\r\n"); //set the bluetooth work in slave mode
  blueToothSerial.print("\r\n+STNA=DWI\r\n"); //set the bluetooth name as "HC-05"
  blueToothSerial.print("AT+NAME=DWI\r\n");
  blueToothSerial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  blueToothSerial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here */
  
 // delay(2000); // This delay is required.
  //blueToothSerial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
 // blueToothSerial.print("bluetooth connected!\n");
  
  delay(1000); // This delay is required.
  blueToothSerial.flush();
}
