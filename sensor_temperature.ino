#include <dht.h>

dht DHT;

#define DHT22_PIN 7
#define LED_PIN   2
#define MOTOR_PIN 3

float humidity;
float temperature;
int   chk;
float temp_calibrated = 0;
int   measurement = 5;
float threshold = 0.5;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  //calibrate sensor
  chk = DHT.read22(DHT22_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
      for (int i=0; i < measurement; i++){
        temp_calibrated = temp_calibrated + DHT.temperature;
        delay(100);
      }
      temp_calibrated = temp_calibrated / measurement;
      Serial.print("Calibrated: "); 
      Serial.println(temp_calibrated);
      Serial.print("Threshold: ");
      Serial.println(temp_calibrated + threshold);
      break;
    case DHTLIB_ERROR_CHECKSUM: 
      break;
    case DHTLIB_ERROR_TIMEOUT: 
      break;
    default: 	
      break;
  }
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
}

void loop()
{
  // READ DATA
  Serial.print("DHT22, \t");
  chk = DHT.read22(DHT22_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
		Serial.print("OK,\t"); 
		break;
    case DHTLIB_ERROR_CHECKSUM: 
		Serial.print("Checksum error,\t"); 
		break;
    case DHTLIB_ERROR_TIMEOUT: 
		Serial.print("Time out error,\t"); 
		break;
    default: 
		Serial.print("Unknown error,\t"); 
		break;
  }
  // DISPLAY DATA
  humidity = DHT.humidity;
  temperature = DHT.temperature;
  Serial.print(humidity, 1);
  Serial.print(",\t");
  Serial.println(temperature, 1);

  // Check for temp
  if (temperature > temp_calibrated + threshold) {
    //Serial.println("se calento el parche!!");
    digitalWrite(LED_PIN,HIGH);
    analogWrite(MOTOR_PIN,255);
  } 
  else {
    digitalWrite(LED_PIN,LOW);
    analogWrite(MOTOR_PIN,0);
  }
  
  //Sensing period 
  delay(2000);
}
