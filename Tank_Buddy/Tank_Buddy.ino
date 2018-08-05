#include <NewPing.h>

#include <SoftwareSerial.h>
SoftwareSerial SIM900(8, 7);

int val;
int tempPin = 1;
float temp;
char incomingChar;
float cm;
#define TRIGGER_PIN 11
#define ECHO_PIN 12
#define MAX_DISTANCE 400
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


void setup() {
  SIM900.begin(4800);  
  Serial.begin(9600);
}

void loop() {
  val = analogRead(tempPin);
float mv = ( val/1024.0)*5000; 
float temp = mv/10;
Serial.print("TEMPRATURE = ");
Serial.print(temp);
Serial.print("*C");
Serial.println();


unsigned int cm = sonar.ping_cm();
   Serial.print("depth:");
   Serial.print(cm);
   Serial.println("cm");
    
  Serial.println("TCP Send :");
  Serial.print("AT\\r\\n");
  SIM900.println("AT");
  delay(5000);
  ShowSerialData(); 
  delay(5000);
  Serial.print("AT+CIPMODE=0\\r\\n");
  SIM900.println("AT+CIPMODE=0");
  delay(5000);
  ShowSerialData();
  Serial.print("AT+CIPMUX=0\\r\\n");
  SIM900.println("AT+CIPMUX=0");  
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CGATT=1\\r\\n");
  SIM900.println("AT+CGATT=1");
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CREG?\\r\\n");
  SIM900.println("AT+CREG?"); 
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CGATT?\\r\\n");
  SIM900.println("AT+CGATT?"); 
  delay(5000); 
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CSTT=\"WWW\",\"\",\"\"\\r\\n");
  SIM900.println("AT+CSTT=\"WWW\",\"\",\"\""); 
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CIICR\\r\\n");
  SIM900.println("AT+CIICR");
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CIFSR\\r\\n");
  SIM900.println("AT+CIFSR"); 
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"\\r\\n");
  SIM900.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\""); 
  delay(5000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CIPSEND=10\\r\\n");
  SIM900.println("AT+CIPSEND"); 
  delay(2000);
  ShowSerialData();
  delay(2000);
  Serial.print("GET /update?api_key=JPC08FASRF4KNUCK&field1="+String(temp)+"&field2="+String(cm)+"\\r\\n");
  SIM900.print("GET /update?api_key=JPC08FASRF4KNUCK&field1="+String(temp)+"&field2="+String(cm)+"\r\n\x1A"); 
  delay(10000);
  ShowSerialData();
  delay(5000);
  Serial.print("AT+CIPSHUT\\r\\n");
  SIM900.println("AT+CIPSHUT"); 
  delay(5000);
  ShowSerialData();
  delay(5000);
}

void ShowSerialData()
{
  while(SIM900.available()!=0) 
  Serial.write(char (SIM900.read()));
}



